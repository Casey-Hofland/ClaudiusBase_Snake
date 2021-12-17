#pragma once

#include "Game.h"

class IRenderable
{
public:
    virtual ~IRenderable() {}
    virtual void Render(const Game& game) const noexcept = 0;
};
