#include "game/game.h"

#include "game/timing/timer.h"

#include <thread>
#include <iostream>

int main(int argc, const char* argv[]) {
    timer::start(60);

    // auto& sovarian = game::get();

    while (true) {
        timer::tick();

        if (timer::lastFrameDuration < timer::targetFrameDuration) {
            std::this_thread::sleep_for(
                timer::targetFrameDuration - timer::lastFrameDuration);
        } else {
            std::cout << timer::lastFrameDuration.count() << std::endl;
        }
    }

    return 0;
}