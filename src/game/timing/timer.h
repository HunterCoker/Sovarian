#pragma once

#include <chrono>

class timer {
public:
    using clock     = std::chrono::steady_clock;
    using micro    = std::chrono::microseconds;
public:
    static micro lastFrameDuration;
    static micro targetFrameDuration;
public:
    static void start(uint32_t targetFrameRate) {
        targetFrameDuration = micro(1'000'000 / targetFrameRate);
        _M_prev = clock::now();
    }

    static void tick() {
        _M_curr = clock::now();
        lastFrameDuration
            = std::chrono::duration_cast<micro>(_M_curr - _M_prev);
        _M_prev = _M_curr;
    }
private:
    static clock::time_point _M_curr, _M_prev;
};

timer::micro timer::lastFrameDuration   = timer::micro(0);
timer::micro timer::targetFrameDuration = timer::micro(0);
timer::clock::time_point timer::_M_prev = timer::clock::time_point::min();
timer::clock::time_point timer::_M_curr = timer::clock::time_point::min();
