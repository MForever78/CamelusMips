#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <vector>
#include <cstdint>
#include <iostream>
#include <regex>
#include <map>

#include "Assembly.hpp"

class Assembler {
public:
    Assembler();
    explicit Assembler(const std::vector<std::string> &instOriginal);

    // getter
    std::vector<Assembly> getInstAssembled() const;
    std::map<std::string, int> getSymbolTable() const;
    std::vector<std::string> getInstTrimmed() const;

    friend std::ostream &operator<<(std::ostream &os, const Assembler &assembler);

private:
    const static std::regex rTypeExp;
    const static std::regex iTypeExp;
    const static std::regex jTypeExp;

    const static std::regex branchExp;
    const static std::regex jumpExp;

    const static std::regex immExp;
    const static std::regex labelExp;
    const static std::regex operandExp;
    const static std::regex operandsExp;
    const static std::regex operandWithImmExp;
    const static std::regex operandsWithAddrExp;
    const static std::regex operandsWithImmExp;
    const static std::regex operandsWithLabelExp;
    const static std::map<std::string, int> funcMap;
    const static std::map<std::string, int> opcodeMap;

    std::vector<std::string> instTrimmed;
    std::vector<Assembly> instAssembled;
    std::map<std::string, int> symbolTable;

    std::uint32_t getOperand(const std::string &operandName);
    Assembly getRTypeAssembly(const std::string &inst, const std::smatch &match);
    Assembly getITypeAssembly(const std::string &inst, const std::smatch &match);
    Assembly getJTypeAssembly(const std::string &inst, const std::smatch &match);
    
    /**
     * @brief Generate symbol table and trim the instructions by the way
     *  
     * @param inst Instruction set
     * @return Generated symbol table
     */
    std::map<std::string, int> generateSymbolTable(std::vector<std::string> &inst);

    /**
     * @brief Trim instruction comment and whitespace on both end
     * 
     * @param inst A single instruction string
     */
    void trimComment(std::string &inst);

    /**
     * @brief Substitute labels with absolute or relative address accordingly
     * 
     * @param inst Instruction set with symbol table generated
     */
    void substituteLabels(std::vector<std::string> &inst);
};

#endif
