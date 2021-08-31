#include "elements/rules_filters/TimeStampRuleFilter.h"
#include "parser/CSSConstants.h"

namespace WebVTT
{
    TimeStampRuleFilter::TimeStampRuleFilter()
    {
        allowedPropreties.insert(CSSConstants::COLOR);
        allowedPropreties.insert(CSSConstants::OPACITY);
        allowedPropreties.insert(CSSConstants::VISIBILITY);
        allowedPropreties.insert(CSSConstants::TEXT_SHADOW);

        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::ANIMATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::TRANSITION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::DECORATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::BACKGROUND);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::OUTLINE);
    }
} // namespace WebVTT
