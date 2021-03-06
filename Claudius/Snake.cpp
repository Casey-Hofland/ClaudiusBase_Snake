#include "Snake.h"
#include <ranges>
#include <cmath>
#include <numbers>

// Constructors
Snake::Snake(Vector2 position, int size, int bodyParts)
    : m_position{ position }
    , m_size{ size }
{
    SDL_Rect bodyPartRect{ static_cast<int>(position.x), static_cast<int>(position.y), size, size };

    m_head() = bodyPartRect;
    m_tail() = bodyPartRect;

	for (; bodyParts > minimumBodyParts; bodyParts--)
	{
		Grow();
	}
}

#pragma region Public update functions
void Snake::Update(float deltaTime) noexcept
{
	m_position += speed * deltaTime * m_direction;

	UpdateHead();
	UpdateBody();
	UpdateTail();
}

void Snake::Render(SDL_Renderer* renderer) const noexcept
{
    // Draw all body parts except for the head.
    SDL_SetRenderDrawColor(renderer, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);
    for (const auto& bodyPart : m_bodyParts | std::views::drop(1))
    {
        SDL_RenderFillRect(renderer, &bodyPart);
    }

	// Draw the head as a rectangle.
	//SDL_SetRenderDrawColor(renderer, headColor.r, headColor.g, headColor.b, headColor.a);
	//SDL_RenderFillRect(renderer, &Head());

	// Draw the head as an image.
	// Note: this code is unoptimized and unclear. For the assignment I would like to submit the rect function, however for the game I had to put Ulf's head in. I mean: Come on.
	auto surface = SDL_LoadBMP("../Assets/Ulf.bmp");
	auto texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect textureRect = { 0, 0, 128, 128 };

	constexpr float headScale = 0.7f;
	SDL_Rect dest = Head();
	dest.x -= static_cast<int>(m_size * headScale);
	dest.y -= static_cast<int>(m_size * headScale);
	dest.w += static_cast<int>(m_size * headScale * 2);
	dest.h += static_cast<int>(m_size * headScale * 2);

	const float angle = std::atan2(m_direction.y, m_direction.x) * (180.0f / std::numbers::pi_v<float>);
	SDL_RenderCopyEx(renderer, texture, &textureRect, &dest, angle, {}, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Snake::Grow()
{
    m_bodyParts.push_back(Tail());
}

void Snake::Shrink() noexcept
{
    if (BodyPartsSize() <= minimumBodyParts)
    {
        return;
    }
    
    m_bodyParts.pop_back();
}

void Snake::SnapPositionToSize() noexcept
{
	m_position /= static_cast<const float>(m_size);
	m_position.x = std::roundf(m_position.x);
	m_position.y = std::roundf(m_position.y);
	m_position *= static_cast<const float>(m_size);
}

// Change the snake's direction. Fails if the direction would be equal to that of the previous direction or inverse of that.
[[gsl::suppress(f.6, justification : "BodyPartAt(1): The snake is never smaller than 2 body parts, so BodyPartAt(1) may never throw. \nm_bodyParts.push_front(head): we call m_bodyParts.pop_back() right before, so m_bodyParts.push_front(head) may never throw.")]]
void Snake::ChangeDirection(Vector2 direction) noexcept
{
	direction = Vector2::normalize(direction);

	if (direction == this->m_direction
		|| direction == -this->m_direction)
	{
		return;
	}

	this->m_direction = direction;

	// Snap the head to size.
	SnapPositionToSize();
	UpdateHead();

	// If the snapping caused the head and the body to detach, update the body.
	const auto head{ Head() };
	const auto secondBodyPart{ BodyPartAt(1) };
	if (secondBodyPart.x != head.x
		|| secondBodyPart.y != head.y)
	{
		m_bodyParts.pop_back();
		m_bodyParts.push_front(head);
	}

	// Move the position by an amount that will ensure that the snake can never collide with itself when performing a U-turn.
	m_position += m_size * 0.5f * m_direction;
}

bool Snake::IsSelfColliding() const noexcept
{
	const auto& head = Head();
	const auto& tail = Tail();

	// For the third to second-to-last bodypart...
	for (const auto& bodyPart : m_bodyParts
		| std::views::take(BodyPartsSize() - 1)
		| std::views::drop(2))
	{
		// Check if we are colliding with the head, and that we are not at the same position of the tail (this prevents self collisions returning true when the snake is coiled up during the start of the game).
		if (SDL_HasIntersection(&head, &bodyPart)
			&& !(bodyPart.x == tail.x && bodyPart.y == tail.y))
		{
			return true;
		}
	}

	return false;
}
#pragma endregion

#pragma region Private update functions
// Update the head: round the floating position.
void Snake::UpdateHead() noexcept
{
	auto& head = m_head();
	head.x = static_cast<int>(std::roundf(m_position.x));
	head.y = static_cast<int>(std::roundf(m_position.y));
}

// Update the body: for every factor of 'size' that the head is ahead of the body, take the last body part and move it towards the head.
[[gsl::suppress(f.6, justification : "BodyPartAt(1): The snake is never smaller than 2 body parts, so BodyPartAt(1) may never throw. \nm_bodyParts.push_front(head): we call m_bodyParts.pop_back() right before, so m_bodyParts.push_front(head) may never throw.")]]
void Snake::UpdateBody() noexcept
{
	const SDL_Rect head{ Head() };
	const SDL_Rect secondBodyPart = m_bodyPartAt(1);

	// Calculate the number of body parts we need to update in order for our snake to stay in one piece.
	const size_t headDistance = static_cast<size_t>(std::abs(secondBodyPart.x - head.x)) + std::abs(secondBodyPart.y - head.y);
	size_t bodyPartIndex = std::min(headDistance / m_size, BodyPartsSize() - 1);

	for (; bodyPartIndex > 0; bodyPartIndex--)
	{
		// Take a reference of the head. We are calling it "nextBodyPartRef" because we'll be adding the head anew later on. Taking a reference of the head like this is free optimization.
		auto& nextBodyPartRef = m_head();

		// Move the next body part behind the head based on the snakes movement direction.
		nextBodyPartRef.x = static_cast<int>(head.x - m_direction.x * m_size * (bodyPartIndex - 1));
		nextBodyPartRef.y = static_cast<int>(head.y - m_direction.y * m_size * (bodyPartIndex - 1));

		// In the case where the head is not perfectly on the grid and our direction is a factor of minus one or less, solve for incorrect snapping.
		if (m_direction.x <= -1.0f && head.x % m_size != 0)
		{
			nextBodyPartRef.x += m_size;
		}
		if (m_direction.y <= -1.0f && head.y % m_size != 0)
		{
			nextBodyPartRef.y += m_size;
		}

		// Snap the body part to size (done implicitely by int division).
		nextBodyPartRef.x /= m_size;
		nextBodyPartRef.x *= m_size;

		nextBodyPartRef.y /= m_size;
		nextBodyPartRef.y *= m_size;

		// Pop the last body part and push the head to the front.
		m_bodyParts.pop_back();
		m_bodyParts.push_front(head);
	}
}

// Update the tail: take the distance of the head to the second body part, invert it, and apply it to the distance of the tail to the second to last body part.
[[gsl::suppress(f.6, justification : "BodyPartAt(1): The snake is never smaller than 2 body parts, so BodyPartAt(1) may never throw. \nBodyPartAt(secondToLastBodyPartIndex): we are retrieving an index that we know is less than the BodyPartsSize, so BodyPartAt(secondToLastBodyPartIndex) may never throw.")]]
void Snake::UpdateTail() noexcept
{
	auto& tailRef = m_tail();

	// If the head is the second to last body part, set the tail position equal to that of the head.
	const SDL_Rect head{ Head() };
	const auto secondToLastBodyPartIndex = BodyPartsSize() - 2;
	if (secondToLastBodyPartIndex == 0)
	{
		tailRef.x = head.x;
		tailRef.y = head.y;
		return;
	}

	// Calculate the tail distance based on how far away the head is from the second body part.
	const SDL_Rect secondBodyPart = m_bodyPartAt(1);
	const auto tailDistance = m_size - std::abs(secondBodyPart.x - head.x) - std::abs(secondBodyPart.y - head.y);

	const auto secondToLastBodyPart = BodyPartAt(secondToLastBodyPartIndex);

	if (tailRef.x != secondToLastBodyPart.x)
	{
		// Get the normalized direction in which the tail is moving away from the second to last body part (will be either 1 or -1).
		auto offsetDirection = secondToLastBodyPart.x - tailRef.x;
		offsetDirection /= std::abs(offsetDirection);

		// Move the tail away from the body part.
		const auto offset = offsetDirection * tailDistance;
		tailRef.x = (secondToLastBodyPart.x - offset);
	}

	// Same as above but for y.
	if (tailRef.y != secondToLastBodyPart.y)
	{
		auto offsetDirection = secondToLastBodyPart.y - tailRef.y;
		offsetDirection /= std::abs(offsetDirection);

		const auto offset = offsetDirection * tailDistance;
		tailRef.y = (secondToLastBodyPart.y - offset);
	}
}
#pragma endregion

#pragma region Getters & Setters
SDL_Rect& Snake::m_head() noexcept
{
	return m_bodyParts.front();
}

const SDL_Rect& Snake::Head() const noexcept
{
    return m_bodyParts.front();
}

SDL_Rect& Snake::m_tail() noexcept
{
	return m_bodyParts.back();
}

const SDL_Rect& Snake::Tail() const noexcept
{
    return m_bodyParts.back();
}

const SDL_Rect& Snake::BodyPartAt(size_t index) const
{
    return m_bodyParts.at(index);
}

SDL_Rect& Snake::m_bodyPartAt(size_t index)
{
	return m_bodyParts.at(index);
}

const std::deque<SDL_Rect>& Snake::GetBodyParts() const noexcept
{
	return m_bodyParts;
}

size_t Snake::BodyPartsSize() const noexcept
{
    return m_bodyParts.size();
}

int Snake::GetSize() const noexcept
{
	return m_size;
}

void Snake::SetSize(int size) noexcept
{
	this->m_size = size;

	for (auto& bodyPart : m_bodyParts)
	{
		bodyPart.w = bodyPart.h = size;
	}

	SnapPositionToSize();
	UpdateHead();
	UpdateBody();
}

Vector2 Snake::GetDirection() const noexcept
{
    return m_direction;
}

void Snake::SetDirection(Vector2 direction) noexcept
{
	this->m_direction = Vector2::normalize(direction);
}

Vector2 Snake::GetPosition() const noexcept
{
    return m_position;
}

void Snake::SetPosition(Vector2 position) noexcept
{
	this->m_position = position;

	SnapPositionToSize();
	UpdateHead();
	UpdateBody();
}
#pragma endregion
