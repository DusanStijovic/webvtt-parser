#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_TOKEN_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_TOKEN_HPP_
#include "elements/cue_nodes/NodeObject.hpp"
#include <string>
#include <stack>
#include <memory>

namespace webvtt
{

  class Token
  {
  public:
    explicit Token(std::u32string &tokenValue) : tokenValue(tokenValue) {}
    virtual void process(std::shared_ptr<NodeObject> &nodeObject, std::stack<std::u32string> &language) = 0;

    Token() = default;
    Token(const Token &) = delete;
    Token(Token &&) = delete;
    Token &operator=(const Token &) = delete;
    Token &operator=(Token &&) = delete;
    virtual ~Token() = default;

  protected:
    std::u32string tokenValue;
  };

}

#endif // LIBWEBVTT_INCLUDE_PARSER_CUE_TEXT_TOKENIZER_TOKENS_TOKEN_HPP_
