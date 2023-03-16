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
        int from, to;
        char symbol;
        fin >> from >> to >> symbol;
        this->graph[from][symbol] = to;
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
        std::stack<int> path;
        if (verify(word, start_state, path)) {
            fout << "DA\n";
            std::cout << word << ": ";
            while (!path.empty()) {
                std::cout << path.top() << " ";
                path.pop();
            }
            std::cout << "\n";
        } else {
            fout << "NU\n";
        }
    }
}

bool DFA::verify(const std::string &word, int state, std::stack<int> &path) {
    if (word.empty()) {
        return states[state];
    }

    char symbol = word[0];

    std::string next_word = word.substr(1, word.size() - 1);

    if (graph[state].find(symbol) != graph[state].end()) {
        path.push(graph[state][symbol]);
        return verify(next_word, graph[state][symbol], path);
    }

    return false;
}
