#include "Sprite.h"

Sprite::Sprite() : source(), color(), image()
{
}

Sprite::Sprite(const Sprite& rhs) : source(rhs.source), color(rhs.color), image(rhs.image)
{
}

Sprite::Sprite(Image& image) 
	: source{ 0, 0, 0, 0 }
	, color{ 0, 0, 0, 0 }
	, image(&image)
{
}

Sprite::Sprite(SDL_Rect source, SDL_Color color, Image& image) : source(source), color(color), image(&image)
{
}

Sprite::Sprite(int x, int y, int w, int h, SDL_Color color, Image& image) 
	: source{ x,y,w,h }
	, color(color)
	, image(&image)
{
}

Sprite::Sprite(SDL_Rect source, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Image& image)
	: source(source)
	, color{ r, g, b, a }
	, image(&image)
{
}

Sprite::Sprite(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Image& image)
	: source{ x,y,w,h }
	, color{ r, g, b, a }
	, image(&image)
{
}

void Sprite::SetImage(Image& image)
{
	this->image = &image;
}

void Sprite::SetSource(int x, int y, int w, int h)
{
	source = { x, y, w, h };
}

void Sprite::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color = { r, g, b, a };
}
