#include "elements/rules_filter_objects/ArgumentRuleFilter.h"

namespace WebVTT
{
    ArgumentRuleFilter::ArgumentRuleFilter()
    {
        allowedPropreties.insert(RuleFilter::COLOR);
        allowedPropreties.insert(RuleFilter::OPACITY);
        allowedPropreties.insert(RuleFilter::VISIBILITY);
        allowedPropreties.insert(RuleFilter::TEXT_SHADOW);
        allowedPropreties.insert(RuleFilter::WHITE_SPACE);
        allowedPropreties.insert(RuleFilter::TEXT_COMBINE_UPRIGHT);
        allowedPropreties.insert(RuleFilter::RUBY_POSITION);

        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::ANIMATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::DECORATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::BACKGROUND);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::OUTLINE);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::FONT);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::TRANSITION);
    }
} // namespace WebVTT
