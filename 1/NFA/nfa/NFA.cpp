//
// Created by Zaha on 3/16/2023.
//

#include "NFA.hpp"

NFA::NFA(const std::string &input_file, const std::string &output_file) {
    fin.open(input_file);
    fout.open(output_file);

    build();
}

void NFA::build() {
    int tmp;

    // read the states
    fin >> tmp; // num of states
    while (tmp--) {
        int state;
        fin >> state;
        // create a new state and mark it as non-final
        states[state] = false;
    }

    // read transitions
    fin >> tmp; // num of transitions
    while (tmp--) {
        int from, to;
        char symbol;
        fin >> from >> to >> symbol;
        // add the transition to the graph
        graph[from].insert(std::make_pair(symbol, to));
    }

    fin >> start_state;

    // read final states
    fin >> tmp;
    while (tmp--) {
        int s;
        fin >> s;
        states[s] = true; // mark it as final
    }
}

void NFA::run() {
    int words;
    fin >> words;

    while (words--) {
        std::string word;
        fin >> word;
        if (verify(word, start_state)) {
            fout << "DA\n";
        } else {
            fout << "NU\n";
        }
    }
}

bool NFA::verify(const std::string &word, int state) {
    if (word.empty()) {
        return states[state];
    }

    char symbol = word[0];
    std::string rest = word.substr(1);

    // run verify for all the states that can be reached from the current state
    for (auto &transition : graph[state]) {
        if (transition.first == symbol) {
            if (verify(rest, transition.second)) {
                return true;
            }
        }
    }

    return false;
}