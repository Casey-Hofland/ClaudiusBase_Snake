#pragma once

#include <vector>

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

struct Sprite;
struct Transform;

struct RenderManager
{
	struct SpriteEntry
	{
		const Sprite& sprite;
		const Transform& trans;
	};

	struct RectEntry
	{
		const SDL_Rect& rect;
		const SDL_Color& color;
		const Transform& trans;
	};


	void Render(const Sprite& sprite, const Transform& trans);
	void Render(const SDL_Rect& rect, const SDL_Color& color, const Transform& trans);
	void Clear();

	std::vector<SpriteEntry> spriteEntries;
	std::vector<RectEntry> rectEntries;
};
