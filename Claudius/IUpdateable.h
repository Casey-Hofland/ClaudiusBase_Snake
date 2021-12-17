#pragma once

#include "Game.h"

class IUpdateable
{
public:
    virtual ~IUpdateable() {}
    virtual void Update(const Game& game) = 0;
};

