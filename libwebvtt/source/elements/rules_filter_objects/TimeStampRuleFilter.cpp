#include "elements/rules_filter_objects/TimeStampRuleFilter.h"

namespace WebVTT
{
    TimeStampRuleFilter()
    {
        allowedPropreties.insert(StyleSelector::COLOR);
        allowedPropreties.insert(StyleSelector::OPACITY);
        allowedPropreties.insert(StyleSelector::VISIBILITY);
        allowedPropreties.insert(StyleSelector::TEXT_SHADOW);
        allowedPropreties.insert(StyleSelector::WHITE_SPACE);
        allowedPropreties.insert(StyleSelector::TEXT_COMBINE_UPRIGHT);
        allowedPropreties.insert(StyleSelector::RUBY_POSITION);

        StyleSelector::addRuleToAllowedRules(StyleSelector::allowedPropreties, RULE_SHORTLAND_TYPE::ANIMATION);
        StyleSelector::addRuleToAllowedRules(StyleSelector::allowedPropreties, RULE_SHORTLAND_TYPE::TRANSITION);
        StyleSelector::addRuleToAllowedRules(StyleSelector::allowedPropreties, RULE_SHORTLAND_TYPE::DECORATION);
        StyleSelector::addRuleToAllowedRules(StyleSelector::allowedPropreties, RULE_SHORTLAND_TYPE::BACKGROUND);
        StyleSelector::addRuleToAllowedRules(StyleSelector::allowedPropreties, RULE_SHORTLAND_TYPE::OUTLINE);
        StyleSelector::addRuleToAllowedRules(StyleSelector::allowedPropreties, RULE_SHORTLAND_TYPE::FONT);
    }
} // namespace WebVTT
