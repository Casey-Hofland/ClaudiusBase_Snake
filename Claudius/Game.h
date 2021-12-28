#pragma once

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

#include <string>
#include <vector>
#include "Apple.h"
#include "Snake.h"
#include "Time.h"

class Game
{
private:
	unsigned int gridSize{};
	unsigned int columns{};
	unsigned int rows{};

	Snake snake{ -Vector2::one(), 0, 0 };
	Apple apple{ -1, -1, 0 };

	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Game(unsigned int gridSize, unsigned int columns, unsigned int rows);
	virtual ~Game() noexcept;

	Game(const Game&) = default;
	Game(Game&&) = default;
	Game& operator=(const Game&) = default;
	Game& operator=(Game&&) = default;

	void Update(float deltaTime);
	void Render() const noexcept;

	std::tuple<unsigned int, unsigned int> GetRandomUniqueGridIndex() const;
	std::tuple<unsigned int, unsigned int> GetRandomUniqueGridPosition() const;
	std::tuple<unsigned int, unsigned int> GetRandomGridIndex() const noexcept;
	std::tuple<unsigned int, unsigned int> GetRandomGridPosition() const noexcept;

	std::tuple<unsigned int, unsigned int> GridIndexToPosition(unsigned int column, unsigned int row) const noexcept;
	std::tuple<unsigned int, unsigned int> PositionToGridIndex(unsigned int x, unsigned int y) const noexcept;

	bool GridIndexIsEmpty(unsigned int column, unsigned int row) const noexcept;

	unsigned int GetGridSize() const noexcept;
	void SetGridSize(unsigned int gridSize) noexcept;
	unsigned int GetColumns() const noexcept;
	void SetColumns(unsigned int columns) noexcept;
	unsigned int GetRows() const noexcept;
	void SetRows(unsigned int rows) noexcept;

	unsigned int GetWidth() const noexcept;
	unsigned int GetHeight() const noexcept;
};
