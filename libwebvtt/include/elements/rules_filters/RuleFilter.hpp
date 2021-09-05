#ifndef LIBWEBVTT_INCLUDE_ELEMENTS_RULES_FILTERS_RULE_FILTER_HPP_
#define LIBWEBVTT_INCLUDE_ELEMENTS_RULES_FILTERS_RULE_FILTER_HPP_
#include <set>
#include <string>
#include <memory>
#include <map>

namespace webvtt {

class RuleFilter {

 public:

  [[nodiscard]] bool isRuleAllowed(std::string_view name) const;
  virtual ~RuleFilter() = 0;

  enum class RULE_FILTER_TYPE {
    TIME_STAMP,
    NO_ARGUMENT,
    ARGUMENT
  };

  static const RuleFilter &
  getRuleFilter(RULE_FILTER_TYPE ruleFilterType);

  RuleFilter() = default;
  RuleFilter(const RuleFilter &) = delete;
  RuleFilter(RuleFilter &&) = delete;
  RuleFilter &operator=(const RuleFilter &) = delete;
  RuleFilter &operator=(RuleFilter &&) = delete;
 protected:
  std::set<std::string_view> allowedProperties;
  enum class RULE_SHORT_LAND_TYPE {
    ANIMATION,
    TRANSITION,
    FONT,
    OUTLINE,
    BACKGROUND,
    DECORATION
  };

  void addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE ruleShortlandType);

 private:
  static std::map<RULE_FILTER_TYPE, std::unique_ptr<RuleFilter>> ruleFilters;
  static std::unique_ptr<RuleFilter> makeRuleFilter(RULE_FILTER_TYPE ruleFilterType);
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_ELEMENTS_RULES_FILTERS_RULE_FILTER_HPP_
