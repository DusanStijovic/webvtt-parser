#ifndef STYLE_SHEET_FORMAT_ERROR_H
#define STYLE_SHEET_FORMAT_ERROR_H
#include <exception>

namespace webvtt
{
    class StyleSheetFormatError : public std::exception
    {

    public:
        StyleSheetFormatError() = default;

        const char *what() const noexcept override
        {
            return "Style Sheet Format Error";
        }
    };

} // namespace webvtt

#endif // STYLE_SHEET_FORMAT_ERROR_H