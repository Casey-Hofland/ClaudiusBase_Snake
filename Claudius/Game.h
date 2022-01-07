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
#include "Input.h"

class Game
{
private:
	int m_gridSize{};
	int m_columns{};
	int m_rows{};

	Snake m_snake{ -Vector2::one(), 0, 0 };
	Apple m_apple{ -1, -1, 0 };

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	Time m_time{};
	Input m_input{};

	void ResetSnake();
	void ResetApple();
	void TurnSnake() noexcept;

public:
	Game(int gridSize, int columns, int rows);
	virtual ~Game() noexcept;

	Game(const Game&) = default;
	Game(Game&&) = default;
	Game& operator=(const Game&) = default;
	Game& operator=(Game&&) = default;

	void Update();
	void Render() const noexcept;

	std::tuple<int, int> GetRandomUniqueGridIndex() const;
	std::tuple<int, int> GetRandomUniqueGridPosition() const;
	std::tuple<int, int> GetRandomGridIndex() const noexcept;
	std::tuple<int, int> GetRandomGridPosition() const noexcept;

	std::tuple<int, int> GridIndexToPosition(int column, int row) const noexcept;
	std::tuple<int, int> PositionToGridIndex(int x, int y) const noexcept;

	bool GridIndexIsEmpty(int column, int row) const noexcept;
	bool InsideWindow(const SDL_Point& point) const noexcept;
	bool InsideWindow(const SDL_Rect& rect) const noexcept;

	int GetGridSize() const noexcept;
	void SetGridSize(int gridSize) noexcept;
	int GetColumns() const noexcept;
	void SetColumns(int columns) noexcept;
	int GetRows() const noexcept;
	void SetRows(int rows) noexcept;

	int GetWidth() const noexcept;
	int GetHeight() const noexcept;
	bool IsPlaying() const noexcept;
};
