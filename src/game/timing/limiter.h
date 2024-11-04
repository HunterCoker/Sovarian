#pragma once

#include "timeit.h"
#include "literals.h"
#include "platform/sleep.h"

#include <cassert>

namespace timing {

class limiter {
public:
    static void setTargetFps(uint32_t targetFps)
    {
        _M_prevTick = PerfCounter();
        _M_frequency = PerfFrequency();
        _M_targetFrameTicks = _M_frequency / targetFps;
        _M_targetSecPerFrame = static_cast<double>(_M_targetFrameTicks) / _M_frequency;
    }

    static void wait()
    {
        assert(_M_targetFrameTicks != 0u);
        uint64_t currTick;
        uint64_t elapsedTicks;

        /*
         * repeatedly sleeps the main thread for 1ms until 20ms away
         * from the target frame ticks, then finishes with busy waiting
         */
        while (true) {
            currTick = PerfCounter();
            elapsedTicks = currTick - _M_prevTick;

            if (elapsedTicks >= _M_targetFrameTicks) {
                _M_prevTick = currTick;
                break;
            }

            if (_M_targetFrameTicks - elapsedTicks < 20u * _M_frequency)
            {
                SleepInMs(1u);
            }
        }
    }

    static inline double dt()
    {
        return _M_targetSecPerFrame;
    }
private:
    static uint64_t _M_prevTick;
    static uint64_t _M_frequency;
    static uint64_t _M_targetFrameTicks;
    static double _M_targetSecPerFrame;
};

uint64_t limiter::_M_prevTick = 0u;
uint64_t limiter::_M_frequency = 0u;
uint64_t limiter::_M_targetFrameTicks = 0u;
double limiter::_M_targetSecPerFrame = 0.0;

}  // timing
