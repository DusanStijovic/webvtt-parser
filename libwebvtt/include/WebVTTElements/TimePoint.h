#include <stdint.h>

namespace WebVTT
{

    class TimePoint
    {
    private:
        uint8_t hours;
        uint8_t minutes;
        uint8_t seconds;
        uint32_t miliseconds;

        TimePoint(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t milliseconds)
        {
            this->hours = hours;
            this->minutes = minutes;
            this->seconds = seconds;
            this->miliseconds = milliseconds;
        }
    };
}