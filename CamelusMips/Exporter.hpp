#ifndef EXPORTER_HPP
#define EXPORTER_HPP

#include <string>
#include <vector>
#include "Assembler.hpp"
#include "Assembly.hpp"

class Exporter {
public:
    void exportToFile(const Assembler &assembler, const std::string &filePath, const int type);
    void exportAssembly(const std::vector<Assembly> &assemblies, std::ostream &os, const int type);

    static const int COE;
    static const int HEX;
    static const int BIN;
    static const int ASCIIBIN;
};

#endif