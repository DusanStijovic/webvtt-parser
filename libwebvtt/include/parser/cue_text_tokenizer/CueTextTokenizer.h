#ifndef LIBWEBVTT_CUE_TEXT_TOKENIZER_H
#define LIBWEBVTT_CUE_TEXT_TOKENIZER_H

#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.h"
#include "parser/cue_text_tokenizer/tokens/Token.h"
#include <string>
#include <list>

namespace WebVTT
{

    class CueTextTokenizer
    {
    public:
        enum class TokenizerState
        {
            DATA,
            START_TAG,
            START_TAG_ANNOTATION,
            START_TAG_CLASS,
            END_TAG,
            TIME_STAMP_TAG,
            TAG
        };
        constexpr static uint32_t STOP_TOKENIZER = 0xFFFF;

        explicit CueTextTokenizer(std::u32string_view new_input)
        {
            this->input = new_input;
            currentPosition = input.begin();

            initializeTokenizerStates();
            currentState = getStateInstance(TokenizerState::DATA);
        }

        std::shared_ptr<Token> getNextToken();

        void setTokenizerState(TokenizerState tokenizerState)
        {
            currentState = getStateInstance(tokenizerState);
        }

        std::shared_ptr<CueTextTokenizerState> &getTokenizerState()
        {
            return currentState;
        }

        std::shared_ptr<CueTextTokenizerState> &getStateInstance(TokenizerState tokenizerState);

        inline std::u32string_view getInput() { return input; }

        inline std::u32string &getResult() { return result; }

        inline std::u32string &getBuffer() { return buffer; }

        inline typename std::u32string_view::iterator &getCurrentPosition() { return currentPosition; }

        inline std::list<std::u32string> &getClasses() { return classes; }

        void addBufferToClasses()
        {
            this->classes.push_back(this->buffer);
        }

    private:
        std::u32string_view input{};
        std::u32string result;
        std::u32string buffer;
        std::list<std::u32string> classes;

        std::shared_ptr<CueTextTokenizerState> currentState;
        typename std::u32string_view::iterator currentPosition;

        void initializeTokenizerStates();

        std::map<TokenizerState, std::shared_ptr<CueTextTokenizerState>> statesInsance;
    };

}
#endif
