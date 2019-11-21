#include <iostream>
#include <signal.h>

#include "jsonParser.hpp"

#include "include/format.hpp"
#include "include/color.hpp"
#include "include/fileReader.hpp"
#include "include/processCommandLineArguments.hpp"
#include "include/lineParser.hpp"

void sighandler(int sig = 0) {
  std::exit(0);
}

int main(int argc, char **argv)
{
  // handle user-interruption
  signal(SIGINT, &sighandler);

  const processCommandLineArguments comArgs(argc, argv);
  fileReader styleFile(comArgs.getLocationOfStyleFile());
  styleFile.read();
  lineParser parser(styleFile.getParameters());

  // listen to input from the command line
  std::string line;
  bool surpressString = false;
  while (std::cin) {
    surpressString = false;
    std::getline(std::cin, line);
    surpressString = parser.checkIfStringShouldBeSurpressed(line);
    parser.checkForAnyDelimiterInCurrentLine(line);
    parser.checkIfStringRequiresStyleAdjustment(line);
    if (!surpressString)
      std::cout << line << std::endl;
  }
  return 0;
}