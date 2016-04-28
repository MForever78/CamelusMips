#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include "boost/program_options.hpp"
#include "easylogging++.h"

namespace po = boost::program_options;

class Options {
public:
    Options() {};
    Options(int argc, char *argv[]) {
        po::options_description desc("Supported options");
        desc.add_options()
            ("debug,d", po::bool_switch()->default_value(false),      "Enable debug mode")
            ("file,f", po::value<std::string>(&filePath),             "Assign assembly file")
            ("help,h",                                                "This help message");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            exit(0);
        }

        debug = vm["debug"].as<bool>();
    }

    bool debug = false;
    std::string filePath;

private:

};

#endif