#include "elements/rules_filters/ArgumentRuleFilter.hpp"
#include "parser/CSSConstants.hpp"

namespace webvtt
{
    ArgumentRuleFilter::ArgumentRuleFilter()
    {
        allowedProperties.insert(CSSConstants::COLOR);
        allowedProperties.insert(CSSConstants::OPACITY);
        allowedProperties.insert(CSSConstants::VISIBILITY);
        allowedProperties.insert(CSSConstants::TEXT_SHADOW);
        allowedProperties.insert(CSSConstants::WHITE_SPACE);
        allowedProperties.insert(CSSConstants::TEXT_COMBINE_UPRIGHT);
        allowedProperties.insert(CSSConstants::RUBY_POSITION);

        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::ANIMATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::DECORATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::BACKGROUND);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::OUTLINE);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::FONT);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE::TRANSITION);
    }
} // namespace webvtt
