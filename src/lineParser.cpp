#include <iostream>
#include <cassert>

#include "include/lineParser.hpp"

bool lineParser::checkIfStringShouldBeSurpressed(std::string &line) const
{
  bool surpressString = false;
  for (const auto entry : _ignoreLineContainingString)
    if (line.find(entry) != std::string::npos)
      surpressString = true;
  return surpressString;
}

void lineParser::checkForAnyDelimiterInCurrentLine(std::string &line) const
{
  for (const auto delimiterTuple : _delimiters)
  {
    const auto start = std::get<0>(delimiterTuple);
    const auto end = std::get<1>(delimiterTuple);
    const auto replaceBy = std::get<2>(delimiterTuple);
    removeContentBetweenDelimiter(start, end, replaceBy, line);
  }
}

void lineParser::checkIfStringRequiresStyleAdjustment(std::string &line) const
{
  for (const auto entry : _keywordToStyle)
    if (line.find(entry.getKeyword()) != std::string::npos)
      applyLineFormating(entry, line);
}

void lineParser::removeContentBetweenDelimiter(const std::string &startDelimiter, const std::string &endDelimiter,
  const std::string &replaceBy, std::string &line) const
{
  // replace types by <...>
  long unsigned pos = 0;
  long unsigned length = 0;
  int count = 0;
  bool containsDelimiters = false;
  long unsigned i = 0;
  long unsigned lineLength = line.length();
  for (i = 0; i < lineLength; ++i) {
    if (line.substr(i, startDelimiter.length()) == startDelimiter)
    {
      if (!containsDelimiters)
      {
        pos = i;
        containsDelimiters = true;
      }
      count++;
    }
    if (line.substr(i, endDelimiter.length()) == endDelimiter)
      count--;
    if (containsDelimiters && count == 0)
    {
      length = i - pos + 1;
      line = line.replace(pos, length, startDelimiter + replaceBy + endDelimiter);
      containsDelimiters = false;
      i = pos + startDelimiter.length() + replaceBy.length() + endDelimiter.length();
      lineLength = line.length();
    }
  }
}

void lineParser::applyLineFormating(const styling &style, std::string &line) const
{
  const auto keyword = style.getKeyword();
  const auto applyAtLocation = style.getStylingLocation();
  const auto color = style.getColor();
  const auto lineStyle = style.getStyle();

  assert((applyAtLocation == std::string("preKeyword") || applyAtLocation == std::string("onKeyword") ||
    applyAtLocation == std::string("postKeyword") || applyAtLocation == std::string("everywhere")) &&
    "Could not determine where to apply line formating.");

  const auto position = line.find(keyword);
  const auto length = keyword.length();

  if (position != std::string::npos)
  {
    if (applyAtLocation == std::string("preKeyword"))
      line = lineStyle + color + line.substr(0, position) + format::NORMAL + color::WHITE + line.substr(position);
    else if (applyAtLocation == std::string("onKeyword"))
      line = line.substr(0, position) + lineStyle + color + keyword + format::NORMAL + color::WHITE +
        line.substr(position + length);
    else if (applyAtLocation == std::string("postKeyword"))
      line = line.substr(0, position + length) + lineStyle + color + line.substr(position + length) + format::NORMAL +
        color::WHITE;
    else if (applyAtLocation == std::string("everywhere"))
      line = lineStyle + color + line + format::NORMAL + color::WHITE;
  }
  // auto pos   = line.find("Processing");
  // int length = 10;
  // if (pos != std::string::npos) {
  //   line = line.substr(0, pos + length) + BLUE + BOLD + line.substr(pos + length, line.size() - (pos + length)) + NORMAL + WHITE;
  //   returnValue = OK;
  // }

  // pos = line.find("Waf: Entering directory");
  // if (pos != std::string::npos) {
  //   line = GREEN + line + WHITE;
  //   returnValue = OK;
  // }
}