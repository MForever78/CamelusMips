#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    const int inst_sample[] = {

    };

    vector<int> inst(cbegin(inst_sample), cend(inst_sample));

    Simulator simulator;

    simulator.exec(&inst);
}