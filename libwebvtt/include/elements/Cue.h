#ifndef WEBVTT_CUE_H
#define WEBVTT_CUE_H

#include <string>
#include <memory>
#include <optional>
#include <utility>
#include "TimePoint.h"
#include "constants.h"
#include "Block.h"
#include "Region.h"

namespace WebVTT {

    class Cue : public Block {
    public:
        constexpr static int DEFAULT_CUE_SIZE = 100;
        constexpr static std::u32string_view REGION = U"region";
        constexpr static std::u32string_view VERTICAL = U"vertical";
        constexpr static std::u32string_view LINE = U"line";
        constexpr static std::u32string_view POSITION = U"position";
        constexpr static std::u32string_view SIZE = U"size";
        constexpr static std::u32string_view ALIGN = U"align";

        enum class WritingDirection {
            HORIZONTAL,
            VERTICAL_GROWING_LEFT,
            VERTICAL_GROWING_RIGHT
        };
        enum class Alignment {
            AUTO,
            START,
            CENTER,
            END,
            LEFT,
            RIGHT
        };

        enum class TimeUnit {
            HOURS,
            MINUTES,
            SECONDS
        };

        explicit Cue(std::u32string identifier) : identifier(std::move(identifier)) {};

        void setText(std::u32string text) {
            this->text = std::move(text);
        }

        void setStartTime(long startTime) {
            this->startTime = startTime;
        }

        void setEndTime(long endTime) {
            this->endTime = endTime;
        }

        void setWritingDirection(WritingDirection writingDirection) {
            this->writingDirection = writingDirection;
        }

        void setRegion(std::shared_ptr<Region> region) {
            this->region = region;
        }

        void setTextAlignment(Alignment alignment) {
            this->textAlignment = alignment;
        }

        void setPositionAlignment(Alignment alignment) {
            this->positionAlignment = alignment;
        }

        void setPosition(double position) {
            this->position = position;
        }

        void setSize(double size) {
            this->size = size;
        }

    private:
        std::u32string identifier;
        bool pauseOnExit = false;
        std::shared_ptr<Region> region = nullptr;
        WritingDirection writingDirection = WritingDirection::HORIZONTAL;
        bool snapToLines = true;
        //Line line = auto
        double position = -1;
        Alignment positionAlignment = Alignment::AUTO;
        Alignment lineAlignment = Alignment::START;
        Alignment textAlignment = Alignment::CENTER;
        uint64_t size = DEFAULT_CUE_SIZE;
        std::u32string text;
        uint32_t startTime, endTime;
    };
}; // namespace name

#endif