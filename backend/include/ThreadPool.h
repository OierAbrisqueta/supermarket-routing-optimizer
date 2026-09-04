#ifndef ROUTINGOPTIMIZER_THREADPOOL_H
#define ROUTINGOPTIMIZER_THREADPOOL_H

#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "Database.h"

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads, const std::string& dbPath);
    ~ThreadPool();

    void enqueueTask(std::function<void(Database&)> task);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void(Database&)>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;

    bool stop;
};

#endif //ROUTINGOPTIMIZER_THREADPOOL_H