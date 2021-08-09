#ifndef LIBWEBVTT_STYLE_STATE_H
#define LIBWEBVTT_STYLE_STATE_H

namespace WebVTT
{
    class StyleSheetParser;

    class StyleState
    {
    public:
        StyleState(StyleSheetParser &styleSheetParser) : styleSheetParser(styleSheetParser) {}
        virtual void processState() = 0;
        virtual ~StyleState() = default;

    protected:
        StyleSheetParser &styleSheetParser;
    };

}
#endif //LIBWEBVTT_STYLE_STATE_H
