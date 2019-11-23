#include <iostream>
#include <cassert>

#include "include/processCommandLineArguments.hpp"

void processCommandLineArguments::printHelp()
{
  std::cout << "This program removes unwanted strings from screen while reformating strings of interest" << std::endl;
  std::cout << std::endl;
  std::cout << "Usage: To invoke the parser on a text file use" << std::endl;
  std::cout << std::endl;
  std::cout << "   cat fileName | parser" << std::endl;
  std::cout << std::endl;
  std::cout << "Alternatively, you can invoke a command that produces output to the screen which should be parsed, ";
  std::cout << "and then pass that text to a log file which is then parsed, as:" << std::endl;
  std::cout << std::endl;
  std::cout << "   commandToInvoke | tee log | parser" << std::endl;
  std::cout << std::endl;
  std::cout << "If the intermediate log file is not required, the tee command may be ommitted." << std::endl;
  std::cout << std::endl;
  std::cout << "-h,  --help:             Prints this help section" << std::endl;
  std::cout << "-f,  --file:             JSON file containing formating instructions" << std::endl;
  std::cout << "-k,  --keywordsOnly:     Only output string to terminal which contain keywords" << std::endl;
}

void processCommandLineArguments::setArguments()
{
  for (unsigned argIndex = 1; argIndex < _numArguments; ++argIndex)
  {
    if (std::string(_arguments[argIndex]) == "-f" || std::string(_arguments[argIndex]) == "--file")
      _jsonFile = _arguments[argIndex + 1];
    if (std::string(_arguments[argIndex]) == "-k" || std::string(_arguments[argIndex]) == "--keywordsOnly")
      _keywordsOnly = true;
  }
}

std::string processCommandLineArguments::getLocationOfStyleFile() const
{
  assert(_jsonFile.length() != 0);
  return _jsonFile;
}

bool processCommandLineArguments::getKeywordsOnlyFlag() const
{
  return _keywordsOnly;
}