//
// Created by Zaha on 3/16/2023.
//

#include "E_NFA.hpp"

E_NFA::E_NFA(const std::string &input_file, const std::string &output_file) {
    fin.open(input_file);
    fout.open(output_file);

    build();
}

void E_NFA::build() {
    int tmp;

    // read the final_states
    fin >> tmp; // num of final_states
    while (tmp--) {
        int state;
        fin >> state;
        // create a new state and mark it as non-final
        final_states[state] = false;
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

    // get initial state
    fin >> tmp;
    start_states.insert(tmp);

    // read final final_states
    fin >> tmp;
    while (tmp--) {
        int s;
        fin >> s;
        final_states[s] = true; // mark it as final
    }

    transform_to_nfa();
}

void E_NFA::epsilon_closure(int state, std::set<int> &closure) {
    for (auto &transition: graph[state]) {
        // epsilon (lambda) transitions are represented by the symbol 'L'
        if (transition.first == 'L') {
            if (closure.find(transition.second) == closure.end()) {
                closure.insert(transition.second);
                epsilon_closure(transition.second, closure);
            }
        }
    }
}

void E_NFA::clean_graph() {
    // remove duplicate transitions
    for (auto &state: final_states) {
        std::set<std::pair<char, int>> transitions;
        for (auto &transition: graph[state.first]) {
            transitions.insert(transition);
        }
        graph[state.first] = {};
        for (auto &transition: transitions) {
            graph[state.first].insert(transition);
        }
    }
}

void E_NFA::transform_to_nfa() {
    // first we complete the graph with epsilon transitions
    for (auto &state: final_states) {
        std::set<int> closure;
        epsilon_closure(state.first, closure);
        for (auto &c: closure) {
            graph[state.first].insert(std::make_pair('L', c));
        }
    }

    // then we transform the E-NFA to NFA
    for (auto &state: final_states) {
        for (auto &transition: graph[state.first]) {
            if (transition.first == 'L') {
                // we add the transitions from the state to which the epsilon transition leads
                for (auto &t: graph[transition.second]) {
                    graph[state.first].insert(t);
                }

                // we add the final final_states from the state to which the epsilon transition leads
                final_states[state.first] = final_states[state.first] || final_states[transition.second];

                // if the current state is a start state, then the final_states to which the epsilon transition leads are also start final_states
                if (start_states.find(state.first) != start_states.end()) {
                    start_states.insert(transition.second);
                }
            }
        }

        // we remove the epsilon transitions
        graph[state.first].erase('L');
    }

    clean_graph();
}

void E_NFA::run() {
    int words;
    fin >> words;

    while (words--) {
        std::string word;
        fin >> word;
        bool ok = false;
        for (auto &state: start_states) {
            if (verify(word, state)) {
                ok = true;
                break;
            }
        }
        if (ok) {
            fout << "DA\n";
        } else {
            fout << "NU\n";
        }
    }
}

bool E_NFA::verify(const std::string &word, int state) {
    // same as in NFA science we transform the E-NFA to NFA

    if (word.empty()) {
        return final_states[state];
    }

    char symbol = word[0];

    for (auto &transition: graph[state]) {
        if (transition.first == symbol) {
            if (verify(word.substr(1), transition.second)) {
                return true;
            }
        }
    }

    return false;
}