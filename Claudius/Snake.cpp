#include "Snake.h"
#include <ranges>
#include <cmath>

// Constructors
Snake::Snake(Vector2 position, int size, int bodyParts)
    : m_position{ position }
    , m_size{ size }
{
    SDL_Rect bodyPartRect{ position.x, position.y, size, size };

    m_head() = bodyPartRect;
    m_tail() = bodyPartRect;

	for (; bodyParts > minimumBodyParts; bodyParts--)
	{
		Grow();
	}
}

void Snake::Update(float deltaTime) noexcept
{
    ProcessInput();

	m_position += speed * deltaTime * m_direction;

	UpdateHead();
	UpdateBody();
}

void Snake::Render(SDL_Renderer* renderer) const noexcept
{
    // Draw all body parts except for the head.
    SDL_SetRenderDrawColor(renderer, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);
    for (const auto& bodyPart : m_bodyParts | std::views::drop(1))
    {
        SDL_RenderFillRect(renderer, &bodyPart);
    }

	// Draw the head.
	SDL_SetRenderDrawColor(renderer, headColor.r, headColor.g, headColor.b, headColor.a);
	SDL_RenderFillRect(renderer, &Head());
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

void Snake::ProcessInput() noexcept
{
	Vector2 newDirection{ Vector2::zero() };
	if (Input::GetKey(SDL_Scancode::SDL_SCANCODE_LEFT))
	{
		newDirection = Vector2::left();
	}
	else if (Input::GetKey(SDL_Scancode::SDL_SCANCODE_RIGHT))
	{
		newDirection = Vector2::right();
	}
	else if (Input::GetKey(SDL_Scancode::SDL_SCANCODE_UP))
	{
		newDirection = Vector2::down();
	}
	else if (Input::GetKey(SDL_Scancode::SDL_SCANCODE_DOWN))
	{
		newDirection = Vector2::up();
	}

	// Change the snake's direction. Fails if the direction wouldn't change or if it would completely turn around.
	if (newDirection == Vector2::zero()
		|| newDirection == this->m_direction
		|| newDirection == -this->m_direction)
	{
		return;
	}

	this->m_direction = newDirection;

	// Snap the head to the grid and updaate the head and body.
	m_position /= m_size;
	m_position.x = std::roundf(m_position.x);
	m_position.y = std::roundf(m_position.y);
	m_position *= m_size;

	UpdateHead();
	UpdateBody();

	// Move the head by an amount that will ensure that the snake can never collide with itself when performing a U-turn.
	m_position += m_size * 0.5f * m_direction;
}

// Update the head: round the floating position.
void Snake::UpdateHead() noexcept
{
	auto& head = m_head();
	head.x = std::roundf(m_position.x);
	head.y = std::roundf(m_position.y);
}

void Snake::UpdateBody() noexcept
{
	const auto head{ Head() };
	if (head.x % m_size == 0
		&& head.y % m_size == 0)
	{
		const auto secondBodyPart{ BodyPartAt(1) };
		if (secondBodyPart.x != head.x
			|| secondBodyPart.y != head.y)
		{
			m_bodyParts.pop_back();
			m_bodyParts.push_front(head);
		}
	}
}

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

size_t Snake::BodyPartsSize() const noexcept
{
    return m_bodyParts.size();
}

Vector2 Snake::GetPosition() const noexcept
{
    return m_position;
}
