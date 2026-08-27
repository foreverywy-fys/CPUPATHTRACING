#include "thread/thread_pool.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <functional>
#include <thread>

ThreadPool thread_pool {};

void ThreadPool::WorkerThread(ThreadPool *master)
{
    while (master->alive == 1) 
    {
        if (master->tasks.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            continue;
        }
        Task *task = master->getTask();
        if (task != nullptr)
        {
            task->run();
            delete task;
            master->unfinished_tasks.fetch_sub(1, std::memory_order_release);
        }
        else 
        {
            std::this_thread::yield();
        }
    }
}

ThreadPool::ThreadPool(std::size_t thread_count)
{
    alive = 1;
    unfinished_tasks = 0;
    if (thread_count == 0)
    {
        thread_count = std::thread::hardware_concurrency();
    }

    for (std::size_t i = 0; i < thread_count; ++i)
    {
        threads.push_back(std::thread(&ThreadPool::WorkerThread, this));
    }
}

ThreadPool::~ThreadPool()
{
    wait();
    alive = 0;
    for (auto& thread : threads)
    {
        thread.join();
    }

    threads.clear();
}

void ThreadPool::addTask(Task *task)
{
    Guard guard(spin_lock);
    tasks.push(task);
    unfinished_tasks.fetch_add(1, std::memory_order_release);
}

Task *ThreadPool::getTask()
{
    Guard guard(spin_lock);
    if (tasks.empty())
    {
        return nullptr;
    }
    Task *task = tasks.front();
    tasks.pop();
    return task;
}

void ThreadPool::wait() const
{
    while (unfinished_tasks.load(std::memory_order_acquire) != 0)
    {
        std::this_thread::yield();
    }
}

struct ParallelForTask : public Task
{
public:
    ParallelForTask(size_t x, size_t y, size_t chunk_width, size_t chunk_height, const std::function<void(size_t, size_t)> &lambda) : x(x), y(y), chunk_width(chunk_width), chunk_height(chunk_height), lambda(lambda) {}

    void run() override
    {
        for (size_t idx_x = 0; idx_x < chunk_width; idx_x++)
        {
            for (size_t idx_y = 0; idx_y < chunk_height; idx_y++)
            {
                lambda(idx_x + x, idx_y + y);
            }
        }
    }
private:
    size_t x, y;
    size_t chunk_width, chunk_height;

    std::function<void(size_t, size_t)> lambda;
};

void ThreadPool::parallelFor(size_t width, size_t height, const std::function<void(size_t, size_t)> &lambda, bool complex)
{
    Guard guard(spin_lock);

    const size_t worker_count = std::max<size_t>(threads.size(), 1);
    const double worker_grid = std::sqrt(static_cast<double>(worker_count));
    double chunk_width_float = static_cast<double>(width) / worker_grid;
    double chunk_height_float = static_cast<double>(height) / worker_grid;
    if (complex)
    {
        chunk_width_float /= 16;
        chunk_height_float /= 16;
    }
    const size_t chunk_width = std::max<size_t>(1, static_cast<size_t>(std::ceil(chunk_width_float)));
    const size_t chunk_height = std::max<size_t>(1, static_cast<size_t>(std::ceil(chunk_height_float)));

    for (size_t x = 0; x < width; x += chunk_width)
    {
        const size_t current_chunk_width = std::min(chunk_width, width - x);
        for (size_t y = 0; y < height; y += chunk_height)
        {
            const size_t current_chunk_height = std::min(chunk_height, height - y);
            tasks.push(new ParallelForTask(x, y, current_chunk_width, current_chunk_height, lambda));
            unfinished_tasks.fetch_add(1, std::memory_order_release);
        }
    }
}
