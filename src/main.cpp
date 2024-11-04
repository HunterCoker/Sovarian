#include "game/game.h"
#include "game/timing/limiter.h"

#include <iostream>

using namespace timing::literals;

int main( /* int argc, const char* argv[] */ ) {
    timing::limiter::setTargetFps(60_fps);
    game& sovarian = game::get();

    while (sovarian.isRunning())
    {
        double dt = timing::limiter::dt();
        sovarian.update(dt);

        timing::limiter::wait();
    }

    return 0;
}
