#include "Game.h"
#include <stdexcept>
#include <ctime>
#include <numeric>

#pragma region Constructors / Destructors
Game::Game(int gridSize, int columns, int rows)
	: m_gridSize{ gridSize }
	, m_columns{ columns }
	, m_rows{ rows }
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create the window and check that it was successfully created.
	m_window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GetWidth(), GetHeight(), SDL_WindowFlags::SDL_WINDOW_SHOWN);
	if (m_window == nullptr) 
	{
		throw std::invalid_argument("Could not create window: " + std::string(SDL_GetError()) + ".\n");
	}

	// Create the renderer and check that it was successfully created.
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::invalid_argument("Could not create renderer: " + std::string(SDL_GetError()) + ".\n");
	}

	// Initialize random with a time-based seed.
	[[gsl::suppress(type.1, justification : "We know the static_cast is safe (warning thrown because of an arithmetic conversion).")]]
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Setup the game.
	ResetSnake();
	ResetApple();
}

Game::~Game() noexcept
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
#pragma endregion

#pragma region Core Game functions
void Game::Update()
{
	// Update systems.
	m_time.Update();
	m_input.ProcessInput();

	// Update game objects.
	const auto deltaTime = m_time.GetDeltaTime();
	TurnSnake();
	m_snake.Update(deltaTime);

	// Check snake collision.
	if (m_snake.IsSelfColliding()
		|| !InsideWindow(m_snake.Head()))
	{
		ResetSnake();
	}

	// Check apple collision.
	if (SDL_HasIntersection(&m_snake.Head(), &m_apple.rect))
	{
		m_snake.score++;
		m_snake.Grow();
		m_snake.speed *= 1.05f;

		ResetApple();
	}
}

void Game::Render() const noexcept
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);

	m_snake.Render(m_renderer);
	m_apple.Render(m_renderer);

	SDL_RenderPresent(m_renderer);
}

void Game::ResetSnake()
{
	auto [snakeX, snakeY] = GetRandomUniqueGridPosition();
	m_snake = { Vector2{static_cast<float>(snakeX), static_cast<float>(snakeY)}, m_gridSize, 10 };
}

void Game::ResetApple()
{
	auto [appleX, appleY] = GetRandomUniqueGridPosition();
	m_apple = { appleX, appleY, m_gridSize };
}

void Game::TurnSnake() noexcept
{
	if (m_input.GetKeyDown(SDL_Scancode::SDL_SCANCODE_LEFT))
	{
		m_snake.ChangeDirection(Vector2::left());
	}
	else if (m_input.GetKeyDown(SDL_Scancode::SDL_SCANCODE_RIGHT))
	{
		m_snake.ChangeDirection(Vector2::right());
	}
	else if (m_input.GetKeyDown(SDL_Scancode::SDL_SCANCODE_UP))
	{
		m_snake.ChangeDirection(Vector2::down());
	}
	else if (m_input.GetKeyDown(SDL_Scancode::SDL_SCANCODE_DOWN))
	{
		m_snake.ChangeDirection(Vector2::up());
	}
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

	for (const auto& bodyPart : m_snake.GetBodyParts())
	{
		if (bodyPart.x == x
			&& bodyPart.y == y)
		{
			return false;
		}
	}

	if (m_apple.rect.x == x
		&& m_apple.rect.y == y)
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
	return m_gridSize;
}

void Game::SetGridSize(int gridSize) noexcept
{
	this->m_gridSize = gridSize;
	m_snake.SetSize(gridSize);
	m_apple.rect.w = gridSize;
	m_apple.rect.h = gridSize;
}

int Game::GetColumns() const noexcept
{
	return m_columns;
}

void Game::SetColumns(int columns) noexcept
{
	this->m_columns = columns;
}

int Game::GetRows() const noexcept
{
	return m_rows;
}

void Game::SetRows(int rows) noexcept
{
	this->m_rows = rows;
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
	return !m_input.GetKey(SDL_Scancode::SDL_SCANCODE_ESCAPE);
}
#pragma endregion
