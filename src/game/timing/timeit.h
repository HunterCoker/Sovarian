#pragma once

#include <functional>

#ifdef DEBUG

#include <iostream>
#include <chrono>

namespace timing {

template <typename Func, typename... Args>
void timeit(Func func, Args&&... args)
{
    auto start = std::chrono::high_resolution_clock::now();

    func(std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "execution time: " << duration.count() << "us\n";
}

template <typename Func>
void timeit(Func func)
{
    auto start = std::chrono::high_resolution_clock::now();

    func();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "execution time: " << duration.count() << "us\n";
}

#else

namespace timing {

template <typename Func, typename... Args>
void timeit(Func func, Args&&... args)
{
    func(std::forward<Args>(args)...);
}

template <typename Func>
void timeit(Func func)
{
    func();
}

#endif  // DEBUG

}  // timing