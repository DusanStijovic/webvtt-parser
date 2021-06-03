#include <string>
#include <algorithm>
#include "utf8.h"

namespace WebVTT {

    class ParserUtil {
    public:
        static bool isSpaceCharacter(uint32_t character) {
            if (character >= 0x0009 && character <= 0x000D)
                return true;

            if (character >= 0x2000 && character <= 0x200A)
                return true;

            uint32_t checkList[9] = {
                    0x0085, 0x0020, 0x00A0, 0x1680, 0x2028, 0x2029, 0x202F, 0x205F, 0x3000};
            auto position = std::find(std::begin(checkList), std::end(checkList), character);
            return position != std::end(checkList);
        }

        static inline bool isDigit(uint32_t character) {
            return character >= 0x0030 && character <= 0x0039;
        }

        static std::optional<std::string>
        collectDigits(std::u32string_view input, std::u32string_view::iterator &position) {
            if (position < input.begin()) return std::nullopt;
            std::string collectedDigits;
            while (ParserUtil::isDigit(*position) && position != input.end()) {
                std::u32string temp{*position};
                collectedDigits.append(utf8::utf32to8(temp));
                position++;
            }
            return collectedDigits;
        }

        static bool skipWhiteSpaces(std::u32string_view input, std::u32string_view::iterator &position) {
            if (position < input.begin()) return false;
            while (ParserUtil::isSpaceCharacter(*position) && position != input.end()) {
                std::advance(position, 1);
            }
            return position == input.end();
        }

        static bool checkIfStringContainsArrow(std::u32string input) {
            //TO DO - maybe change to string and use regex
            if (input.size() < 3)
                return false;
            auto current = input.begin();
            auto end = input.end();
            do {
                auto first = current++;
                auto second = current++;
                auto third = current++;
                if (*first != HYPEN_MINUS || *second != HYPEN_MINUS || *third != HYPEN_GREATHER) {
                    if (end - current < 1)
                        break;
                    current = second;
                    continue;
                }
                return true;
            } while (true);
            return false;
        };
    };

}