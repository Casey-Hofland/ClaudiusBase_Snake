#pragma once

#include <vector>
#include "Vector2.h"

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

struct Sprite;

struct RenderManager
{
public:
	SDL_Renderer* renderer;

	struct SpriteEntry
	{
		const Sprite& sprite;
		const Vector2& position;
	};

	struct RectEntry
	{
		const SDL_Rect& rect;
		const SDL_Color& color;
		const Vector2& position;
	};

	RenderManager(SDL_Renderer* renderer) noexcept;

	void Render(const Sprite& sprite, const Vector2& position);
	void Render(const SDL_Rect& rect, const SDL_Color& color, const Vector2& position);
	void Clear();

	std::vector<SpriteEntry> spriteEntries;
	std::vector<RectEntry> rectEntries;
};
