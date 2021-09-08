#include "exceptions/parser_util/PercentageFormatNotValid.hpp"
#include "parser/ParserUtil.hpp"
#include "logger/LoggingUtility.hpp"
#include "exceptions/parser_util/ParsingFloatPointNumber.hpp"
#include "exceptions/parser_util/ParsingCoordinatesError.hpp"
#include "exceptions/parser_util/ParsingLongNumberError.hpp"
#include "exceptions/parser_util/ParsingTimeStampException.hpp"
#include "exceptions/parser_util/CollectingCharactersException.hpp"
#include "exceptions/parser_util/IteratorsNotPointToGivenString.hpp"
#include "exceptions/parser_util/PercentageFormatNotValid.hpp"

namespace webvtt {

void ParserUtil::checkIfIteratorPointToInput(std::u32string_view input, const std::u32string_view::iterator &position) {
  if (position < input.begin() || position > input.end())
    throw IteratorsNotPointToGivenString();
}

bool ParserUtil::isASCIIWhiteSpaceCharacter(uint32_t character) {
  if (character == ParserUtil::SPACE_C ||
      character == ParserUtil::TAB_C ||
      character == ParserUtil::LF_C ||
      character == ParserUtil::FF_C ||
      character == ParserUtil::CR_C) {
    return true;
  }

  return false;
}
inline bool ParserUtil::isAsciiDecDigit(uint32_t character) {
  return character >= NUMBER_ZERO_C && character <= NUMBER_NINE_C;
}
inline bool ParserUtil::isAsciiHexDigit(uint32_t character) {
  return (character >= NUMBER_ZERO_C && character <= NUMBER_NINE_C) ||
      (character >= CAPITAL_LETTER_A_C && character <= CAPITAL_LETTER_F_C) ||
      (character >= SMALL_LETTER_A_C && character <= SMALL_LETTER_F_C);
}
inline bool ParserUtil::isAsciiAlphaNumeric(uint32_t character) {
  if (isAsciiDecDigit(character))
    return true;
  if ((character >= SMALL_LETTER_A_C && character <= SMALL_LETTER_Z_C) ||
      (character >= CAPITAL_LETTER_A_C && character <= CAPITAL_LETTER_Z_C))
    return true;
  return false;
}

std::string
ParserUtil::collectCharacters(std::u32string_view input, std::u32string_view::iterator &position,
    const
std::function<
bool(uint32_t
character)> &isLookedCharacter) {
checkIfIteratorPointToInput(input, position
);
std::string collectedCharacters;
while (
isLookedCharacter(*position)
&& position != input.
end()
) {
utf8::append(*position, collectedCharacters
);
position++;
}
return
collectedCharacters;
}

double
ParserUtil::parsePercentage(std::u32string_view input) {
  try {
    if (input.back() != ParserUtil::PERCENT_C)
      throw PercentageFormatNotValid();
    return parseFloatPointingNumber(input.substr(0, input.length() - 1));
  }
  catch (const ParsingFloatPointNumber &error) {
    DILOGE(error.what());
    throw PercentageFormatNotValid();
  }
}

double
ParserUtil::parseFloatPointingNumber(std::u32string_view input) {
  try {
    std::size_t index = 0;
    std::string temp = utf8::utf32to8(input);
    double number = std::stod(temp, &index);
    if (index < temp.length())
      throw ParsingFloatPointNumber();
    return number;
  }
  catch (const std::out_of_range &error) {
    DILOGE(error.what());
    throw ParsingFloatPointNumber();
  }
  catch (const std::invalid_argument &error) {
    DILOGE(error.what());
    throw ParsingFloatPointNumber();
  }
}

long
ParserUtil::parseLongNumber(std::u32string_view input, uint8_t base) {
  std::string temp = utf8::utf32to8(input);
  return ParserUtil::parseLongNumber(temp, base);
}
long
ParserUtil::parseLongNumber(std::string_view input, uint8_t base) {
  try {
    std::size_t index = 0;
    std::string temp = std::string(input);
    long number = std::stol(temp, &index, base);
    if (index < temp.length())
      throw ParsingLongNumberError();
    return number;
  }
  catch (const std::out_of_range &error) {
    DILOGE(error.what());
    throw ParsingLongNumberError();
  }
  catch (const std::invalid_argument &error) {
    DILOGE(error.what());
    throw ParsingLongNumberError();
  }
}

void ParserUtil::skipWhiteSpaces(std::u32string_view input, std::u32string_view::iterator &position) {
  checkIfIteratorPointToInput(input, position);
  while (ParserUtil::isASCIIWhiteSpaceCharacter(*position) && position != input.end()) {
    std::advance(position, 1);
  }
}
bool ParserUtil::stringContainsSeparator(std::u32string_view input, std::u32string_view separator) {
  return input.find(separator, 0) != std::u32string_view::npos;
};
bool ParserUtil::compareU32Strings(std::u32string_view str1, std::u32string_view str2) {
  return str1.compare(str2) == 0;
}

std::u32string_view
ParserUtil::parseUntilCharacter(std::u32string_view input, uint32_t character,
                                std::u32string_view::iterator &position) {

  checkIfIteratorPointToInput(input, position);

  auto startPosition = position - input.begin();
  auto endPosition = input.find(character, startPosition);

  if (endPosition == std::u32string_view::npos) {
    endPosition = input.length();
  }

  position = position + endPosition - startPosition;
  return input.substr(startPosition, endPosition - startPosition);
}

std::u32string_view
ParserUtil::parseUntilAnyOfGivenCharacters(std::u32string_view input, std::u32string_view characters,
                                           std::u32string_view::iterator &position) {

  checkIfIteratorPointToInput(input, position);

  auto startPosition = position - input.begin();
  auto endPosition = input.find_first_of(characters, startPosition);

  if (endPosition == std::u32string_view::npos) {
    endPosition = input.length();
  }

  position = position + endPosition - startPosition;
  return input.substr(startPosition, endPosition - startPosition);
}

std::optional <std::tuple<std::u32string_view, std::u32string_view>>
ParserUtil::splitStringAroundCharacter(std::u32string_view input, uint32_t character) {
  auto charPos = input.find(character);

  if (charPos == std::u32string_view::npos) {
    return std::nullopt;
  }
  if (charPos == 0)
    return std::make_tuple<>(ParserUtil::EMPTY_STRING_VIEW, input);

  if (charPos == input.length() - 1)
    return std::make_tuple<>(input, ParserUtil::EMPTY_STRING_VIEW);

  auto key = input.substr(0, charPos);
  auto value = input.substr(charPos + 1, input.length() - charPos);
  return std::make_tuple<>(key, value);
}

std::tuple<double, double>
ParserUtil::parseCoordinates(std::u32string_view coordinates, uint32_t separator) {
  try {
    auto splitDataOptional = ParserUtil::splitStringAroundCharacter(coordinates, separator);
    if (!splitDataOptional.has_value())
      throw ParsingCoordinatesError();

    auto[xCoordinateString, yCoordinateString] = splitDataOptional.value();
    if (xCoordinateString.empty() || yCoordinateString.empty())
      throw ParsingCoordinatesError();

    double xCoord = ParserUtil::parsePercentage(xCoordinateString);
    double yCoord = ParserUtil::parsePercentage(yCoordinateString);

    return std::make_tuple(xCoord, yCoord);
  }
  catch (const PercentageFormatNotValid &error) {
    DILOGE(error.what());
    throw ParsingCoordinatesError();
  }
}

double
ParserUtil::parseTimeStamp(std::u32string_view input, std::u32string_view::iterator &position) {
  try {
    checkIfIteratorPointToInput(input, position);

    TimeUnit timeUnit = TimeUnit::MINUTES;
    uint32_t value1, value2, value3, value4;

    if (position == input.end())
      throw ParsingTimeStampException();

    if (!ParserUtil::isAsciiDecDigit(*position))
      throw ParsingTimeStampException();

    std::string collectedTimeString = ParserUtil::collectCharacters(input, position, ParserUtil::isAsciiDecDigit);
    value1 = ParserUtil::parseLongNumber(collectedTimeString, 10);

    if (collectedTimeString.length() != NUM_OF_DIGITS_FIRST_PART || value1 >= MAX_MINUTES_VALUE) {
      timeUnit = TimeUnit::HOURS;
    }

    if (position == input.end() || *position != ParserUtil::COLON_C)
      throw ParsingTimeStampException();
    position++;

    collectedTimeString = ParserUtil::collectCharacters(input, position, ParserUtil::isAsciiDecDigit);
    if (collectedTimeString.length() != NUM_OF_DIGITS_SECOND_PART)
      throw ParsingTimeStampException();
    value2 = ParserUtil::parseLongNumber(collectedTimeString, 10);

    //Check if first parsed digit is hours or minutes(does we have three or for parts)
    if (timeUnit == TimeUnit::HOURS || (position != input.end() && *position == ParserUtil::COLON_C)) {

      if (position == input.end() || *position != ParserUtil::COLON_C)
        throw ParsingTimeStampException();
      position++;

      collectedTimeString = ParserUtil::collectCharacters(input, position, ParserUtil::isAsciiDecDigit);
      if (collectedTimeString.length() != NUM_OF_DIGITS_THIRD_PART)
        throw ParsingTimeStampException();
      value3 = ParserUtil::parseLongNumber(collectedTimeString, 10);
    } else {
      value3 = value2;
      value2 = value1;
      value1 = 0;
    }

    if (position == input.end() || *position != ParserUtil::FULL_STOP)
      throw ParsingTimeStampException();
    position++;

    //Collect milliseconds
    collectedTimeString = ParserUtil::collectCharacters(input, position, ParserUtil::isAsciiDecDigit);
    if (collectedTimeString.length() != NUM_OF_DIGITS_FORTH_PART)
      throw ParsingTimeStampException();
    value4 = ParserUtil::parseLongNumber(collectedTimeString, 10);

    if (value2 >= MAX_MINUTES_VALUE || value3 >= MAX_SECONDS_VALUE)
      throw ParsingTimeStampException();

    return value1 * MAX_MINUTES_VALUE * MAX_SECONDS_VALUE + value2 * MAX_SECONDS_VALUE + value3 +
        ((double) value4) / MAX_MILLISECONDS_VALUE;
  }
  catch (const ParsingLongNumberError &error) {
    DILOGE(error.what());
    throw ParsingTimeStampException();
  }
  catch (const IteratorsNotPointToGivenString &error) {
    DILOGE(error.what());
    throw ParsingTimeStampException();
  }
}

std::u32string
ParserUtil::parseHTMLNumberReference(std::u32string_view input,
                                     std::u32string_view::iterator &currentPosition,
                                     bool &parsingError) {

  checkIfIteratorPointToInput(input, currentPosition);

  auto position = currentPosition;

  uint8_t base;
  std::optional <std::string> result;

  position++;
  if (position == input.end()) {
    return U"";
  }

  if (*position == ParserUtil::LATIN_CAPITAL_LETTER_X || *position == ParserUtil::LATIN_SMALL_LETTER_X) {
    position++; //Skip X or x
    result = ParserUtil::collectCharacters(input, position, ParserUtil::isAsciiHexDigit);
    base = 16;
  } else {
    result = ParserUtil::collectCharacters(input, position, ParserUtil::isAsciiDecDigit);
    base = 10;
  }

  if (!result.has_value()) {
    parsingError = true;
    return U"";
  }

  if (position != input.end() || *position == ParserUtil::SEMI_COLON) {
    position++;
  } else {
    DILOGE("Parsing HTML number reference, semi colon not found at the end");
    parsingError = true;
  }

  uint32_t number = ParserUtil::parseLongNumber(result.value(), base);
  currentPosition = position;

  //Check if number reference is allowed

  auto iter = numberHTMLReferences.find(number);
  if (iter != numberHTMLReferences.end()) {
    DILOGE("Parsing HTML number reference, references found in table of forbidden references");
    parsingError = true;
    return iter->second;
  }
  if ((number >= 0xD800 && number <= 0xDFFF) || number > 0x10FFFF) {
    DILOGE("Parsing HTML number reference, the reference number forbidden");
    parsingError = true;
    return {ParserUtil::REPLACEMENT_C};
  }

  for (uint32_t i = 0; i < std::size(low_border); i++) {
    if (number >= low_border[i] && number <= high_border[i]) {
      parsingError = true;
      DILOGE("Parsing HTML number reference, the reference number forbidden");
    }
  }

  if (unallowedNumbers.find(number) != unallowedNumbers.end()) {
    parsingError = true;
    DILOGE("Parsing HTML number reference, the reference number forbidden");
  }
  return {number};
}

std::u32string
ParserUtil::parseHTMLNamedReference(std::u32string_view input, std::u32string_view::iterator &currentPosition,
                                    bool isInAttribute, bool &parsingError) {
  try {
    checkIfIteratorPointToInput(input, currentPosition);

    auto position = currentPosition;

    if (position == input.end())
      return U"";

    std::string forMatching;
    std::map<std::string, std::u32string>::const_iterator found;

    uint32_t range = 1;

    while (range <= ParserUtil::MAX_NAMED_HTML_REF_LENGTH &&
        position != input.end() &&
        *position != ParserUtil::SEMI_COLON) {
      utf8::append(*position, forMatching);

      auto iter = namedHTMLREferences.find(forMatching);
      if (iter != namedHTMLREferences.end())
        found = iter;
      position++;
      range++;
    }
    if (*position == ParserUtil::SEMI_COLON) {
      utf8::append(*position, forMatching);
      auto iter = namedHTMLREferences.find(forMatching);
      if (iter != namedHTMLREferences.end())
        found = iter;
    }

    if (found == namedHTMLREferences.end()) {
      bool potentialError = true;
      std::string_view check = forMatching;
      for (char one : check.substr(0, forMatching.length() - 1)) {
        if (!ParserUtil::isAsciiAlphaNumeric(one))
          potentialError = false;
      }
      if (check.back() != ParserUtil::SEMI_COLON) {
        potentialError = false;
      }
      if (potentialError) {
        parsingError = true;
        DILOGE("Parsing HTML named reference, can not found voiceName in table of character references");
      }
      return U"";
    }

    if (isInAttribute && forMatching.back() != ParserUtil::SEMI_COLON && position != input.end()) {
      if (*position == ParserUtil::EQUAL_C || ParserUtil::isAsciiAlphaNumeric(*position)) {
        parsingError = true;
        return U"";
      }
    }

    if (isInAttribute && position != input.end() && *position == '=') {
      parsingError = true;
      DILOGE("Parsing HTML named reference, some legacy user agents will misinterpret the markup in those cases");
    }

    if (forMatching.back() != ';') {
      parsingError = true;
      DILOGE("Parsing HTML named reference, need to end with semi colon");
    }
    currentPosition = position;
    return found->second;
  }
  catch (const std::out_of_range &error) {
    DILOGE(error.what());
    parsingError = true;
    return U"";
  }
}

std::u32string
ParserUtil::consumeHTMLCharacter(std::u32string_view input, std::u32string_view::iterator &currentPosition,
                                 std::optional <uint32_t> additionalCharacter, bool isInAttribute, bool &parsingError) {
  try {

    checkIfIteratorPointToInput(input, currentPosition);

    auto position = currentPosition;
    position++;
    if (position == input.end())
      return U"";

    if (additionalCharacter.has_value() && additionalCharacter.value() == *position)
      return U"";

    std::u32string result;

    switch (*position) {
      case ParserUtil::TAB_C:
      case ParserUtil::LF_C:
      case ParserUtil::FF_C:
      case ParserUtil::SPACE_C:
      case ParserUtil::HYPHEN_LESS:
      case ParserUtil::AMPERSAND_C:result = U"";
        break;
      case ParserUtil::HASHTAG_C:result = ParserUtil::parseHTMLNumberReference(input, position, parsingError);
        currentPosition = position;
        break;
      default:result = ParserUtil::parseHTMLNamedReference(input, position, isInAttribute, parsingError);
        currentPosition = position;
        break;
    }
    return result;
  }
  catch (const IteratorsNotPointToGivenString &error) {
    DILOGE(error.what());
    return U"";
  }
  catch (const ParsingLongNumberError &error) {
    DILOGE(error.what());
    return U"";
  }
}

std::u32string ParserUtil::convertCSSEscapedString(std::u32string_view input) {
  auto position = input.begin();
  std::u32string convertedString;

  while (position != input.end()) {
    try {
      convertedString.append(ParserUtil::parseUntilCharacter(input, ParserUtil::BACK_SLASH_C, position));

      // Not found
      if (position == input.end())
        break;

      position++;

      // Backslash on the end
      if (position == input.end()) {
        convertedString.push_back(ParserUtil::BACK_SLASH_C);
        break;
      }
      char32_t character = *position;

      if (!ParserUtil::isAsciiHexDigit(character) &&
          ParserUtil::CR_C != character && ParserUtil::LF_C != character && ParserUtil::FF_C != character) {
        convertedString.push_back(character);
        position++;
        continue;
      }

      std::u32string_view parsedString = ParserUtil::parseWhileCondition(
          input, position,
          [](uint32_t character) {
            return ParserUtil::isAsciiHexDigit(character) ||
                !ParserUtil::isASCIIWhiteSpaceCharacter(character);
          },
          ParserUtil::MAX_NUMBER_OF_CSS_ESCAPED_CHARACTER);

      if (position != input.end() && ParserUtil::isASCIIWhiteSpaceCharacter(*position)) {
        position++;
      }

      if (parsedString.empty())
        break;

      char32_t number = ParserUtil::parseLongNumber(utf8::utf32to8(parsedString), 16);

      convertedString.push_back(number);
    }
    catch (const ParsingLongNumberError &error) {
      DILOGE(error.what());
    }
    catch (const IteratorsNotPointToGivenString &error) {
      DILOGE(error.what());
    }
  }

  DILOGI("Converted string:" + utf8::utf32to8(convertedString));
  return convertedString;
}

bool ParserUtil::checkIfCSSSIdentifierRightFormat(std::u32string_view input) {
  if (input.empty())
    return false;
  if (ParserUtil::isAsciiDecDigit(input.at(0)))
    return false;
  if (input.size() > 1) {
    if (ParserUtil::HYPHEN_MINUS == input.at(0)) {
      if (ParserUtil::HYPHEN_MINUS == input.at(1) || ParserUtil::isAsciiDecDigit(input.at(1)))
        return false;
    }
  }

  for (const auto &one : input) {
    if (ParserUtil::isAsciiAlphaNumeric(one))
      continue;
    if (one > ParserUtil::NO_BREAK_SPACE_C)
      continue;
    if (one == ParserUtil::HYPHEN_MINUS)
      continue;
    if (one == ParserUtil::UNDERSCORE_C)
      continue;
    return false;
  }
  return true;
}

std::u32string_view
ParserUtil::parseWhileCondition(std::u32string_view input, std::u32string_view::iterator &position,
                                const std::function<bool(uint32_t)> &condition,
                                uint8_t maxNumberOfCharacters) {

  checkIfIteratorPointToInput(input, position);

  long startPosition = position - input.begin();
  size_t length = 0;
  uint8_t iteration = 0;
  while (position != input.end() && condition(*position) &&
      iteration < maxNumberOfCharacters) {
    length++;
    iteration++;
    position++;
  }
  return input.substr(startPosition, length);
}

void ParserUtil::clearAndSetCharacter(std::u32string &input, uint32_t characterToSet) {
  input.clear();
  input.push_back(characterToSet);
}

void ParserUtil::strip(std::u32string_view &input, const std::function<bool(uint32_t)> &isAskedCharacter) {
  if (input.empty())
    return;

  auto position = input.begin();
  while (position != input.end() && isAskedCharacter(*position))
    position++;
  auto newBegin = position;

  if (newBegin == input.end()) {
    input = ParserUtil::EMPTY_STRING_VIEW;
    return;
  }

  position = input.end();
  position--;
  while (isAskedCharacter(*position))
    position--;
  auto newEnd = position;

  input = input.substr(newBegin - input.begin(), newEnd - newBegin + 1);
}

void ParserUtil::strip(std::u32string &input, const std::function<bool(uint32_t)> &isAskedCharacter) {
  std::u32string_view temp = input;
  strip(temp, isAskedCharacter);
  input = std::u32string(temp);
}

void ParserUtil::replaceAllSequenceOfCharactersWithGivenCharacter(std::u32string &input,
                                                                  const std::function<bool(uint32_t)> &isAskedCharacter,
                                                                  uint32_t character) {
  auto position = input.begin();
  while (position != input.end()) {
    while (position != input.end() && !isAskedCharacter(*position))
      position++;
    if (position == input.end())
      return;

    auto startPosition = position;

    while (position != input.end() && isAskedCharacter(*position))
      position++;

    if (startPosition == position - 1)
      continue;

    position = input.erase(startPosition, position - 1);
    *position = character;
  }
}

};
