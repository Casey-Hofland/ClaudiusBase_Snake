#include "Game.h"
#include <stdexcept>
#include <ctime>
#include <numeric>
#include "Input.h"

#pragma region Constructors / Destructors
Game::Game(int gridSize, int columns, int rows)
	: gridSize{ gridSize }
	, columns{ columns }
	, rows{ rows }
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create the window and check that it was successfully created.
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GetWidth(), GetHeight(), SDL_WindowFlags::SDL_WINDOW_SHOWN);
	if (window == nullptr) 
	{
		throw std::invalid_argument("Could not create window: " + std::string(SDL_GetError()) + ".\n");
	}

	// Create the renderer and check that it was successfully created.
	renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		throw std::invalid_argument("Could not create renderer: " + std::string(SDL_GetError()) + ".\n");
	}

	// Initialize random with a time-based seed.
	std::srand(std::time(nullptr));

	// Setup the game.
	ResetSnake();
	ResetApple();
}

Game::~Game() noexcept
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
#pragma endregion

#pragma region Core Game functions
void Game::Update()
{
	// Update time.
	time.Update();
	const auto deltaTime = time.GetDeltaTime();
	
	// Update game objects.
	snake.Update(deltaTime);

	// Check snake collision.
	if (snake.IsSelfColliding()
		|| !InsideWindow(snake.Head()))
	{
		ResetSnake();
	}

	// Check apple collision.
	if (SDL_HasIntersection(&snake.Head(), &apple.rect))
	{
		snake.score++;
		snake.Grow();

		ResetApple();
	}
}

void Game::Render() const noexcept
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	snake.Render(renderer);
	apple.Render(renderer);

	SDL_RenderPresent(renderer);
}

void Game::ResetSnake()
{
	auto [snakeX, snakeY] = GetRandomUniqueGridPosition();
	snake = { Vector2{static_cast<float>(snakeX), static_cast<float>(snakeY)}, gridSize, 10 };
}

void Game::ResetApple()
{
	auto [appleX, appleY] = GetRandomUniqueGridPosition();
	apple = { appleX, appleY, gridSize };
}
#pragma endregion

#pragma region Grid functions
std::tuple<int, int> Game::GetRandomUniqueGridIndex() const
{
	std::vector<int> columns(GetColumns());
	std::iota(columns.begin(), columns.end(), 0);

	for (size_t i = columns.size(); i > 0; i--)
	{
		const int columnIndex = std::rand() % i;
		const int column = columns.at(columnIndex);

		std::vector<int> rows(GetRows());
		std::iota(rows.begin(), rows.end(), 0);

		for (size_t j = rows.size(); j > 0; j--)
		{
			const int rowIndex = std::rand() % j;
			const int row = rows.at(rowIndex);

			if (GridIndexIsEmpty(column, row))
			{
				return std::make_tuple(column, row);
			}

			rows.erase(rows.begin() + rowIndex);
		}

		columns.erase(columns.begin() + columnIndex);
	}

	return std::make_tuple(-1, -1);
}

std::tuple<int, int> Game::GetRandomUniqueGridPosition() const
{
	auto gridIndexTuple = GetRandomUniqueGridIndex();

	auto [column, row] = gridIndexTuple;
	if (column == -1 && row == -1)
	{
		return gridIndexTuple;
	}

	return GridIndexToPosition(column, row);
}

std::tuple<int, int> Game::GetRandomGridIndex() const noexcept
{
	const int column = std::rand() % GetColumns();
	const int row = std::rand() % GetRows();

	return std::make_tuple(column, row);
}

std::tuple<int, int> Game::GetRandomGridPosition() const noexcept
{
	auto [column, row] = GetRandomGridIndex();
	return GridIndexToPosition(column, row);
}

std::tuple<int, int> Game::GridIndexToPosition(int column, int row) const noexcept
{
	const unsigned int gridSize = GetGridSize();
	return std::make_tuple(column * gridSize, row * gridSize);
}

std::tuple<int, int> Game::PositionToGridIndex(int x, int y) const noexcept
{
	const unsigned int gridSize = GetGridSize();
	return std::make_tuple(x / gridSize, y / gridSize);
}

bool Game::GridIndexIsEmpty(int column, int row) const noexcept
{
	auto [x, y] = GridIndexToPosition(column, row);

	for (const auto& bodyPart : snake.GetBodyParts())
	{
		if (bodyPart.x == x
			&& bodyPart.y == y)
		{
			return false;
		}
	}

	if (apple.rect.x == x
		&& apple.rect.y == y)
	{
		return false;
	}

	return true;
}

bool Game::InsideWindow(const SDL_Point& point) const noexcept
{
	SDL_Rect window{ 0, 0, GetWidth(), GetHeight() };
	return SDL_PointInRect(&point, &window);
}

bool Game::InsideWindow(const SDL_Rect& rect) const noexcept
{
	SDL_Point upperleft{ rect.x, rect.y };
	SDL_Point upperRight{ rect.x + std::max(rect.w - 1, 0), rect.y };
	SDL_Point bottomLeft{ rect.x, rect.y + std::max(rect.h - 1, 0) };
	// no need to check for bottom left: we already know the rect is inside the grid if these 3 points are.

	return InsideWindow(upperleft) 
		&& InsideWindow(upperRight) 
		&& InsideWindow(bottomLeft);
}
#pragma endregion

#pragma region Getters & Setters
int Game::GetGridSize() const noexcept
{
	return gridSize;
}

void Game::SetGridSize(int gridSize) noexcept
{
	this->gridSize = gridSize;
	snake.SetSize(gridSize);
	apple.rect.w = gridSize;
	apple.rect.h = gridSize;
}

int Game::GetColumns() const noexcept
{
	return columns;
}

void Game::SetColumns(int columns) noexcept
{
	this->columns = columns;
}

int Game::GetRows() const noexcept
{
	return rows;
}

void Game::SetRows(int rows) noexcept
{
	this->rows = rows;
}

int Game::GetWidth() const noexcept
{
	return GetGridSize() * GetColumns();
}

int Game::GetHeight() const noexcept
{
	return GetGridSize() * GetRows();
}

bool Game::IsPlaying() const noexcept
{
	return !Input::GetKey(SDL_Scancode::SDL_SCANCODE_ESCAPE);
}
#pragma endregion
