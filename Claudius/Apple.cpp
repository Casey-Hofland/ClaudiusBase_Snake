#pragma once

#include <iostream>
#include "Apple.h"
#include "RenderManager.h"

Apple::Apple(int width, int height)
	: position{ 100.0f, 200.0f }
	, rect{ 100, 200, width, height }
{
}

void Apple::Render(RenderManager& renderManager)
{
	renderManager.Render(rect, color, position);
}
