#ifndef CSS_CONSTANTS_H
#define CSS_CONSTANTS_H
#include <string>

namespace WebVTT
{
    class CSSConstants
    {
    public:
        //FIELDS
        static constexpr std::string_view COLOR = "color";
        static constexpr std::string_view OPACITY = "opacity";
        static constexpr std::string_view VISIBILITY = "visibility";
        static constexpr std::string_view TEXT_SHADOW = "text_shadow";
        static constexpr std::string_view WHITE_SPACE = "white-space";
        static constexpr std::string_view TEXT_COMBINE_UPRIGHT = "text-combine-upright";
        static constexpr std::string_view RUBY_POSITION = "ruby-position";
        //Text decoration rules
        static constexpr std::string_view TEXT_DECORATION = "text-decoration";
        static constexpr std::string_view TEXT_DECORATION_LINE = "text-decoration-line";
        static constexpr std::string_view TEXT_DECORATION_STYLE = "text-decoration-style";
        static constexpr std::string_view TEXT_DECORATION_COLOR = "text-decoration-color";
        //Background rules
        static constexpr std::string_view BACKGROUND = "background";
        static constexpr std::string_view BACKGROUND_COLOR = "background-color";
        static constexpr std::string_view BACKGROUND_POSITION = "background-position";
        static constexpr std::string_view BACKGROUND_SIZE = "background-size";
        static constexpr std::string_view BACKGROUND_REPEAT = "background-repeat";
        static constexpr std::string_view BACKGROUND_CLIP = "background-clip";
        static constexpr std::string_view BACKGROUND_ATTACHMENT = "background-attachment";
        static constexpr std::string_view BACKGROUND_IMAGE = "background-image";
        //Font rules
        static constexpr std::string_view FONT = "font";
        static constexpr std::string_view FONT_STYLE = "font-style";
        static constexpr std::string_view FONT_VARIANT = "font-variant";
        static constexpr std::string_view FONT_WEIGHT = "font-weight";
        static constexpr std::string_view FONT_STRETCH = "font-stretch";
        static constexpr std::string_view FONT_SIZE = "font-size";
        static constexpr std::string_view FONT_LINE_HEIGHT = "line-height";
        static constexpr std::string_view FONT_FAMILY = "font-family";
        //Outline
        static constexpr std::string_view OUTLINE = "outline";
        static constexpr std::string_view OUTLINE_COLOR = "font";
        static constexpr std::string_view OUTLINE_STYLE = "font";
        static constexpr std::string_view OUTLINE_WIDTH = "font";

        //Transition rules
        static constexpr std::string_view TRANSITION = "transition";
        static constexpr std::string_view TRANSITION_PROPERTY = "transition-property";
        static constexpr std::string_view TRANSITION_DURATION = "transition-duration";
        static constexpr std::string_view TRANSITION_TIMING_FUNCTION = "transition-timing-function";
        static constexpr std::string_view TRANSITION_DELAY = "transition-deley";

        //Animation rules
        static constexpr std::string_view ANIMATION = "animation";
        static constexpr std::string_view ANIMATION_NAME = "animation-name";
        static constexpr std::string_view ANIMATION_DURATION = "animation-duration";
        static constexpr std::string_view ANIMATION_TIMING_FNCTION = "animation-timing-function";
        static constexpr std::string_view ANIMATION_DELAY = "animation-delay";
        static constexpr std::string_view ANIMATION_ITERATION_COUNT = "animation-iteration-count";
        static constexpr std::string_view ANIMATION_DIRECTION = "animation-direction";
        static constexpr std::string_view ANIMATION_FILL_MODE = "animation-fill_mode";
        static constexpr std::string_view ANIMATION_PLAY_STATE = "animation-play-state";

        //ALLOWED TYPES
        constexpr static std::u32string_view BOLD = U"b";
        constexpr static std::u32string_view ITALIC = U"i";
        constexpr static std::u32string_view CLASS = U"c";
        constexpr static std::u32string_view LANG = U"lang";
        constexpr static std::u32string_view RUBY = U"ruby";
        constexpr static std::u32string_view UNDERLINE = U"u";
        constexpr static std::u32string_view VOICE = U"v";
        constexpr static std::u32string_view RUBY_TEXT = U"rt";
        //SUPORTED PSEUDO CLASSES

        //SUPORTED PSEUDO ELEMENTS
    };

} // namespace WebVTT

#endif //CSS_CONSTANTS_H
