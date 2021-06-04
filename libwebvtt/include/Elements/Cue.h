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


    namespace CUE_SETTING {
        constexpr int DEFAULT_CUE_SIZE = 100;
        constexpr std::u32string_view REGION = U"region";
        constexpr std::u32string_view VERTICAL = U"vertical";
        constexpr std::u32string_view LINE = U"line";
        constexpr std::u32string_view POSITION = U"position";
        constexpr std::u32string_view SIZE = U"size";
        constexpr std::u32string_view ALIGN = U"align";
    };

    class Cue : public Block {
    public:

        explicit Cue(std::u32string identifier) : identifier(std::move(identifier)) {};

        bool collectTimingAndSettings(std::u32string_view input,
                                             std::u32string_view::iterator &position);

        void setText(std::u32string text) {
            this->text = std::move(text);
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
        uint64_t size = CUE_SETTING::DEFAULT_CUE_SIZE;
        std::u32string text;
        uint32_t start, end;


        static std::optional<long> collectTimeStamp(std::u32string_view input, std::u32string_view::iterator &position);

        static std::optional<std::tuple<long, long>>
        collectTiming(std::u32string_view input, std::u32string_view::iterator &position);


        void collectSetting(std::u32string_view input, std::u32string_view::iterator &position);

        void collectRegionSetting(std::u32string_view name, std::u32string_view value);

        void collectVerticalSetting(std::u32string_view name, std::u32string_view value);

        void collectLineSetting(std::u32string_view name, std::u32string_view value);

        void collectPositionSetting(std::u32string_view name, std::u32string_view value);

        void collectSizeSetting(std::u32string_view name, std::u32string_view value);

        void collectAlignSetting(std::u32string_view name, std::u32string_view value);
    };
}; // namespace name



#endif