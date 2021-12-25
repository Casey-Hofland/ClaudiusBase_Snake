#pragma once

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

#include <queue>
#include "Vector2.h"
#include "Input.h"

class Snake
{
private:
	int m_size{};
	Vector2 m_direction{};
	Vector2 m_position{};
	std::deque<SDL_Rect> m_bodyParts{ minimumBodyParts };

	// Member functions
	void ProcessInput() noexcept;	// Noexcept is implicit: ignore compiler warnings on BodyPartAt(1), BodyPartAt(BodyPartsSize() - 2), and bodyParts.push_front() right after bodyParts.pop_back().
	void UpdateHead() noexcept;		// See above.
	void UpdateBody() noexcept;		// See above.
	void UpdateTail() noexcept;		// See above.

	// Getters & Setters
	SDL_Rect& m_head() noexcept;
	SDL_Rect& m_tail() noexcept;
	SDL_Rect& m_bodyPartAt(size_t index);

public:
	static constexpr int minimumBodyParts{ 2 };

	int score{};
	float speed{ 10.0f };
	SDL_Color bodyColor{ SDL_MAX_UINT8 , 0, 0, SDL_MAX_UINT8 };
	SDL_Color headColor{ 0, SDL_MAX_UINT8, 0, SDL_MAX_UINT8 };

	// Constructors
	Snake(Vector2 position, int size, int bodyParts = minimumBodyParts);

	// Member functions
	void Update(float deltaTime) noexcept;
	void Render(SDL_Renderer* renderer) const noexcept;
	void Grow();
	void Shrink() noexcept;
	void SnapPositionToSize() noexcept;
	void ChangeDirection(Vector2 direction) noexcept;

	// Getters & Setters
	const SDL_Rect& Head() const noexcept;
	const SDL_Rect& Tail() const noexcept;
	const SDL_Rect& BodyPartAt(size_t index) const;
	size_t BodyPartsSize() const noexcept;
	int GetSize() const noexcept;
	void SetSize(int size) noexcept;
	Vector2 GetDirection() const noexcept;
	void SetDirection(Vector2 direction) noexcept;
	Vector2 GetPosition() const noexcept;
	void SetPosition(Vector2 position) noexcept;
};
