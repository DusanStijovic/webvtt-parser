#include <Semaphore.h>

void Semaphore::release()
{
    std::unique_lock<std::mutex> lock(mutex);
    value += 1;
    cv.notify_one();
}
void Semaphore::acquire()
{
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]()
            { return value != 0; });
    value -= 1;
}