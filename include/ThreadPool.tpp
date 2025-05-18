// 提交任务函数模板实现
// Template implementation for task submission
// 支持任意参数和返回值的可调用对象（如函数、lambda）
// Supports any callable with parameters and return value
template<class F, class... Args>
auto ThreadPool::submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    using return_type = decltype(f(args...)); // 推导返回值类型
                                            // Deduce return type

    // 使用 packaged_task 包装任务，以支持 future
    // Use packaged_task to wrap the function for future support
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future(); // 获取 future
                                                      // Get future for result
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (stop) throw std::runtime_error("submit on stopped ThreadPool"); // 防止提交到已关闭的池
                                                                            // Disallow submission after stop
        tasks.emplace([task]() { (*task)(); }); // 添加任务到队列
                                             // Add task to queue
    }
    condition.notify_one(); // 唤醒一个等待线程
                           // Notify one waiting thread
    return res;
}