#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>

// 简易线程池类定义
// Simple thread pool class definition
class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads); // 构造函数，指定线程数量
                                            // Constructor: specify number of threads
    ~ThreadPool(); // 析构函数，关闭线程池
                   // Destructor: cleanly shutdown the pool

    // 提交任务，支持任意可调用对象，返回 future
    // Submit task to the pool, supports any callable, returns future
    template<class F, class... Args>
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;

private:
    std::vector<std::thread> workers; // 工作线程列表
                                     // Worker threads
    std::queue<std::function<void()>> tasks; // 任务队列
                                           // Task queue

    std::mutex queueMutex; // 队列互斥锁
                           // Mutex for task queue
    std::condition_variable condition; // 条件变量用于唤醒
                                       // Condition variable for wakeup
    std::atomic<bool> stop; // 线程池停止标志
                             // Stop signal
};

#include "ThreadPool.tpp"