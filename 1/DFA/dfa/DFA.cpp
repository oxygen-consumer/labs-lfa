//
// Created by Zaha on 3/11/2023.
//

#include "DFA.hpp"

DFA::DFA(const std::string& input_filename, const std::string& output_filename) {
    this->fin.open(input_filename);
    this->fout.open(output_filename);

    this->build();
}

void DFA::build() {
    int tmp;

    // read the states
    fin >> tmp; // num of states
    while (tmp--) {
        int state;
        fin >> state;
        // create a new state in the map and mark it as non-final
        states[state] = false;
    }

    // read transitions
    fin >> tmp; // num of transitions
    while (tmp--) {
        int x, y;
        char l;
        fin >> x >> y >> l;
        this->graph[x][l] = y;
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

void DFA::run() {
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

bool DFA::verify(const std::string &word, int state) {
    char l = word[0];
    bool done = word.size() == 1;

    std::string next_word = word.substr(1, word.size() - 1);

    int next_state;
    try {
        next_state = graph.at(state).at(l);
    } catch (std::out_of_range &e) {
        return false;
    };

    if (done) {
        return states[next_state];
    }
    return verify(next_word, next_state);
}
