
#include <iostream>

#include "include/styling.hpp"
#include "include/color.hpp"
#include "include/format.hpp"

const std::string &styling::getKeyword() const
{
  return _keyword;
}

const bool &styling::getGatherStatistics() const
{
  return _gatherStatistics;
}

const std::string &styling::getStylingLocation() const
{
  return _applyStyling;
}

const std::string &styling::getColor() const
{
  if (_color == std::string("white"))
    return color::WHITE;
  else if (_color == std::string("red"))
    return color::RED;
  else if (_color == std::string("green"))
    return color::GREEN;
  else if (_color == std::string("magenta"))
    return color::MAGENTA;
  else if (_color == std::string("blue"))
    return color::BLUE;
  else if (_color == std::string("cyan"))
    return color::CYAN;
  else if (_color == std::string("yellow"))
    return color::YELLOW;
  else
    return color::WHITE;
}

const std::string &styling::getStyle() const
{
  if (_style == std::string("normal"))
    return format::NORMAL;
  else if (_style == std::string("underline"))
    return format::UNDERLINE;
  else if (_style == std::string("bold"))
    return format::BOLD;
  else if (_style == std::string("dim"))
    return format::DIM;
  else if (_style == std::string("blink"))
    return format::BLINK;
  else
    return format::NORMAL;
}

const bool &styling::getSurpressKeywordFlag() const
{
  return _surpressKeyword;
}

void styling::writeLineContainingKeyword(std::string line) const
{
  _occurances.push_back(line);
}