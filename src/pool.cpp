#include "../include/pool.hpp"

ThreadPool::ThreadPool(int num_threads) : stop(false), workers(std::vector<pthread_t>(num_threads)) {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    for (auto& thread : workers) {
        pthread_create(&thread, NULL, Worker, this);
    }
}

ThreadPool::~ThreadPool() {
    pthread_mutex_lock(&mutex);
    stop = true;
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&cond);
    for (auto& thread : workers) {
        pthread_join(thread, NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

void* ThreadPool::Worker(void* arg) {
    ThreadPool* pool = static_cast<ThreadPool*>(arg);
    while (true) {
        pthread_mutex_lock(&pool->mutex);
        while (pool->tasks.empty() && !pool->stop) {
            pthread_cond_wait(&pool->cond, &pool->mutex);
        }
        if (pool->stop && pool->tasks.empty()) {
            pthread_mutex_unlock(&pool->mutex);
            return NULL;
        }
        auto task = std::move(pool->tasks.front());
        pool->tasks.pop();
        pthread_mutex_unlock(&pool->mutex);
        task();
    }
}

// template<typename Func, typename... Args>
// void ThreadPool::Enqueue(Func&& func, Args&&... args) {
//     auto task = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
//     pthread_mutex_lock(&mutex);
//     tasks.emplace(task);
//     pthread_mutex_unlock(&mutex);
//     pthread_cond_signal(&cond);
// }