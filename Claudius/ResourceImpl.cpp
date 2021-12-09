#include "ResourceImpl.h"

ResourceImpl::ResourceImpl(SDL_Renderer* renderer) : renderer(renderer) 
{
}

SDL_Texture* ResourceImpl::GetTexture(unsigned int id)
{
	if (id < textures.size())
		return textures[id].second;
	else
		return nullptr;
}