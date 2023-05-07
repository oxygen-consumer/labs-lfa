#include "src/DFA/DFA.hpp"
#include "src/NFA/NFA.hpp"
#include <iostream>


int main() {
    NFA nfa("nfa.txt");
    DFA dfa(nfa);

    std::fstream fin("words.txt");
    std::string word;
    while (fin >> word) {
        std::cout << word << ": " << (dfa.verify(word) ? "DA" : "NU") << " " << (nfa.verify(word) ? "DA" : "NU")
                  << "\n";
    }
}
