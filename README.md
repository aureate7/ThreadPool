# ThreadPool (C++11)

A simple yet functional C++11 thread pool implementation.

## 📌 Features

- ✅ Fixed-size thread pool with configurable worker count
- ✅ Task submission with arbitrary parameters
- ✅ Future-based result retrieval (`std::future`)
- ✅ Thread-safe task queue
- ✅ Graceful shutdown

## 🛠️ Build Instructions

### Requirements

- CMake >= 3.10
- C++11-compatible compiler (e.g. `g++`, `clang++`)

### Compile

```bash
mkdir build && cd build
cmake ..
make
```

### Run
```bash
./ThreadPoolTest
```

### Example
```cpp
ThreadPool pool(4); // Create a thread pool with 4 threads

// Submit a long-running task
auto result1 = pool.submit([]() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 42;
});

// Submit a task with arguments
auto result2 = pool.submit([](int a, int b) {
    return a + b;
}, 5, 7);

// Wait for results
std::cout << result1.get() << std::endl; // Output: 42
std::cout << result2.get() << std::endl; // Output: 12
```

### Project Structure
```bash
ThreadPool/
├── include/
│   ├── ThreadPool.h        # Thread pool class definition
│   └── ThreadPool.tpp      # Task submission template implementation
├── src/
│   └── ThreadPool.cpp      # Core logic and thread management
├── test/
│   └── main.cpp            # Demonstration and test cases
├── CMakeLists.txt
└── README.md
```