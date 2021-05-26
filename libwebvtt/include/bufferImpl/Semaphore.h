#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
    Semaphore() = default;
    Semaphore(int x) : value(x) {}
    void release();
    void acquire();

private:
    int value = 0;
    std::mutex mutex;
    std::condition_variable cv;
};

#endif