#include <string>
#include <memory>
#include <optional>
#include "TimePoint.h"
#include "constants.h"

namespace WebVTT
{

    class Cue
    {
    public:
        static std::optional<Cue> collectTextAndSettings(std::u32string_view input, const char32_t *position);
        static std::optional<long> colectTimePoint(std::u32string_view input, const char32_t *positon);
        static std::optional<std::tuple<long, long>> colectTiming(std::u32string_view input, const char32_t *position);

    private:
        constexpr static int DEFAULT_CUE_SIZE = 100;
        std::u32string identifier;
        bool pauseOnExit = false;
        //Region region = null;
        WritingDIrection writingDirection = WritingDIrection::HORIZONTAL;
        bool snapToLines = true;
        //Line line = auto
        //Position position = auto
        Alignment positionAlignment = Alignment::AUTO;
        Alignment lineAlignment = Alignment::START_ALIGNMENT;
        Alignment textAlignment = Alignment::CENTER_ALIGNMENT;
        uint64_t size = DEFAULT_CUE_SIZE;
        std::u32string text;
    };
}; // namespace name
