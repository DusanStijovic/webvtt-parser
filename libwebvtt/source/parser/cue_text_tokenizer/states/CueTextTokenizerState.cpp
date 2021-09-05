#include "parser/cue_text_tokenizer/states/CueTextTokenizerState.hpp"
#include "parser/cue_text_tokenizer/CueTextTokenizer.hpp"
#include "parser/cue_text_tokenizer/states/DataState.hpp"
#include "parser/cue_text_tokenizer/states/StartTagState.hpp"
#include "parser/cue_text_tokenizer/states/StartTagAnnotationState.hpp"
#include "parser/cue_text_tokenizer/states/StartTagClassState.hpp"
#include "parser/cue_text_tokenizer/states/EndTagState.hpp"
#include "parser/cue_text_tokenizer/states/TagState.hpp"
#include "parser/cue_text_tokenizer/states/TimeStampTagState.hpp"
#include "parser/ParserUtil.hpp"

namespace webvtt
{

  std::map<CueTextTokenizerState::TokenizerState, std::unique_ptr<CueTextTokenizerState>>
      CueTextTokenizerState::statesInstance;

  uint32_t CueTextTokenizerState::getNextCharacter(CueTextTokenizer &tokenizer)
  {
    uint32_t character;
    if (tokenizer.getCurrentPosition() == tokenizer.getInput().end())
      character = CueTextTokenizer::STOP_TOKENIZER;
    else
    {
      character = *tokenizer.getCurrentPosition();
    }
    return character;
  }

  std::unique_ptr<CueTextTokenizerState> CueTextTokenizerState::makeNewTokenizerState(TokenizerState tokenizerState)
  {
    switch (tokenizerState)
    {
    case TokenizerState::DATA:
      return std::make_unique<DataState>();
    case TokenizerState::START_TAG:
      return std::make_unique<StartTagState>();
    case TokenizerState::START_TAG_ANNOTATION:
      return std::make_unique<StartTagAnnotationState>();
    case TokenizerState::TAG:
      return std::make_unique<TagState>();
    case TokenizerState::END_TAG:
      return std::make_unique<EndTagState>();
    case TokenizerState::START_TAG_CLASS:
      return std::make_unique<StartTagClassState>();
    case TokenizerState::TIME_STAMP_TAG:
      return std::make_unique<TimpStampTagState>();
    default:
      return nullptr;
    }
  }

  CueTextTokenizerState *CueTextTokenizerState::getInstance(TokenizerState tokenizerState)
  {
    auto instance = statesInstance.find(tokenizerState);
    if (instance != statesInstance.end())
      return instance->second.get();
    else
    {
      auto temp = std::move(makeNewTokenizerState(tokenizerState));
      return (statesInstance[tokenizerState] = std::move(temp)).get();
    }
  }
}
