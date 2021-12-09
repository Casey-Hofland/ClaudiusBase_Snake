#include "RenderManager.h"

void RenderManager::Render(const Sprite& sprite, const Vector2& position)
{
	spriteEntries.push_back({ sprite, position });
}

void RenderManager::Render(const SDL_Rect& rect, const SDL_Color& color, const Vector2& position)
{
	rectEntries.push_back({ rect, color, position });
}

void RenderManager::Clear()
{
	spriteEntries.clear();
	rectEntries.clear();
}