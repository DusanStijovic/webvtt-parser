#ifndef LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_REGION_PARSER_HPP_
#define LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_REGION_PARSER_HPP_

#include "elements/webvtt_objects/Region.hpp"
#include "parser/object_parser/base_classes/RegionParserBase.hpp"
#include <list>
#include <memory>
#include <string>

namespace webvtt {
class RegionParser : public RegionParserBase {
 public:
  void buildObjectFromString(std::u32string_view input) override;

  RegionParser() = default;
  RegionParser(const RegionParser &) = delete;
  RegionParser(RegionParser &&) = delete;
  RegionParser &operator=(const RegionParser &) = delete;
  RegionParser &operator=(RegionParser &&) = delete;
  ~RegionParser() override = default;

 private:
  /**
 * Const expresions that represent specific region setting
 */
  static constexpr std::u32string_view ID_SETTING = U"id";
  static constexpr std::u32string_view WIDTH_SETTING = U"width";
  static constexpr std::u32string_view LINES_SETTING = U"lines";
  static constexpr std::u32string_view REGION_ANCHOR_SETTING = U"regionanchor";
  static constexpr std::u32string_view VIEW_PORT_ANCHOR_SETTING = U"viewportanchor";
  static constexpr std::u32string_view SCROLL_SETTING = U"scroll";

  /**
 * Parse and set region id
 *
 * @param settingValue value of setting being parsed
 */
  void parseAndSetIdSetting(std::u32string_view settingValue);

  /**
 * Parse and set region width setting
 *
 * @param settingValue value of setting being parsed
 */
  void parseAndSetWidthSetting(std::u32string_view settingValue);

  /**
 *Parse and set region line setting
 *
 * @param settingValue value of setting being parsed
 */
  void parseAndSetLinesSetting(std::u32string_view settingValue);

  /**
 * Parse and set region anchor setting
 *
 * @param settingValue value of setting being parsed
 */
  void parseAndSetAnchorSetting(std::u32string_view settingValue);

  /**
 *Parse and set region view port anchor setting
 *
 * @param settingValue value of setting being parsed
 */
  void parseAndSetViewPortAnchorSetting(std::u32string_view settingValue);

  /**
 * Parse and set region scroll setting
 *
 * @param settingValue value of setting being parsed
 */
  void parseAndSetScrollSetting(std::u32string_view settingValue);
};

} // namspace webvtt

#endif // LIBWEBVTT_INCLUDE_PARSER_OBJECT_PARSER_REGION_PARSER_HPP_