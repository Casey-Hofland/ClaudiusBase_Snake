#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

#include "RenderManager.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Sprite.h"
#include "Image.h"
#include "Input.h"
#include "Time.h"

#undef main

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Base", 0, 0, 0, 0, SDL_WindowFlags::SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		const char* error = SDL_GetError();
		return 0;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		const char* error = SDL_GetError();
		return 0;
	}
	bool running = true;
	
	RenderManager renderManager{ renderer };
	ResourceImpl resourceImpl(renderer);
	ResourceManager resourceManager(resourceImpl);
	Game game{};

	constexpr int width = 1250;
	constexpr int height = 700;
	const std::string title = "Snake";

	game.width = width;
	game.height = height;

	SDL_SetWindowSize(window, width, height);
	SDL_SetWindowTitle(window, title.c_str());
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	
	Time time{};
	while (running)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		time.Update();

		// Update the game
		game.Update(time.GetDeltaTime());

		// Render the game
		game.Render(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
