#include "e-nfa/E_NFA.hpp"

int main() {
    E_NFA e_nfa("input.txt", "output.txt");
    e_nfa.run();
    return 0;
}
