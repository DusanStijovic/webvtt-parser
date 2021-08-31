#include "elements/rules_filters/ArgumentRuleFilter.h"
#include "parser/CSSConstants.h"

namespace WebVTT
{
    ArgumentRuleFilter::ArgumentRuleFilter()
    {
        allowedPropreties.insert(CSSConstants::COLOR);
        allowedPropreties.insert(CSSConstants::OPACITY);
        allowedPropreties.insert(CSSConstants::VISIBILITY);
        allowedPropreties.insert(CSSConstants::TEXT_SHADOW);
        allowedPropreties.insert(CSSConstants::WHITE_SPACE);
        allowedPropreties.insert(CSSConstants::TEXT_COMBINE_UPRIGHT);
        allowedPropreties.insert(CSSConstants::RUBY_POSITION);

        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::ANIMATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::DECORATION);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::BACKGROUND);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::OUTLINE);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::FONT);
        RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE::TRANSITION);
    }
} // namespace WebVTT
