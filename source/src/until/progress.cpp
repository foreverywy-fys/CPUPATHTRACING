#include "until/progress.hpp"
#include <iostream>

Progress::Progress(size_t total, size_t step) : total(total), current(0), percent(0), last_percent(0), step(step) 
{
    std::cout << "0%\n";
}

void Progress::update(size_t count)
{
    Guard guard(spin_lock);
    current += count;
    percent = static_cast<int>(100.0 * static_cast<double>(current) / static_cast<double>(total));
    if ((percent - last_percent >= step) || percent == 100)
    {
        last_percent = percent;
        std::cout << percent << "%\n";
    }
}
