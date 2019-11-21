#ifndef PROCESSCOMMANDLINEARGUMENTS_HPP
#define PROCESSCOMMANDLINEARGUMENTS_HPP

#include <iostream>
#include <string>

class processCommandLineArguments
{
  public:
    processCommandLineArguments(unsigned numArguments, char **arguments) : _numArguments(numArguments),
      _arguments(arguments)
    {
      // check if the user only wants to see the help section
      if (_numArguments > 1)
      {
        if (std::string(_arguments[1]) == "-h" || std::string(_arguments[1]) == "--help")
        {
          printHelp();
          std::exit(0);
        }
      }
      setArguments();
    }

    /// get the path and name of the json file
    std::string getStyleFile() const;

  private:
    /// print help to screen
    void printHelp();

    /// store the command line arguments
    void setArguments();

  private:
    /// number of command line arguments passed to program
    const unsigned _numArguments;

    /// actual command line arguments
    char **_arguments;

    /// path and filename of JSON file
    std::string _jsonFile = "";
};

#endif