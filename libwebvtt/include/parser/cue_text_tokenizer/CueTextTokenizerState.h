#ifndef LIBWEBVTT_CUE_TEXT_TOKENIZE_RSTATE_H
#define LIBWEBVTT_CUE_TEXT_TOKENIZE_RSTATE_H
#include "DataState.h"

class CueTextTokenizerState
{

public:
    static std::shared_ptr<CueTextTokenizerState> getIstance()
    {
        if (instance == nullptr)
            instance = std::shared_ptr<CueTextTokenizerState>(new DataState);
    }
    virtual ~CueTextTokenizerState() = 0;

private:
    static std::shared_ptr<CueTextTokenizerState> instance;

protected:
    CueTextTokenizerState() {}
};

#endif
