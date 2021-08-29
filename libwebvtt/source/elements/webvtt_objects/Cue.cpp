#include "elements/webvtt_elements/Region.h"
#include "elements/webvtt_elements/Cue.h"
#include "parser/ParserUtil.h"
#include "utf8.h"

namespace WebVTT
{
    void Cue::setText(std::u32string newText)
    {
        this->text = std::move(newText);
    }

    void Cue::setStartTime(double newTime)
    {
        this->startTime = newTime;
    }

    void Cue::setEndTime(double newTime)
    {
        this->endTime = newTime;
    }

    void Cue::setWritingDirection(WritingDirection newWritingDirection)
    {
        if (writingDirection != Cue::WritingDirection::HORIZONTAL)
        {
            this->setRegion(nullptr);
        }
        this->writingDirection = newWritingDirection;
    }

    void Cue::setRegion(Region *newRegion)
    {
        this->region = newRegion;
    }

    void Cue::setTextAlignment(Alignment newAlignment)
    {
        this->textAlignment = newAlignment;
    }

    void Cue::setPositionAlignment(Alignment newAlignment)
    {
        this->positionAlignment = newAlignment;
    }

    void Cue::setPosition(double newPosition)
    {
        this->position = newPosition;
    }

    void Cue::setSize(double newSize)
    {
        this->size = newSize;
        if (newSize < MAX_CUE_SIZE)
            this->setRegion(nullptr);
    }

    void Cue::setLineAlignment(Alignment newAlignment)
    {
        this->lineAlignment = newAlignment;
    }

    void Cue::setLineNumber(double newLineNumber)
    {
        this->lineNumber = newLineNumber;
        if (newLineNumber != LINE_DEFAULT_VALUE)
            this->setRegion(nullptr);
    }

    void Cue::setSnapToLines(bool newSnapToLines)
    {
        this->snapToLines = newSnapToLines;
    }

    std::u32string_view Cue::getText()
    {
        return text;
    }

    void Cue::setTextTreeRoot(std::shared_ptr<NodeObject> &treeRoot)
    {
        this->textTreeRoot = treeRoot;
    }

    const NodeObject &Cue::getTextTreeRoot()
    {
        return *this->textTreeRoot.get();
    }
}
