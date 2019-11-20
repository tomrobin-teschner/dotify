#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <string>

#include "include/jsonParser.hpp"

class fileReader {

  public:
    fileReader(std::string filename) : _filename(filename) { }

    /// read the content of the json file
    void read();

    /// get the processed json object
    const nlohmann::json &getJSON() const;

  private:
    /// filename and location of the style file
    const std::string _filename;

    /// json object containing style information
    nlohmann::json jsonObject;

};

#endif