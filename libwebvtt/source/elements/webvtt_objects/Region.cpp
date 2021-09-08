#include "elements/webvtt_objects/Region.hpp"
#include <algorithm>
#include <iterator>

namespace webvtt {

void Region::setIdentifier(const std::u32string_view newIdentifier) {
  this->identifier = std::u32string(newIdentifier);
}

void Region::setWidth(double newWidth) {
  this->width = newWidth;
}

void Region::setLines(int newNumOfLines) {
  this->lines = newNumOfLines;
}

void Region::setViewAnchorPort(std::tuple<double, double> newViewPortAnchor) {
  this->viewPortAnchor = newViewPortAnchor;
}

void Region::setAnchor(std::tuple<double, double> newAnchor) {
  this->anchor = newAnchor;
}

void Region::setScrollValue(ScrollType newScrollValue) {
  this->scrollValue = newScrollValue;
}

bool Region::IsShouldApplyLastVisitedStyleSheet() const {
  return shouldApplyLastVisitedStyleSheet;
}

void Region::visit(const MatchAllSelector &selector) {
  shouldApplyLastVisitedStyleSheet = true;
}

void Region::visit(const IdSelector &selector) {
  shouldApplyLastVisitedStyleSheet = selector.getId() == this->identifier;
}
void Region::visit(const ClassSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}

void Region::visit(const ItalicTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void Region::visit(const LanguageTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void Region::visit(const UnderlineTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void Region::visit(const VoiceTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void Region::visit(const VoiceSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void Region::visit(const ClassTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void Region::visit(const BoldTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void Region::visit(const RubyTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void Region::visit(const RubyTextTypeSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}
void Region::visit(const LanguageSelector &selector) {
  shouldApplyLastVisitedStyleSheet = false;
}

void Region::visit(const CompoundSelector &selector) {
  throw NotImplementedError();
}
void Region::visit(const CombinatorSelector &selector) {
  throw NotImplementedError();
}

}
