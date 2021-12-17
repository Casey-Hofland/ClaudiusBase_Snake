#pragma once
class Grid
{
public:
	unsigned int width{ 10 };
	unsigned int height{ 10 };
	unsigned int scale{ 30 };

	Grid() = default;
	Grid(unsigned int width, unsigned int height);
	Grid(unsigned int width, unsigned int height, unsigned int scale);
};

