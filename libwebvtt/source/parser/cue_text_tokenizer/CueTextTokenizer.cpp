#include "parser/cue_text_tokenizer/CueTextTokenizer.h"
#include "parser/cue_text_tokenizer/states/DataState.h"
#include "parser/cue_text_tokenizer/states/StartTagState.h"
#include "parser/cue_text_tokenizer/states/StartTagAnnotationState.h"
#include "parser/cue_text_tokenizer/states/StartTagClassState.h"
#include "parser/cue_text_tokenizer/states/EndTagState.h"
#include "parser/cue_text_tokenizer/states/TagState.h"
#include "parser/cue_text_tokenizer/states/TimeStampTagState.h"
#include "parser/cue_text_tokenizer/tokens/Token.h"
#include "parser/ParserUtil.h"
#include <memory>

namespace WebVTT {

    std::shared_ptr<Token> CueTextTokenizer::getNextToken() {
        while (true) {
            uint32_t c = *currentPosition;
            if (currentPosition == input.end())
                c = STOP_TOKENIZER;
            std::shared_ptr<Token> token = currentState->process();
            if (token != nullptr)
                return token;
            currentPosition++;
        }
        return nullptr;
    }

    void CueTextTokenizer::initializeTokenizerStates() {
        statesInsance[TokenizerState::DATA] = std::shared_ptr<CueTextTokenizerState>(new DataState(*this));
        statesInsance[TokenizerState::START_TAG] = std::shared_ptr<CueTextTokenizerState>(new StartTagState(*this));
        statesInsance[TokenizerState::START_TAG_ANNOTATION] = std::shared_ptr<CueTextTokenizerState>(
                new StartTagAnnotationState(*this));
        statesInsance[TokenizerState::TAG] = std::shared_ptr<CueTextTokenizerState>(new TagState(*this));
        statesInsance[TokenizerState::END_TAG] = std::shared_ptr<CueTextTokenizerState>(new EndTagState(*this));
        statesInsance[TokenizerState::START_TAG_CLASS] = std::shared_ptr<CueTextTokenizerState>(
                new StartTagClassState(*this));
        statesInsance[TokenizerState::TIME_STAMP_TAG] = std::shared_ptr<CueTextTokenizerState>(
                new TimpStampTagState(*this));
    }

    std::shared_ptr<CueTextTokenizerState> CueTextTokenizer::getStateInstance(TokenizerState tokenizerState) {
        auto instance = statesInsance.find(tokenizerState);
        if (instance != statesInsance.end()) return instance->second;
        else return nullptr;
    }

}
