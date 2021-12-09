#pragma once

#include <string>
#include "ResourceImpl.h"
#include "Image.h"

struct Sound;

struct ResourceManager
{
	ResourceManager(ResourceImpl& impl);
	
	bool LoadImageFromFile(Image& image, const std::string &filePath);
	bool LoadSoundFromFile(Sound& sound, const std::string &filePath); // TODO
private:
	ResourceImpl& impl;
};
