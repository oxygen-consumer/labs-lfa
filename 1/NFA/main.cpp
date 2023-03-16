#include "nfa/NFA.hpp"

int main() {
    NFA nfa("input.txt", "output.txt");
    nfa.run();
    return 0;
}
