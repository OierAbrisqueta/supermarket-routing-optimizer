#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads, const std::string& dbPath) {
    this->stop = false;

    for (auto i{0}; i < numThreads; i++) {
        this->workers.emplace_back([this, dbPath]() {
            Database thread_private_db(dbPath);

            while (true) {
                std::function<void(Database&)> task;
                {
                    std::unique_lock<std::mutex> lock(this->queueMutex);

                    this->condition.wait(lock, [this]() {
                        return this->stop || !this->tasks.empty();
                    });

                    if (this->stop && this->tasks.empty()) {
                        return;
                    }

                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }

                task(thread_private_db);
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }

    condition.notify_all();

    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::enqueueTask(std::function<void(Database&)> task) {
    {
        std::lock_guard<std::mutex> lock(this->queueMutex);
        this->tasks.push(task);
    }

    this->condition.notify_one();
}