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
    const auto mustContain = std::get<3>(delimiterTuple);
    removeContentBetweenDelimiter(start, end, replaceBy, mustContain, line);
  }
}

void lineParser::checkIfStringRequiresStyleAdjustment(std::string &line, bool &containsKeyword,
  bool &surpressKeyword) const
{
  for (const auto &entry : _keywordToStyle)
    if (line.find(entry.getKeyword()) != std::string::npos)
      applyLineFormating(entry, line, containsKeyword, surpressKeyword);
}

void lineParser::removeContentBetweenDelimiter(const std::string &startDelimiter, const std::string &endDelimiter,
  const std::string &replaceBy, const std::string mustContain, std::string &line) const
{
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
    bool contentShouldBeRemoved = true;
    if (mustContain.length() != 0)
      contentShouldBeRemoved = line.find(mustContain) != std::string::npos;
    if (containsDelimiters && count == 0 && contentShouldBeRemoved)
    {
      length = i - pos + 1;
      line = line.replace(pos, length, startDelimiter + replaceBy + endDelimiter);
      containsDelimiters = false;
      i = pos + startDelimiter.length() + replaceBy.length() + endDelimiter.length();
      lineLength = line.length();
    }
  }
}

void lineParser::applyLineFormating(const styling &style, std::string &line, bool &containsKeyword,
  bool &surpressKeyword) const
{
  const auto keyword = style.getKeyword();
  const auto gatherStatistics = style.getGatherStatistics();
  const auto removeDuplicates = style.getRemoveDuplicatesFlag();
  const auto applyAtLocation = style.getStylingLocation();
  const auto color = style.getColor();
  const auto lineStyle = style.getStyle();

  assert((applyAtLocation == std::string("preKeyword") || applyAtLocation == std::string("onKeyword") ||
    applyAtLocation == std::string("postKeyword") || applyAtLocation == std::string("everywhere")) &&
    "Could not determine where to apply line formating.");

  containsKeyword = false;
  surpressKeyword = style.getSurpressKeywordFlag();

  // check if string already printed to screen and whether we want to surpress it or not
  if (removeDuplicates)
  {
    const auto messages = style.getRecordedStrings();
    const auto found = std::find(messages.begin(), messages.end(), line);
    if (found != messages.end())
    {
      surpressKeyword = true;
    }
  }

  // if we want to get some statistics about the current line, we need to store it to process it later
  if (gatherStatistics || removeDuplicates)
    style.writeLineContainingKeyword(line);

  const auto position = line.find(keyword);
  const auto length = keyword.length();

  if (position != std::string::npos)
  {
    containsKeyword = true;
    if (applyAtLocation == std::string("preKeyword"))
      line = lineStyle + color + line.substr(0, position) + format::NORMAL + color::NEUTRAL + line.substr(position);
    else if (applyAtLocation == std::string("onKeyword"))
      line = line.substr(0, position) + lineStyle + color + keyword + format::NORMAL + color::NEUTRAL +
        line.substr(position + length);
    else if (applyAtLocation == std::string("postKeyword"))
      line = line.substr(0, position + length) + lineStyle + color + line.substr(position + length) + format::NORMAL +
        color::NEUTRAL;
    else if (applyAtLocation == std::string("everywhere"))
      line = lineStyle + color + line + format::NORMAL + color::NEUTRAL;
  }
}