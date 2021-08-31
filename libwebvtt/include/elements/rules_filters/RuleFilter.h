#ifndef LIBWEBVTT_RULE_FILTER_H
#define LIBWEBVTT_RULE_FILTER_H
#include <set>
#include <string>
#include <memory>
#include <map>

namespace WebVTT
{

    class RuleFilter
    {

    public:
       
        bool isRuleAllowed(std::string_view name) const;
        virtual ~RuleFilter() = 0;

        enum class RULE_FILTER_TYPE
        {
            TIME_STAMP,
            NO_ARGUMENT,
            ARGUMENT
        };

        static const RuleFilter &
        getRuleFilter(RULE_FILTER_TYPE ruleFilterType);

    protected:
        std::set<std::string_view> allowedPropreties;
        enum class RULE_SHORTLAND_TYPE
        {
            ANIMATION,
            TRANSITION,
            FONT,
            OUTLINE,
            BACKGROUND,
            DECORATION
        };

        void addRuleGroupToAllowedRules(RULE_SHORTLAND_TYPE ruleShortlandType);

    private:
        static std::map<RULE_FILTER_TYPE, std::unique_ptr<RuleFilter>> ruleFilters;
        static std::unique_ptr<RuleFilter> makeRuleFilter(RULE_FILTER_TYPE ruleFilterType);
    };

} // namespace WebVTT

#endif //LIBWEBVTT_RULEFILTER_H
