#include <string>
#include <algorithm>
#include "utf8.h"

namespace WebVTT
{

    class ParserUtil
    {
    public:
        static bool isSpaceCharacter(uint32_t character)
        {
            if (character >= 0x0009 && character <= 0x000D)
                return true;

            if (character >= 0x2000 && character <= 0x200A)
                return true;

            uint32_t checkList[9] = {
                0x0085, 0x0020, 0x00A0, 0x1680, 0x2028, 0x2029, 0x202F, 0x205F, 0x3000};
            auto position = std::find(std::begin(checkList), std::end(checkList), character);
            return position != std::end(checkList) ? true : false;
        }

        static inline bool isDigit(uint32_t character)
        {
            return character >= 0x0030 && character <= 0x0039;
        }

        static std::string collectDigits(std::u32string_view input, const char32_t *position)
        {
            std::string collectedDigits;
            while (ParserUtil::isDigit(*position))
            {
                uint32_t index = position - input.begin();
                collectedDigits.append(utf8::utf32to8(input.substr(index, 1)));
                position++;
            }
            return collectedDigits;
        }

        static bool skipWhiteSpaces(std::u32string_view input, const char32_t *position)
        {
            while (*position == ParserUtil::isSpaceCharacter(*position) && position != input.end())
            {
                position++;
            }
            return position == input.end();
        }
    };

}