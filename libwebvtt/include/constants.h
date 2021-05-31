

namespace WebVTT
{

    enum class WritingDIrection
    {
        HORIZONTAL,
        VERTICAL
    };
    enum class Alignment
    {
        AUTO,
        START_ALIGNMENT,
        CENTER_ALIGNMENT
    };

    enum SPECIAL_CHARACTER
    {
        NULL_C = 0x0000,
        REPLACEMENT_C = 0xFFFD,
        CR_C = 0x000D,
        LF_C = 0x000A,
        SPACE_C = 0x0020,
        TAB_C = 0x0009,
        HYPEN_MINUS = 0x002D,
        HYPEN_GREATHER = 0x003E,
        COLON = 0x003A, 
        FULL_STOP = 0x002E
    };

    enum class TimeUnit
    {
        HOURS,
        MINUTES,
        SECONDS
    };

};
