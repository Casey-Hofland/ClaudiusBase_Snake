#include "Grid.h"

Grid::Grid(unsigned int width, unsigned int height)
    : Grid(width, height, scale)
{
}

Grid::Grid(unsigned int width, unsigned int height, unsigned int scale)
    : width{width}
    , height{ height }
    , scale{ scale }
{
}