#ifndef LIBWEBVTT_CUE_TEXT_TOKENIZER_H
#define LIBWEBVTT_CUE_TEXT_TOKENIZER_H

#include <string>
#include <string_view>
#include "Token.h"
#include "CueTextTokenizerState.h"
#include "DataState.h"

class CueTextTokenizer
{
public:
    explicit CueTextTokenizer(std::u32string_view new_input)
    {
        this->input = new_input;
        currentState = DataState::getIstance();
        currentPosition = input.begin();
    }

    std::shared_ptr<Token> getNextToken();

private:
    std::u32string_view input{};
    std::shared_ptr<CueTextTokenizerState> currentState;
    typename std::u32string_view::iterator currentPosition;
};

#endif
