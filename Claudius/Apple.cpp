#pragma once

#include <iostream>
#include "Apple.h"
#include "RenderManager.h"

Apple::Apple(int width, int height)
	: rect{ 0, 0, width, height }
{
}

void Apple::Render(RenderManager& renderManager)
{
	renderManager.Render(rect, color, position);
}
