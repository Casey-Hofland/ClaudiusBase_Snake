#pragma once

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

struct Image;

struct Sprite
{
	Sprite();
	Sprite(const Sprite& rhs);
	Sprite(Image& image);
	Sprite(SDL_Rect source, SDL_Color color, Image& image);
	Sprite(int x, int y, int w, int h, SDL_Color color, Image& image);
	Sprite(SDL_Rect source, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Image& image);
	Sprite(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Image& image);
	
	void SetImage(Image& image);
	void SetSource(int x, int y, int w, int h);
	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	SDL_Rect source;
	SDL_Color color;
	const Image* image;
};