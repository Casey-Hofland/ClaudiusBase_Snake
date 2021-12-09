#pragma once

#include <iostream>
#include "Apple.h"
#include "RenderManager.h"

//Constructor.
Apple::Apple()
{

}

void Apple::Initialize(int width, int height)
{
	color = { 0, 255, 0, 0 };
	rect = { 0, 0, width, height };
	position = { 100, 200 };
}

void Apple::Render(RenderManager& renderManager)
{
	renderManager.Render(rect, color, position);
}


