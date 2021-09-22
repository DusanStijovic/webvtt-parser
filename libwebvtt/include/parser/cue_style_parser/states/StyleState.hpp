#ifndef LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_STATES__STYLE_STATE_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_CUE_STYLE_PARSER_STATES__STYLE_STATE_HPP_

#include <stdint.h>
#include <memory>
#include <map>

namespace webvtt
{
  class StyleSheetParser;

  class StyleState
  {
  public:
    enum class StyleStateType
    {
      NONE,
      START,
      START_SELECTOR,
      ID_SELECTOR,
      CLASS_SELECTOR,
      TYPE_SELECTOR,
      ATTRIBUTE_SELECTOR,
      PSEUDO_START,
      PSEUDO_CLASS_SELECTOR,
      PSEUDO_ELEMENT_SELECTOR,
      COLLECT_PSEUDO_ARGUMENT,
      PSEUDO_CLASS_ARGUMENT_END,
      PSEUDO_ELEMENT_ARGUMENT_END,
      BEFORE_RULE_STATE,
      COMBINATION,
      END_SELECTOR,
      RULES,
      END_STATE,
      ERROR,
      START_COMMENT_STATE,
      COMMENT_STATE,
      END_COMMENT_STATE
    };

    StyleState() = default;
    StyleState(const StyleState &) = delete;
    StyleState(StyleState &&) = delete;
    StyleState &operator=(const StyleState &) = delete;
    StyleState &operator=(StyleState &&) = delete;

    virtual void processState(StyleSheetParser &parser) = 0;

    virtual ~StyleState() = default;

    static StyleState *getInstance(StyleStateType styleStateType);

  protected:
    static uint32_t getNextCharacter(StyleSheetParser &parser);

  private:
    static std::map<StyleStateType, std::unique_ptr<StyleState>> statesInstance;
    static std::unique_ptr<StyleState> makeNewState(StyleStateType styleStateType);
  };

}
#endif //LIBWEBVTT_INCLUDE_STYLE_STATE_H
