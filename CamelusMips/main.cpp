#include <iostream>
#include "Options.hpp"
#include "System.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    Options opt(argc, argv);
    System soc(opt);
}
