#include "until/profile.hpp"
#include <chrono>
#include <iostream>

Profile::Profile(const std::string &name)
    : start(std::chrono::high_resolution_clock::now())
    , name(name)
{
}

Profile::~Profile()
{
    auto duration = std::chrono::high_resolution_clock::now() - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    std::cout << "Profile \"" << name << "\": " << ms << "ms\n";
}
