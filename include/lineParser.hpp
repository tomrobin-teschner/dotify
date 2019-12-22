#ifndef LINEPARSER_HPP
#define LINEPARSER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <tuple>

#include "include/jsonParser.hpp"
#include "include/styling.hpp"

/// this class checks a if a given line requires formating and returns the final string that should be printed to screen
class lineParser
{
  public:
    lineParser(const nlohmann::json &jsonArgs) : _jsonArgs(jsonArgs)
    {
      if (_jsonArgs.find("ignoreCompleteLineIfItContainsSubstring") != _jsonArgs.end())
      {
        for (const auto entry : _jsonArgs["ignoreCompleteLineIfItContainsSubstring"])
          _ignoreLineContainingString.push_back(entry);
      }

      if (_jsonArgs.find("styleLineContainingKeywords") != _jsonArgs.end())
      {
        for (const auto entry : _jsonArgs["styleLineContainingKeywords"])
        {
          assert(entry.count("keyword") != 0 && "No keyword defined in styleLineContainingKeywords");
          assert(entry.count("applyStyle") != 0 && "No style defined in styleLineContainingKeywords");

          const std::string keyword = entry["keyword"];
          const bool gatherStatistics = entry.count("gatherStatistics") == 0 ? false :
            static_cast<const bool>(entry["gatherStatistics"]);
          const std::string applyStyle = entry["applyStyle"];
          const std::string color = entry.count("color") == 0 ? std::string("white") :
            static_cast<const std::string>(entry["color"]);
          const std::string style = entry.count("style") == 0 ? std::string("normal") :
            static_cast<const std::string>(entry["style"]);
          const bool surpressKeyword = entry.count("surpressKeyword") == 0 ? false :
            static_cast<const bool>(entry["surpressKeyword"]);
          const bool removeDuplicates = entry.count("removeDuplicates") == 0 ? false :
            static_cast<const bool>(entry["removeDuplicates"]);

          _keywordToStyle.push_back(styling(keyword, gatherStatistics, applyStyle, color, style, surpressKeyword,
            removeDuplicates));
        }
      }

      if (_jsonArgs.find("ignoreContentBetweenDelimiter") != _jsonArgs.end())
      {
        for (const auto entry : _jsonArgs["ignoreContentBetweenDelimiter"])
        {
          assert(entry.count("startingDelimiter") != 0 && "No delimiter defined in ignoreContentBetweenDelimiter");
          assert(entry.count("endingDelimiter") != 0 && "No delimiter defined in ignoreContentBetweenDelimiter");
          const std::string start = entry["startingDelimiter"];
          const std::string end = entry["endingDelimiter"];
          const std::string replaceBy = entry.count("replaceContentBy") == 0 ? std::string("...") :
            static_cast<const std::string>(entry["replaceContentBy"]);
          const std::string mustContain = entry.count("mustContain") == 0 ? std::string("") :
            static_cast<const std::string>(entry["mustContain"]);

          _delimiters.push_back(std::make_tuple(start, end, replaceBy, mustContain));
        }
      }
    }

    /// check if the current line contains strings that should not be printed to screen
    bool checkIfStringShouldBeSurpressed(std::string &line) const;

    /// check if any delimiter is contained within the current line
    void checkForAnyDelimiterInCurrentLine(std::string &line) const;

    /// check if the current line requires formating
    void checkIfStringRequiresStyleAdjustment(std::string &line, bool &containsKeyword, bool &surpressKeyword) const;

    /// print statistics

  private:
    /// check if the current line contains delimiter between which the content is supposed to be removed
    void removeContentBetweenDelimiter(const std::string &startDelimiter, const std::string &endDelimiter,
      const std::string &replaceBy, const std::string mustContain, std::string &line) const;

    /// apply color and formating to line
    void applyLineFormating(const styling &style, std::string &line, bool &containsKeyword, bool &surpressKeyword)
      const;

  private:
    /// the json object containing all required styling information
    const nlohmann::json &_jsonArgs;

    /// vector that holds all strings which, if present, will trigger a line to be surpressed from the output
    std::vector<std::string> _ignoreLineContainingString;

    /// vector that specifies which keywords to format and style as well as how to
    std::vector<styling> _keywordToStyle;

    /// vector containing the delimiters between which the content is reduced to a user-defined string
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> _delimiters;
};

#endif