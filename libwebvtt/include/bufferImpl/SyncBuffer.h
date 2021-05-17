#include "Semaphore.h"
#include <vector>
#include <mutex>

class SyncBuffer
{
public:
    void writeTo(int x);
    int readFrom();

private:
    std::vector<uint32_t> buffer;

    int m_w = 0;
    int m_r = 0;
    Semaphore m_taken{0};
    Semaphore m_free{0};
    std::mutex mutex;
};
