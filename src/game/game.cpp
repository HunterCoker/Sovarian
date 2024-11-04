#include "game.h"

#include <cassert>

game* game::_S_instance = nullptr;

struct game_state
{
    bool isRunning;
};

static game_state _S_gameState
{
    .isRunning = true,
};

game::game()
{

}

game::~game()
{
    assert(_S_instance != nullptr);
    delete _S_instance;
}

game& game::get() {
    if (!_S_instance)
        _S_instance = new game;
    return *_S_instance;
}

void game::update(double dt)
{

}

bool game::isRunning() const
{
    return _S_gameState.isRunning;
}