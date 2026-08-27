#pragma once

#include <atomic>
#include <cstddef>
#include <functional>
#include <thread>
#include <vector>
#include <queue>
#include "thread/spin_lock.hpp"

class Task
{
public:
    virtual void run() = 0;
    virtual ~Task() = default;
};

class ThreadPool
{
public:
    static void WorkerThread(ThreadPool *master);
    ThreadPool(std::size_t thread_count = 0);
    ~ThreadPool();

    void addTask(Task *task);
    Task *getTask();

    void wait() const;
    void parallelFor(size_t width, size_t height, const std::function<void(size_t, size_t)> &lambda, bool complex = true);
private:
    std::atomic<int> alive;
    std::atomic<size_t> unfinished_tasks { 0 };
    std::vector<std::thread> threads;
    std::queue<Task*> tasks;
    SpinLock spin_lock {};
};

extern ThreadPool thread_pool;