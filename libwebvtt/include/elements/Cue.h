#ifndef WEBVTT_CUE_H
#define WEBVTT_CUE_H

#include <string>
#include <memory>
#include <optional>
#include <utility>
#include "TimePoint.h"
#include "constants.h"
#include "Block.h"

namespace WebVTT
{

    class Cue : public Block
    {
    public:
        constexpr static int DEFAULT_CUE_SIZE = 100;
        constexpr static std::u32string_view REGION = U"region";
        constexpr static std::u32string_view VERTICAL = U"vertical";
        constexpr static std::u32string_view LINE = U"line";
        constexpr static std::u32string_view POSITION = U"position";
        constexpr static std::u32string_view SIZE = U"size";
        constexpr static std::u32string_view ALIGN = U"align";

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

        enum class TimeUnit
        {
            HOURS,
            MINUTES,
            SECONDS
        };

        explicit Cue(std::u32string identifier) : identifier(std::move(identifier)){};

        void setText(std::u32string text)
        {
            this->text = std::move(text);
        }
        void setStartTime(long startTime)
        {
            this->startTime = startTime;
        }
        void setEndTime(long endTime)
        {
            this->endTime = endTime;
        }

    private:
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
        uint32_t startTime, endTime;
    };
}; // namespace name

#endif