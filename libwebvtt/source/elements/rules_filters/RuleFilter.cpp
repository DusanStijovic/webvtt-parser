#include "elements/rules_filter_objects/RuleFilter.h"
#include "elements/rules_filter_objects/ArgumentRuleFilter.h"
#include "elements/rules_filter_objects/NoArgumentRuleFilter.h"
#include "elements/rules_filter_objects/TimeStampRuleFilter.h"

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
            allowedPropreties.insert(RuleFilter::ANIMATION);
            allowedPropreties.insert(RuleFilter::ANIMATION_DELAY);
            allowedPropreties.insert(RuleFilter::ANIMATION_DIRECTION);
            allowedPropreties.insert(RuleFilter::ANIMATION_DURATION);
            allowedPropreties.insert(RuleFilter::ANIMATION_FILL_MODE);
            allowedPropreties.insert(RuleFilter::ANIMATION_ITERATION_COUNT);
            allowedPropreties.insert(RuleFilter::ANIMATION_NAME);
            allowedPropreties.insert(RuleFilter::ANIMATION_PLAY_STATE);
            allowedPropreties.insert(RuleFilter::ANIMATION_TIMING_FNCTION);
            break;
        case RULE_SHORTLAND_TYPE::BACKGROUND:
            allowedPropreties.insert(RuleFilter::BACKGROUND);
            allowedPropreties.insert(RuleFilter::BACKGROUND_ATTACHMENT);
            allowedPropreties.insert(RuleFilter::BACKGROUND_CLIP);
            allowedPropreties.insert(RuleFilter::BACKGROUND_COLOR);
            allowedPropreties.insert(RuleFilter::BACKGROUND_IMAGE);
            allowedPropreties.insert(RuleFilter::BACKGROUND_POSITION);
            allowedPropreties.insert(RuleFilter::BACKGROUND_REPEAT);
            allowedPropreties.insert(RuleFilter::BACKGROUND_SIZE);
            break;
        case RULE_SHORTLAND_TYPE::DECORATION:
            allowedPropreties.insert(RuleFilter::TEXT_DECORATION);
            allowedPropreties.insert(RuleFilter::TEXT_DECORATION_COLOR);
            allowedPropreties.insert(RuleFilter::TEXT_DECORATION_LINE);
            allowedPropreties.insert(RuleFilter::TEXT_DECORATION_STYLE);
            break;
        case RULE_SHORTLAND_TYPE::FONT:
            allowedPropreties.insert(RuleFilter::FONT);
            allowedPropreties.insert(RuleFilter::FONT_FAMILY);
            allowedPropreties.insert(RuleFilter::FONT_LINE_HEIGHT);
            allowedPropreties.insert(RuleFilter::FONT_SIZE);
            allowedPropreties.insert(RuleFilter::FONT_STRETCH);
            allowedPropreties.insert(RuleFilter::FONT_STYLE);
            allowedPropreties.insert(RuleFilter::FONT_VARIANT);
            allowedPropreties.insert(RuleFilter::FONT_WEIGHT);
            break;
        case RULE_SHORTLAND_TYPE::OUTLINE:
            allowedPropreties.insert(RuleFilter::OUTLINE);
            allowedPropreties.insert(RuleFilter::OUTLINE_COLOR);
            allowedPropreties.insert(RuleFilter::OUTLINE_STYLE);
            allowedPropreties.insert(RuleFilter::OUTLINE_WIDTH);
            break;
        case RULE_SHORTLAND_TYPE::TRANSITION:
            allowedPropreties.insert(RuleFilter::TRANSITION);
            allowedPropreties.insert(RuleFilter::TRANSITION_DELAY);
            allowedPropreties.insert(RuleFilter::TRANSITION_DURATION);
            allowedPropreties.insert(RuleFilter::TRANSITION_PROPERTY);
            allowedPropreties.insert(RuleFilter::TRANSITION_TIMING_FUNCTION);
            break;
        };
    };

    RuleFilter::~RuleFilter() {}

} // namespace WebVTT
