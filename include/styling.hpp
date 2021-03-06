#ifndef STYLING_HPP
#define STYLING_HPP

#include <vector>
#include <string>

#include <iostream>

#include "include/color.hpp"
#include "include/format.hpp"

/// this class defines the properties of how content should be formated if it contains a given keywords
class styling
{
  public:
    styling(const std::string keyword, const bool gatherStatistics, const std::string applyStyling,
      const std::string color, const std::string style, const bool surpressKeyword, const bool removeDuplicates)
      : _keyword(keyword), _gatherStatistics(gatherStatistics), _applyStyling(applyStyling), _color(color),
      _style(style), _surpressKeyword(surpressKeyword), _removeDuplicates(removeDuplicates)
    { }

    /// get the keyword
    const std::string &getKeyword() const;

    /// get flag if statistics should be gathered
    const bool &getGatherStatistics() const;

    /// get the location at which to apply the styling
    const std::string &getStylingLocation() const;

    /// get the color
    const std::string &getColor() const;

    /// get the style / format
    const std::string &getStyle() const;

    /// get the surpress keyword flag
    const bool &getSurpressKeywordFlag() const;

    /// get the remove duplicates flag
    const bool &getRemoveDuplicatesFlag() const;

    /// get the vector containing all recorded strings
    const std::vector<std::string> &getRecordedStrings() const;

    /// write a line containing the keyword to the occurance container
    void writeLineContainingKeyword(std::string line) const;

  private:
    /// keyword to detect if a line gets formated
    const std::string _keyword;

    /// flag indicating if statistics should be calculated for the current keyword (number of occurances)
    const bool _gatherStatistics;

    /// indicate where the styling should be applied, i.e. for the keyword itself, before or after it or everywhere
    const std::string _applyStyling;

    /// string containing the ascii color code
    const std::string _color;

    /// string containing the ascii format / style code
    const std::string _style;

    /// flag indicating to surpress output individually
    const bool _surpressKeyword;

    /// flag indicating if duplicate strings should be removed
    const bool _removeDuplicates;

    /// container of all the lines containing the keyword
    mutable std::vector<std::string> _occurances;
};

#endif