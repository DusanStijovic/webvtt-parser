#include "elements/rules_filters/TimeStampRuleFilter.hpp"
#include "parser/CSSConstants.hpp"

namespace webvtt
{
    TimeStampRuleFilter::TimeStampRuleFilter()
    {
        allowedProperties.insert(CSSConstants::COLOR);
        allowedProperties.insert(CSSConstants::OPACITY);
        allowedProperties.insert(CSSConstants::VISIBILITY);
        allowedProperties.insert(CSSConstants::TEXT_SHADOW);

        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::ANIMATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::TRANSITION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::DECORATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::BACKGROUND);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::OUTLINE);
    }
} // namespace webvtt
