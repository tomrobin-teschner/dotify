#include <iostream>
#include <signal.h>

#include "include/jsonParser.hpp"

#include "include/format.hpp"
#include "include/color.hpp"
#include "include/fileReader.hpp"
#include "include/processCommandLineArguments.hpp"
#include "include/lineParser.hpp"

int main(int argc, char **argv)
{
  // handle user-interruption
  signal(SIGINT, [](int sig = 0){std::exit(sig);});

  const processCommandLineArguments comArgs(argc, argv);
  fileReader styleFile(comArgs.getLocationOfStyleFile());
  styleFile.read();
  lineParser parser(styleFile.getParameters());

  // listen to input from the command line
  std::string line;
  bool surpressString = false;
  bool surpressStringLocally = false;
  bool containsKeyword = false;
  bool printOnlyStringContainingKeywords = comArgs.getKeywordsOnlyFlag();
  while (std::cin) {
    surpressString = false;
    containsKeyword = false;
    std::getline(std::cin, line);
    surpressString = parser.checkIfStringShouldBeSurpressed(line);
    if (!surpressString)
    {
      parser.checkForAnyDelimiterInCurrentLine(line);
      parser.checkIfStringRequiresStyleAdjustment(line, containsKeyword, surpressStringLocally);
      if (!printOnlyStringContainingKeywords && !surpressStringLocally)
        std::cout << line << std::endl;
      else if (printOnlyStringContainingKeywords && containsKeyword && !surpressStringLocally)
        std::cout << line << std::endl;
    }
  }
  return 0;
}