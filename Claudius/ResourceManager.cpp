#include "ResourceManager.h"

bool ResourceManager::LoadImageFromFile(Image& image, const std::string& filePath)
{
	auto it = impl.textures.begin();
	unsigned int index = 0;
	while (it != impl.textures.end())
	{
		if ((*it).first == filePath)
		{
			image.id = index;
			return true;
		}
		it++;
		index++;
	}
	SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
	if (surface != nullptr)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(impl.renderer, surface);
		if (texture != nullptr)
		{
			impl.textures.push_back(std::pair<std::string, SDL_Texture*>(filePath, texture));
			image.id = static_cast<unsigned int>(impl.textures.size() - 1);
			image.width = surface->w;
			image.height = surface->h;
			return true;
		}
		else
		{
			const char* error = SDL_GetError();
			return false;
		}
	}
	else
	{
		const char* error = SDL_GetError();
		return false;
	}
	return false;
};