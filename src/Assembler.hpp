#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <vector>
#include <cstdint>

class Assembler {
public:
    Assembler() {};
    Assembler(std::vector<std::string> &instOriginal);

    extern const int RS, RT, RD;

private:
    std::vector<std::string> instOriginal;
    std::vector<uint32_t> instAssembled;
}

#endif