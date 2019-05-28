#include "InPicture.h"

#include <iostream>
#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int InPicture::run(int argc, char **argv) noexcept {
  try {
    po::variables_map variablesMap{};
    po::options_description optionsDescription{"Allowed options"};

    try {
      auto conflictingOptions = [&variablesMap](std::string first, std::string second) {
        if (variablesMap.count(first) && !variablesMap[first].defaulted() &&
            variablesMap.count(second) && !variablesMap[second].defaulted())
          throw std::logic_error{"conflicting options - '--" + first + "' and '--" + second + "'"};
      };

      auto dependingOption = [&variablesMap](std::string dependent, std::string dependency) {
        if (variablesMap.count(dependent) && !variablesMap[dependent].defaulted())
          if (variablesMap.count(dependency) == 0 || variablesMap[dependency].defaulted())
            throw std::logic_error{"option '--" + dependent + "' requires option '--" + dependency + "' to be set"};
      };

      optionsDescription.add_options()
          ("help,h", "print help for program")
          ("version,v", "print version and author")
          ("combine,c", "combine data with image")
          ("decombine,d", "decombine data from image")
          ("image,i", po::value<std::string>(), "image file path")
          ("secret,s", po::value<std::string>(), "secret file path")
          ("method,m", po::value<std::string>(), "data joining method");

      po::store(po::parse_command_line(argc, argv, optionsDescription), variablesMap);

      conflictingOptions("combine", "decombine");

      conflictingOptions("decombine", "data");
      conflictingOptions("decombine", "method");

      dependingOption("combine", "image");
      dependingOption("combine", "secret");
      dependingOption("combine", "method");

      dependingOption("decombine", "image");

    } catch (const std::exception &exception) {
      std::cerr << "Program parameter error (" << exception.what() << ")" << std::endl;
      return -1;
    }

    if (variablesMap.count("help"))
      std::cout << optionsDescription << std::endl;

    if (variablesMap.count("version"))
      std::cout << "InPicture version 1.0. Philipp Baszuk 2019. MIT License. " << std::endl;


  } catch (const std::exception &exception) {
    std::cerr << "An error occurred (" << exception.what() << ")" << std::endl;
    return -1;
  } catch (...) {
    std::cerr << "An unknown error occurred" << std::endl;
    return -1;
  }

  return 0;
}
