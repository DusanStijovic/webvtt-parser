#ifndef LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_CUE_PARSER_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_CUE_PARSER_HPP_

#include "elements/webvtt_objects/Cue.hpp"
#include "parser/object_parser/base_classes/CueParserBase.hpp"
#include "parser/cue_text_tokenizer/CueTextTokenizer.hpp"
#include "elements/webvtt_objects/Region.hpp"
#include "buffer/UniquePtrSyncBuffer.hpp"
#include <list>
#include <memory>
#include <utility>

namespace webvtt {

/**
* Parser used to parse all cue info from string and set related filed.
*
* Algorithm and specification used could be found on:
* https://www.w3.org/TR/webvtt1/#cue-timings-and-settings-parsing
*/
class CueParser : public CueParserBase {

 public:

  void buildObjectFromString(std::u32string_view input);

  /**
 * Set cue text to current parsing cue object
 * @param text
 */
  void setTextToObject(std::u32string text) override;

  void parseTextStyleAndMakeStyleTree(std::u32string_view defaultLanguage = U"") override;

  explicit CueParser(std::shared_ptr<UniquePtrSyncBuffer<Region>> regions) : currentRegions(std::move(regions)) {}

  CueParser() = default;
  CueParser(const CueParser &) = delete;
  CueParser(CueParser &&) = delete;
  CueParser &operator=(const CueParser &) = delete;
  CueParser &operator=(CueParser &&) = delete;
  ~CueParser() override = default;

 private:
  const std::shared_ptr<UniquePtrSyncBuffer<Region>> currentRegions;

  std::unique_ptr<CueTextTokenizer> cueTextTokenizer = std::make_unique<CueTextTokenizer>();

  //HYPHEN-MINUS HYPHEN_MINUS HYPHEN_GREATER
  static constexpr std::u32string_view TIME_STAMP_SEPARATOR = U"-->";

  /**
 * Const expressions that represent type of cue setting
 */
  constexpr static std::u32string_view REGION_SETTING = U"region";
  constexpr static std::u32string_view VERTICAL_SETTING = U"vertical";
  constexpr static std::u32string_view LINE_SETTING = U"line";
  constexpr static std::u32string_view POSITION_SETTING = U"position";
  constexpr static std::u32string_view SIZE_SETTING = U"size";
  constexpr static std::u32string_view ALIGN_SETTING = U"align";

  /**
 * Const expressions for parsing vertical settings
 */
  static constexpr std::u32string_view VERTICAL_LEFT_TO_RIGHT = U"lr";
  static constexpr std::u32string_view VERTICAL_RIGHT_TO_LEFT = U"rl";

  /**
 * Const expressions for parsing alignment
 */
  static constexpr std::u32string_view START_ALIGNMENT = U"start";
  static constexpr std::u32string_view END_ALIGNMENT = U"end";
  static constexpr std::u32string_view CENTER_ALIGNMENT = U"center";
  static constexpr std::u32string_view RIGHT_ALIGNMENT = U"right";
  static constexpr std::u32string_view LEFT_ALIGNMENT = U"left";

  /**
 * Const expressions for parsing line settings
 */
  static constexpr std::u32string_view LINE_LEFT = U"line-left";
  static constexpr std::u32string_view LINE_CENTER = U"center";
  static constexpr std::u32string_view LINE_RIGHT = U"line-right";

  /**
 *Parse string(input) starting from specified position and return tuple of two parsed time in seconds or null if parsing
 * was not finished successfully. Times are separated with specified separator;
 *
 *Time format: hh:mm:ss.ttt separator hh:mm:ss.ttt
 *Any number of spaces around separator are allowed
 *
 * @param input string being parsed
 * @param position place in string from which parsing starts
 * @param time stamp separator
 */
  void
  parseAndSetTiming(std::u32string_view input, std::u32string_view::iterator &position,
                    std::u32string_view separator);

  /**
 * Collect settings from input string started from position.
 * This method also sets setting field in current cue.
 * If parsing some setting was not successful function does not have any effects.
 *
 * @param input string being parsed
 * @param position place in string from which parsing starts
 */
  void parseAndSetSetting(std::u32string_view input, std::u32string_view::iterator &position);

  /**
 * Parse and set cue region setting
 *
 * @param value value of setting being parsed
 */
  void parseAndSetRegionSetting(std::u32string_view value);

  /**
 * Parse and set cue vertical setting
 *
 * @param value value of setting being parsed
 */
  void parseAndSetVerticalSetting(std::u32string_view value);

  /**
 * Parse and set cue line setting
 *
 * @param value value of setting being parsed
 */
  void parseAndSetLineSetting(std::u32string_view value);

  /**
 * Parse and set cue position setting
 *
 * @param value value of setting being parsed
 */
  void parseAndSetPositionSetting(std::u32string_view value);

  /**
 * Parse and set cue size setting
 *
 * @param value value of setting being parsed
 */
  void parseAndSetSizeSetting(std::u32string_view value);

  /**
 * Parse and set cue align setting
 *
 * @param value value of setting being parsed
 */
  void parseAndSetAlignSetting(std::u32string_view value);
};

} // namespace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_CUE_PARSER_HPP_
