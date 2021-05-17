#include "SyncBuffer.h"

void SyncBuffer::writeTo(int x)
{
    m_free.acquire();
    {
        std::lock_guard<std::mutex> l(mutex);
        buffer[m_w] = x;
        m_w = m_w % 10 == 0 ? 0 : m_w + 1;
    }
    m_taken.release();
}
int SyncBuffer::readFrom()
{
    int res = -1;
    m_taken.acquire();
    {
        std::lock_guard<std::mutex> l(mutex);
        res = buffer[m_r];
        m_r = m_r % 10 == 0 ? 0 : m_r + 1;
    }
    m_free.release();
    return res;
}