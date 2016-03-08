#include <string>
#include <iostream>
#include <sstream>

#include "Exporter.hpp"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include "Assembler.hpp"
#include "Assembly.hpp"

using namespace std;

const int Exporter::COE = 0;
const int Exporter::HEX = 1;
const int Exporter::BIN = 2;
const int Exporter::ASCIIBIN = 3;

void Exporter::exportToFile(const Assembler &assembler, const string &filePath, const int type) {
    boost::filesystem::path fileDir(filePath);
    boost::filesystem::ofstream ofs;

    vector<Assembly> assemblies = assembler.getInstAssembled();

    if (boost::filesystem::exists(filePath)) {
        if (boost::filesystem::is_regular_file(filePath)) {
            if (type == BIN) {
                ofs.open(filePath, ofstream::binary | ofstream::trunc);
            } else {
                ofs.open(filePath, ofstream::trunc);
            }
            exportAssembly(assemblies, ofs, type);
            ofs.close();
        }
    } else {
        throw runtime_error("Cannot open file to write: " + filePath);
    }
}

void Exporter::exportAssembly(const vector<Assembly> &assemblies, ostream &os, const int type) {
    switch(type) {
        case COE:
            os << "memory_initialization_radix=16;\n";
            os << "memory_initialization_vector=\n";
            for (int i = 0; i < assemblies.size() - 1; ++i)
                os << assemblies[i].toHex() << ",\n";
            os << assemblies.back().toHex() + ";" << endl;
            break;

        case HEX:
            for (auto assembly: assemblies)
                os << assembly.toHex() << endl;
            break;

        case BIN:
            for (auto assembly: assemblies)
                os.write(assembly.toBinaryBlocks(), 4);
            break;

        case ASCIIBIN:
            for (auto assembly: assemblies)
                os << assembly << endl;
            break;
    }

}
