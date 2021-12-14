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
	
	RenderManager renderManager;
	ResourceImpl resourceImpl(renderer);
	ResourceManager resourceManager(resourceImpl);
	Game game{};

	int width = 500;
	int height = 500;
	std::string title = "";
	game.Enter(width, height, title);
	SDL_SetWindowSize(window, width, height);
	SDL_SetWindowTitle(window, title.c_str());
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	
	Uint64 now{ SDL_GetPerformanceCounter() };
	Uint64 last{};
	float deltaTime{};
	while (running)
	{
		// Calculate deltaTime
		last = now;
		now = SDL_GetPerformanceCounter();

		deltaTime = ((now - last) * 1000.0f / SDL_GetPerformanceFrequency()) * 0.01f;

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_EventType::SDL_QUIT: running = false; break;
			case SDL_EventType::SDL_KEYDOWN: game.OnKeyDown(e.key.keysym.sym); break;
			case SDL_EventType::SDL_KEYUP: game.OnKeyUp(e.key.keysym.sym); break;
			}
		}

		game.Update(deltaTime);
		game.Render(renderManager);

		SDL_SetRenderDrawColor(renderer,0,0,0,0);
		SDL_RenderClear(renderer);
		for (auto &&entry : renderManager.spriteEntries)
		{
			if (entry.sprite.image != nullptr)
			{
				SDL_Rect src{ entry.sprite.source.x, entry.sprite.source.y, entry.sprite.source.w, entry.sprite.source.h };
				SDL_Rect dst{ static_cast<int>(entry.position.x),
							  static_cast<int>(entry.position.y),
							  static_cast<int>(entry.sprite.image->width),
							  static_cast<int>(entry.sprite.image->height) };
				SDL_RenderCopy(renderer, resourceImpl.GetTexture(entry.sprite.image->id), &src, &dst);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, entry.sprite.color.r, entry.sprite.color.g, entry.sprite.color.b, entry.sprite.color.a);
				SDL_Rect rect{ static_cast<int>(entry.position.x),
							   static_cast<int>(entry.position.y),
							   entry.sprite.source.w,
							   entry.sprite.source.h };
				SDL_RenderDrawRect(renderer, &rect);
			}
		}
		for (auto&& entry : renderManager.rectEntries)
		{
			SDL_SetRenderDrawColor(renderer, entry.color.r, entry.color.g, entry.color.b, entry.color.a);
			SDL_Rect rect{ static_cast<int>(entry.position.x),
						   static_cast<int>(entry.position.y),
						   entry.rect.w,
						   entry.rect.h };
			//SDL_RenderDrawRect(renderer, &rect);	// <- If you want to draw the "outline" of the rectangle.
			SDL_RenderFillRect(renderer, &rect);  // <- If you want to draw a "filled" rectangle. 
		}
		SDL_RenderPresent(renderer);
		renderManager.Clear();
		SDL_Delay(1000 / 20); //<- "Framerate".
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
