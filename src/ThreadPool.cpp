#include "ThreadPool.h"

// 构造函数：创建指定数量的工作线程
// Constructor: launch threads and keep them running
ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this]() {
            while (true) {
                std::function<void()> task;

                // 加锁等待任务队列非空或停止标志
                // Lock and wait until task available or stop requested
                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    condition.wait(lock, [this]() { return stop || !tasks.empty(); });
                    if (stop && tasks.empty()) return; // 若已停止且无任务，退出
                                                     // Exit if stopped and no tasks
                    task = std::move(tasks.front()); // 获取队首任务
                                                  // Get task from queue
                    tasks.pop();
                }

                task(); // 执行任务
                        // Execute task
            }
        });
    }
}

// 析构函数：设置停止标志并回收所有线程
// Destructor: signal stop and join all threads
ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all(); // 唤醒所有线程
                           // Notify all threads
    for (std::thread &worker : workers) {
        if (worker.joinable()) worker.join(); // 等待线程结束
                                            // Wait for thread to finish
    }
}
