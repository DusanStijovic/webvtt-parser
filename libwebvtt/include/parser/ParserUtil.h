#ifndef WEBVTT_PARSER_UTIL_H
#define WEBVTT_PARSER_UTIL_H

#include "utf8.h"
#include "logger/LoggingUtility.h"
#include <string>
#include <algorithm>
#include <tuple>
#include <map>
#include <functional>
#include <array>
#include <set>

namespace WebVTT {

class ParserUtil {
 public:
  ParserUtil() = delete;

  static const std::map<uint32_t, std::u32string> numberHTMLReferences;
  static const std::map<std::string, std::u32string> namedHTMLREferences;

  static constexpr uint32_t MAX_NAMED_HTML_REF_LENGTH = 31;

  static const std::set<uint32_t> unallowedNumbers;

  static const std::array<uint32_t, 4> low_border;

  static const std::array<uint32_t, 4> high_border;

  static constexpr int MAX_NUMBER_OF_CSS_ESCAPED_CHARACTER = 6;

  enum SPECIAL_CHARACTER {
    FFFF_C = 0xFFFF,
    NULL_C = 0x0000,
    REPLACEMENT_C = 0xFFFD,
    CR_C = 0x000D,
    LF_C = 0x000A,
    FF_C = 0x000C,
    SPACE_C = 0x0020,
    TAB_C = 0x0009,
    HYPHEN_MINUS = 0x002D,
    HYPHEN_GREATER = 0x003E,
    COLON_C = 0x003A,
    SEMI_COLON = 0x003B,
    FULL_STOP = 0x002E,
    COMMA_C = 0x002C,
    DOT_C = 0x002E,
    PERCENT_C = 0x0025,
    AMPERSAND_C = 0x0026,
    HYPHEN_LESS = 0x003C,
    EOF_C = 0x0005,
    SOLIDUS_C = 0x002F,
    LEFT_PARENTHESIS_C = 0x0028,
    RIGHT_PARENTHESIS_C = 0x0029,
    LEFT_SQUARE_BRACKET_C = 0x005B,
    RIGHT_SQUARE_BRACKET_C = 0x005D,
    HASHTAG_C = 0x0023,
    EQUAL_C = 0x003D,
    LEFT_CURLY_BRACKET_C = 0x007B,
    RIGHT_CURLY_BRACKET_C = 0x007D,
    LATIN_SMALL_LETTER_X = 0x0078,
    LATIN_CAPITAL_LETTER_X = 0x0058,
    BACK_SLASH_C = 0x005C,
    PLUS_SIGN_C = 0x002B,
    TILDE_C = 0x007E,
    NUMBER_ZERO_C = 0x0030,
    NUMBER_NINE_C = 0x39,
    CAPITAL_LETTER_A_C = 0x0041,
    CAPITAL_LETTER_F_C = 0x0046,
    CAPITAL_LETTER_Z_C = 0x005A,
    SMALL_LETTER_A_C = 0x0061,
    SMALL_LETTER_F_C = 0x0066,
    SMALL_LETTER_Z_C = 0x007A,
    UNDERSCORE_C = 0x005f,
    NO_BREAK_SPACE_C = 0x00A0

  };

  /**
   * Constexpresions for parsing timestamps
   */
  static constexpr int MAX_MINUTES_VALUE = 60;
  static constexpr int MAX_SECONDS_VALUE = 60;
  static constexpr int MAX_MILLISECONDS_VALUE = 1000;

  static constexpr int NUM_OF_DIGITS_FIRST_PART = 2;
  static constexpr int NUM_OF_DIGITS_SECOND_PART = 2;
  static constexpr int NUM_OF_DIGITS_THIRD_PART = 2;
  static constexpr int NUM_OF_DIGITS_FORTH_PART = 3;

  /**
   *Enum representing type of units in cue time stamp while parsing timestamp
   */
  enum class TimeUnit {
    HOURS,
    MINUTES,
    SECONDS
  };

  static constexpr std::u32string_view TIME_STAMP_SEPARATOR = U"-->";

  static constexpr std::u32string_view EMPTY_STRING_VIEW = U"";

  /**
   * Constansts for cue style
   */
  static constexpr std::u32string_view LANG_TYPE_MARK = U"lang";
  static constexpr std::u32string_view VOICE_TYPE_MARK = U"v";

  static constexpr std::u32string_view LANG_ATTRIBUTE_MARK = U"lang";
  static constexpr std::u32string_view VOICE_ATRIBUTE_MARK = U"voice";

  static bool isASCIIWhiteSpaceCharacter(uint32_t character);
  static bool isWhiteSpaceCharacter(uint32_t character);

  static bool isAsciiDecDigit(uint32_t character);
  static bool isAsciiHexDigit(uint32_t character);

  static bool isAsciiAlphaNumeric(uint32_t character);

  static void checkIfIteratorPointToInput(std::u32string_view input, const std::u32string_view::iterator &position);

  static std::string
  collectCharacters(std::u32string_view input,
                    std::u32string_view::iterator &position,
                    const std::function<bool(uint32_t character)> &isLookedCharacter);

  //TODO add dot option
  static double
  parsePercentage(std::u32string_view input);

  static double
  parseFloatPointingNumber(std::u32string_view input);

  static long
  parseLongNumber(std::u32string_view input, uint8_t base = 10);
  static long
  parseLongNumber(std::string_view input, uint8_t base =10);

  static void skipWhiteSpaces(std::u32string_view input, std::u32string_view::iterator &position);

  static bool stringContainsSeparator(std::u32string_view input, std::u32string_view separator);

  static bool compareU32Strings(std::u32string_view str1, std::u32string_view str2);

  static std::u32string_view
  parseUntilCharacter(std::u32string_view input, uint32_t character, std::u32string_view::iterator &position);

  static std::u32string_view parseWhileCondition(std::u32string_view input, std::u32string_view::iterator &position,
                                                 const std::function<bool(uint32_t)>& condition,
                                                 uint8_t maxNumberOfCharacters);
  static std::u32string_view
  parseUntilAnyOfGivenCharacters(std::u32string_view input,
                                 std::u32string_view characters,
                                 std::u32string_view::iterator &position);

  static std::optional<std::tuple<std::u32string_view, std::u32string_view>>
  splitStringAroundCharacter(std::u32string_view input, uint32_t character);

  static std::tuple<double, double>
  parseCoordinates(std::u32string_view coordinates, uint32_t separator);

  static void clearAndSetCharacter(std::u32string &input, uint32_t characterToSet);

  static void strip(std::u32string_view &input, const std::function<bool(uint32_t)> &isAskedCharacter);
  static void strip(std::u32string &input, const std::function<bool(uint32_t)>& isAskedCharacter);

  static void replaceAllSequenceOfCharactersWithGivenCharacter(std::u32string &input,
                                                               const std::function<bool(uint32_t)>& isAskedCharacter,
                                                               uint32_t character);

  static double
  parseTimeStamp(std::u32string_view input, std::u32string_view::iterator &position);

  static std::u32string_view makeStringViewFromIterator(const std::u32string_view input,
                                                        const std::u32string_view::iterator &begin,
                                                        const typename std::u32string_view::iterator &end);

  static std::u32string consumeHTMLCharacter(std::u32string_view input,
                                             std::u32string_view::iterator &currentPosition,
                                             std::optional<uint32_t> additionalCharacter,
                                             bool isInAttribute,
                                             bool &parsingError);

  static std::u32string parseHTMLNumberReference(std::u32string_view input,
                                                 std::u32string_view::iterator &currentPosition,
                                                 bool &parsingError);
  static bool checkIfNumberReferenceAllowed(uint32_t number);

  static std::u32string parseHTMLNamedReference(std::u32string_view input,
                                                std::u32string_view::iterator &currentPosition,
                                                bool isInAttribute,
                                                bool &parsingError);

  static std::u32string convertCSSEscapedString(std::u32string_view input);
  static bool checkIfCSSSIdentifierRightFormat(std::u32string_view input);
};
}; // namespace WebVTT
#endif