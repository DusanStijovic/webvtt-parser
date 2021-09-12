#include "elements/rules_filters/RuleFilter.hpp"
#include "elements/rules_filters/ArgumentRuleFilter.hpp"
#include "elements/rules_filters/NoArgumentRuleFilter.hpp"
#include "elements/rules_filters/TimeStampRuleFilter.hpp"
#include "parser/CSSConstants.hpp"

namespace webvtt
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
        return allowedProperties.find(name) != allowedProperties.end();
    }

    void RuleFilter::addRuleGroupToAllowedRules(RULE_SHORT_LAND_TYPE ruleShortlandType)
    {
        switch (ruleShortlandType)
        {
        case RULE_SHORT_LAND_TYPE::ANIMATION:
            allowedProperties.insert(CSSConstants::ANIMATION);
            allowedProperties.insert(CSSConstants::ANIMATION_DELAY);
            allowedProperties.insert(CSSConstants::ANIMATION_DIRECTION);
            allowedProperties.insert(CSSConstants::ANIMATION_DURATION);
            allowedProperties.insert(CSSConstants::ANIMATION_FILL_MODE);
            allowedProperties.insert(CSSConstants::ANIMATION_ITERATION_COUNT);
            allowedProperties.insert(CSSConstants::ANIMATION_NAME);
            allowedProperties.insert(CSSConstants::ANIMATION_PLAY_STATE);
            allowedProperties.insert(CSSConstants::ANIMATION_TIMING_FUNCTION);
            break;
        case RULE_SHORT_LAND_TYPE::BACKGROUND:
            allowedProperties.insert(CSSConstants::BACKGROUND);
            allowedProperties.insert(CSSConstants::BACKGROUND_ATTACHMENT);
            allowedProperties.insert(CSSConstants::BACKGROUND_CLIP);
            allowedProperties.insert(CSSConstants::BACKGROUND_COLOR);
            allowedProperties.insert(CSSConstants::BACKGROUND_IMAGE);
            allowedProperties.insert(CSSConstants::BACKGROUND_POSITION);
            allowedProperties.insert(CSSConstants::BACKGROUND_REPEAT);
            allowedProperties.insert(CSSConstants::BACKGROUND_SIZE);
            break;
        case RULE_SHORT_LAND_TYPE::DECORATION:
            allowedProperties.insert(CSSConstants::TEXT_DECORATION);
            allowedProperties.insert(CSSConstants::TEXT_DECORATION_COLOR);
            allowedProperties.insert(CSSConstants::TEXT_DECORATION_LINE);
            allowedProperties.insert(CSSConstants::TEXT_DECORATION_STYLE);
            break;
        case RULE_SHORT_LAND_TYPE::FONT:
            allowedProperties.insert(CSSConstants::FONT);
            allowedProperties.insert(CSSConstants::FONT_FAMILY);
            allowedProperties.insert(CSSConstants::FONT_LINE_HEIGHT);
            allowedProperties.insert(CSSConstants::FONT_SIZE);
            allowedProperties.insert(CSSConstants::FONT_STRETCH);
            allowedProperties.insert(CSSConstants::FONT_STYLE);
            allowedProperties.insert(CSSConstants::FONT_VARIANT);
            allowedProperties.insert(CSSConstants::FONT_WEIGHT);
            break;
        case RULE_SHORT_LAND_TYPE::OUTLINE:
            allowedProperties.insert(CSSConstants::OUTLINE);
            allowedProperties.insert(CSSConstants::OUTLINE_COLOR);
            allowedProperties.insert(CSSConstants::OUTLINE_STYLE);
            allowedProperties.insert(CSSConstants::OUTLINE_WIDTH);
            break;
        case RULE_SHORT_LAND_TYPE::TRANSITION:
            allowedProperties.insert(CSSConstants::TRANSITION);
            allowedProperties.insert(CSSConstants::TRANSITION_DELAY);
            allowedProperties.insert(CSSConstants::TRANSITION_DURATION);
            allowedProperties.insert(CSSConstants::TRANSITION_PROPERTY);
            allowedProperties.insert(CSSConstants::TRANSITION_TIMING_FUNCTION);
            break;
        };
    };

    RuleFilter::~RuleFilter() {}

} // namespace webvtt
