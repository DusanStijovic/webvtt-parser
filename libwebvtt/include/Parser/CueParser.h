#ifndef WEBVTT_CUE_PARSER_H
#define WEBVTT_CUE_PARSER_H

#include "Cue.h"
#include <list>
#include <memory>

namespace WebVTT
{
    class CueParser
    {
    private:
        std::list<std::shared_ptr<Cue>> cues;
    };

} //End of namespace

#endif
