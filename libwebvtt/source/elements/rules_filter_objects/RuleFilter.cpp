#include "elements/rules_filter_objects/RuleFilter.h"

namespace WebVTT
{
    bool RuleFilter::isRuleAllowed(std::string_view name)
    {
        return allowedRules.find(name) != allowedRules.end();
    }

} // namespace WebVTT
