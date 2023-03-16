#include <string>
#include "dfa/DFA.hpp"

const std::string input_filename = "input.txt";
const std::string output_filename = "output.txt";

int main() {
    DFA dfa(input_filename, output_filename);
    dfa.run();
    return 0;
}
