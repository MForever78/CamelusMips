#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include "Assembler.hpp"

using namespace std;

int main() {
    const string inst_sample[] = {
        "add  $t0, $zero, $zero",
        "addi $t1, $t0, 1",
        "add  $t2, $t1, $t1"
    };

    vector<string> inst(inst_sample, inst_sample + sizeof(inst_sample) / sizeof(string));
    Assembler assembler(inst);
    cout << assembler << endl;
}