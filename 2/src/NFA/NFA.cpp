//
// Created by zaha on 5/4/23.
//

#include "NFA.hpp"

NFA::NFA(const std::string &input_file) {
    fin.open(input_file);
    read();
}

void NFA::read() {
    size_t tmp;

    // read the states
    fin >> tmp; // num of states
    while (tmp--) {
        std::string state;
        fin >> state;
        // create a new state and mark it as non-final
        states[state] = false;
    }

    // read transitions
    fin >> tmp; // num of transitions
    while (tmp--) {
        std::string from, to;
        char symbol;
        fin >> from >> to >> symbol;
        // add the transition to the graph
        graph[from].insert(std::make_pair(symbol, to));

        // add the symbol to the alphabet
        symbols.insert(symbol);
    }

    fin >> start_state;

    // read final states
    fin >> tmp; // num of final states
    while (tmp--) {
        std::string s;
        fin >> s;
        states[s] = true; // mark it as final
    }
}

bool NFA::verify(const std::string &word) {
    return dfs(word, start_state);
}

bool NFA::dfs(std::string word, const std::string& state) {
    if (word.empty()) {
        return states[state];
    }

    for (auto& [symbol, next_state] : graph[state]) {
        if (symbol == word[0]) {
            if (dfs(word.substr(1), next_state)) {
                return true;
            }
        }
    }

    return false;
}

const std::map<std::string, std::multimap<char, std::string>> NFA::get_graph() const {
    return graph;
}
