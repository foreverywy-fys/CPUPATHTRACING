#include "renderer/base_renderer.hpp"
#include "thread/thread_pool.hpp"
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
#include "until/progress.hpp"
#include "until/profile.hpp"


void BaseRenderer::render(size_t spp, const std::filesystem::path &filename)
{
    PROFILE("Renderer " + std::to_string(spp) + "spp " + filename.string());
    size_t current_spp = 0;
    size_t increase = 1;
    auto &film = camera.getFilm();
    film.clear();
    Progress progress(film.getWidth() * film.getHeight() * spp, 20);
    while (current_spp < spp)
    {
        thread_pool.parallelFor(film.getWidth(), film.getHeight(), [&](size_t x, size_t y)-> void
        {
            for (size_t i = 0; i < increase; i++)
            {
                film.addSample(x, y, renderPixel({ x, y, current_spp + i }));
            }
            progress.update(increase);
        });
        thread_pool.wait();
        current_spp += increase;
        increase = std::min<size_t>(current_spp, 32);
        film.save(filename);
        std::cout << current_spp << "spp has been saved to " << filename << std::endl;
    }  
}
