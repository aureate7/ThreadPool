#include "ThreadPool.h"
#include <iostream>

int main() {
    ThreadPool pool(4); // 创建线程池，4个工作线程
                        // Create thread pool with 4 workers

    // 提交一个耗时任务（模拟计算）
    // Submit a long task (simulate workload)
    auto future1 = pool.submit([]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 42;
    });

    // 提交一个带参数任务
    // Submit a task with parameters
    auto future2 = pool.submit([](int a, int b) {
        return a + b;
    }, 5, 7);

    // 输出结果
    // Print results
    std::cout << "future1: " << future1.get() << std::endl; // 输出 42
    std::cout << "future2: " << future2.get() << std::endl; // 输出 12

    return 0;
}
