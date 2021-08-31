#include "elements/rules_filters/RuleFilter.h"
#include "elements/rules_filters/ArgumentRuleFilter.h"
#include "elements/rules_filters/NoArgumentRuleFilter.h"
#include "elements/rules_filters/TimeStampRuleFilter.h"
#include "parser/CSSConstants.h"

namespace WebVTT
{

    std::map<RuleFilter::RULE_FILTER_TYPE, std::unique_ptr<RuleFilter>> RuleFilter::ruleFilters;

    std::unique_ptr<RuleFilter> RuleFilter::makeRuleFilter(RULE_FILTER_TYPE ruleFilterType)
    {
        switch (ruleFilterType)
        {
        case RULE_FILTER_TYPE::ARGUMENT:
            return std::make_unique<ArgumentRuleFilter>();
        case RULE_FILTER_TYPE::NO_ARGUMENT:
            return std::make_unique<NoArgumentRuleFilter>();
        case RULE_FILTER_TYPE::TIME_STAMP:
            return std::make_unique<TimeStampRuleFilter>();
        default:
            return nullptr;
        }
    };
    const RuleFilter &
    RuleFilter::getRuleFilter(RULE_FILTER_TYPE ruleFilterType)
    {
        auto found = ruleFilters.find(ruleFilterType);
        if (found == ruleFilters.end())
        {
            std::unique_ptr<RuleFilter> newRuleFilter = makeRuleFilter(ruleFilterType);
            ruleFilters[ruleFilterType] = std::move(newRuleFilter);
            return *newRuleFilter.get();
        }
        return *(found->second.get());
    }

    bool RuleFilter::isRuleAllowed(std::string_view name) const
    {
        return allowedPropreties.find(name) != allowedPropreties.end();
    }

    void RuleFilter::addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE ruleShortlandType)
    {
        switch (ruleShortlandType)
        {
        case RULE_SHORTLAND_TYPE::ANIMATION:
            allowedPropreties.insert(CSSConstants::ANIMATION);
            allowedPropreties.insert(CSSConstants::ANIMATION_DELAY);
            allowedPropreties.insert(CSSConstants::ANIMATION_DIRECTION);
            allowedPropreties.insert(CSSConstants::ANIMATION_DURATION);
            allowedPropreties.insert(CSSConstants::ANIMATION_FILL_MODE);
            allowedPropreties.insert(CSSConstants::ANIMATION_ITERATION_COUNT);
            allowedPropreties.insert(CSSConstants::ANIMATION_NAME);
            allowedPropreties.insert(CSSConstants::ANIMATION_PLAY_STATE);
            allowedPropreties.insert(CSSConstants::ANIMATION_TIMING_FNCTION);
            break;
        case RULE_SHORTLAND_TYPE::BACKGROUND:
            allowedPropreties.insert(CSSConstants::BACKGROUND);
            allowedPropreties.insert(CSSConstants::BACKGROUND_ATTACHMENT);
            allowedPropreties.insert(CSSConstants::BACKGROUND_CLIP);
            allowedPropreties.insert(CSSConstants::BACKGROUND_COLOR);
            allowedPropreties.insert(CSSConstants::BACKGROUND_IMAGE);
            allowedPropreties.insert(CSSConstants::BACKGROUND_POSITION);
            allowedPropreties.insert(CSSConstants::BACKGROUND_REPEAT);
            allowedPropreties.insert(CSSConstants::BACKGROUND_SIZE);
            break;
        case RULE_SHORTLAND_TYPE::DECORATION:
            allowedPropreties.insert(CSSConstants::TEXT_DECORATION);
            allowedPropreties.insert(CSSConstants::TEXT_DECORATION_COLOR);
            allowedPropreties.insert(CSSConstants::TEXT_DECORATION_LINE);
            allowedPropreties.insert(CSSConstants::TEXT_DECORATION_STYLE);
            break;
        case RULE_SHORTLAND_TYPE::FONT:
            allowedPropreties.insert(CSSConstants::FONT);
            allowedPropreties.insert(CSSConstants::FONT_FAMILY);
            allowedPropreties.insert(CSSConstants::FONT_LINE_HEIGHT);
            allowedPropreties.insert(CSSConstants::FONT_SIZE);
            allowedPropreties.insert(CSSConstants::FONT_STRETCH);
            allowedPropreties.insert(CSSConstants::FONT_STYLE);
            allowedPropreties.insert(CSSConstants::FONT_VARIANT);
            allowedPropreties.insert(CSSConstants::FONT_WEIGHT);
            break;
        case RULE_SHORTLAND_TYPE::OUTLINE:
            allowedPropreties.insert(CSSConstants::OUTLINE);
            allowedPropreties.insert(CSSConstants::OUTLINE_COLOR);
            allowedPropreties.insert(CSSConstants::OUTLINE_STYLE);
            allowedPropreties.insert(CSSConstants::OUTLINE_WIDTH);
            break;
        case RULE_SHORTLAND_TYPE::TRANSITION:
            allowedPropreties.insert(CSSConstants::TRANSITION);
            allowedPropreties.insert(CSSConstants::TRANSITION_DELAY);
            allowedPropreties.insert(CSSConstants::TRANSITION_DURATION);
            allowedPropreties.insert(CSSConstants::TRANSITION_PROPERTY);
            allowedPropreties.insert(CSSConstants::TRANSITION_TIMING_FUNCTION);
            break;
        };
    };

    RuleFilter::~RuleFilter() {}

} // namespace WebVTT
