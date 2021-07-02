#ifndef WEBVTT_CUE_H
#define WEBVTT_CUE_H

#include <string>
#include <memory>
#include <optional>
#include <utility>
#include "TimePoint.h"
#include "Block.h"
#include "Region.h"

namespace WebVTT {
    /**
     * Class representing cue in WebVTT. It contains cue id,  cue text, cue timing and cue settings
     *
     * All description of what specific setting mean could be found on:
     * https://www.w3.org/TR/webvtt1/#model-cues
     */
    class Cue : public Block {
    public:


        /**
         *Default values for the settings are set when calling constructor  
         */
        Cue() = default;

        /**
         * Enum representing writing direction of cue text
         */
        enum class WritingDirection {
            HORIZONTAL,
            VERTICAL_GROWING_LEFT,
            VERTICAL_GROWING_RIGHT
        };

        /**
         * Enum representing cue text and position alignment
         */
        enum class Alignment {
            AUTO,
            START,
            CENTER,
            END,
            LEFT,
            RIGHT
        };

        /**
         *Enum representing type of units in cue time stamp while parsing timestamp
         */
        enum class TimeUnit {
            HOURS,
            MINUTES,
            SECONDS
        };


        explicit Cue(std::u32string identifier) : identifier(std::move(identifier)) {};

        /**
         * Set cue text
         *
         * @param text cue text
         */
        void setText(std::u32string newText);

        /**
         * Set cue start time
         *
         * @param time time in seconds
         */
        void setStartTime(double newTime);

        /**
         * Set cue end time
         *
         * @param endTime time in seconds
         */
        void setEndTime(double newTime);

        /**
         * Set cue writing direction
         *
         * @param writingDirection cue text writing direction, one instance of enum WritingDirection
         */
        void setWritingDirection(WritingDirection newWritingDirection);

        /**
         * Set cue region
         *
         * @param region region of cue
         */
        void setRegion(std::shared_ptr<Region> newRegion);

        /**
         * Set cue text alignment
         *
         * @param alignment cue text alignment, one instance of enum Alignment
         */
        void setTextAlignment(Alignment newAlignment);

        /**
         * Set cue position alignment
         *
         * @param alignment cue position alignment, one instance of enum Alignment
         */
        void setPositionAlignment(Alignment newAlignment);

        /**
         * Set cue position
         *
         * @param position cue position
         */
        void setPosition(double newPosition);

        /**
         * Set cue size
         *
         * @param size  set cue size
         */
        void setSize(double newSize);

        /**
         * Set cue line alignment
         *
         * @param alignment line position alignment, one instance of enum Alignment
         */
        void setLineAlignment(Alignment newAlignment);

        /**
         * Set cue line number
         *
         * @param lineNumber number of line
         */
        void setLineNumber(double newLineNumber);

        /**
         * Set cue snapToLines flag
         *
         * @param newSnapToLines new snap to lines flag
         */
        void setSnapToLines(bool newSnapToLines);

    private:

        static constexpr double MAX_CUE_SIZE = 100;
        static constexpr double DEFAULT_CUE_SIZE = 100;

        static constexpr double LINE_DEFAULT_VALUE = -1;
        static constexpr double POSITION_DEFAULT_VALUE = -1;


        /**
         * Unique id of cue
         */
        std::u32string identifier;
        std::shared_ptr<Region> region = nullptr;
        WritingDirection writingDirection = WritingDirection::HORIZONTAL;
        double lineNumber = LINE_DEFAULT_VALUE;
        double position = POSITION_DEFAULT_VALUE;
        Alignment positionAlignment = Alignment::AUTO;
        Alignment lineAlignment = Alignment::START;
        Alignment textAlignment = Alignment::CENTER;
        double size = DEFAULT_CUE_SIZE;
        std::u32string text;
        double startTime = 0, endTime = 0;
        bool pauseOnExit = false;
        bool snapToLines = true;
    };
}; // namespace name

#endif