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
	//this->width = width;
	//this->height = height;
	color = { 0, 255, 0, 0 };
	rect = { 0, 0, width, height };
	trans.SetPosition(100, 200);
	//direction = { -0.05f, 0.05f };
}

void Apple::Render(RenderManager& renderManager)
{
	renderManager.Render(rect, color, trans);
}


