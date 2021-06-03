#ifndef WEBVTT_CUE_H
#define WEBVTT_CUE_H

#include <string>
#include <memory>
#include <optional>
#include <utility>
#include "TimePoint.h"
#include "constants.h"
#include "Block.h"

namespace WebVTT {

    class Cue : public Block{
    public:

        explicit Cue(std::u32string identifier) : identifier(std::move(identifier)) {};

        static bool collectTimingAndSettings(std::unique_ptr<Cue> &cue, std::u32string_view input,
                                             std::u32string_view::iterator &position);

        void setText(std::u32string text) {
            this->text = std::move(text);
        }

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


        static std::optional<long> collectTimeStamp(std::u32string_view input, std::u32string_view::iterator &position);

        static std::optional<std::tuple<long, long>>
        collectTiming(std::u32string_view input, std::u32string_view::iterator &position);

    };
}; // namespace name



#endif