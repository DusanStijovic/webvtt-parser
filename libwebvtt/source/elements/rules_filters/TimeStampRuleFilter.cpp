#include "elements/rules_filter_objects/TimeStampRuleFilter.h"

namespace WebVTT
{
    TimeStampRuleFilter::TimeStampRuleFilter()
    {
        allowedPropreties.insert(RuleFilter::COLOR);
        allowedPropreties.insert(RuleFilter::OPACITY);
        allowedPropreties.insert(RuleFilter::VISIBILITY);
        allowedPropreties.insert(RuleFilter::TEXT_SHADOW);

        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::ANIMATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::TRANSITION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::DECORATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::BACKGROUND);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::OUTLINE);
    }
} // namespace WebVTT
