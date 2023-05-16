#ifndef POOL_HPP
#define POOL_HPP

#include <pthread.h>
#include <vector>
#include <queue>
#include <functional>

class ThreadPool {
public:
    ThreadPool(int num_threads);
    ~ThreadPool();
    template<typename Func, typename... Args>
    void Enqueue(Func&& func, Args&&... args) {
        auto task = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
        pthread_mutex_lock(&mutex);
        tasks.emplace(task);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }

private:
    static void* Worker(void* arg);
    std::vector<pthread_t> workers;
    std::queue<std::function<void()>> tasks;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool stop;
};

#endif

