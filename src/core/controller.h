#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game.h"

template <typename EventType>
class BaseController
{
public:
    virtual void draw() noexcept = 0;
    virtual void logic() noexcept = 0;
    virtual void move(EventType event) noexcept = 0;

protected:
    Game game;
};

#endif //CONTROLLER_H
