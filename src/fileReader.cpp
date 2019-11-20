#include <fstream>

#include "include/fileReader.hpp"

void fileReader::read()
{
  std::ifstream input(_filename);
  assert(input.is_open());

  std::string content = "";
  std::string line;
  while(getline(input, line))
    content += line;
  input.close();

  jsonObject = nlohmann::json::parse(content);
}

const nlohmann::json &fileReader::getJSON() const
{
  return jsonObject;
}