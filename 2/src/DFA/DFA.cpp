//
// Created by zaha on 5/4/23.
//

#include "DFA.hpp"

DFA::DFA(const NFA &nfa) {
    if (nfa.get_states().size() >= MAX_STATES) {
        throw std::runtime_error("Too many states");
    }

    this->symbols = nfa.get_symbols();

    // convert start state
    std::bitset<MAX_STATES> tmp;
    tmp.set(stoi(nfa.get_start_state()));
    this->start_state = tmp.to_string();
    states[this->start_state] = nfa.get_states().at(nfa.get_start_state());

    // add dead state
    std::bitset<MAX_STATES> dead_state;
    dead_state.set(MAX_STATES - 1);
    auto dead_state_str = dead_state.to_string();
    states[dead_state_str] = false;
    for (auto symbol: symbols) {
        graph[dead_state_str][symbol] = dead_state_str;
    }

    transform(nfa);
    minimize();
}

void DFA::transform(const NFA &nfa) {
    // TODO: this function is big, split it into smaller functions

    auto const &nfa_graph = nfa.get_graph();
    auto const &nfa_states = nfa.get_states();

    std::queue<std::string> q;
    q.push(start_state);

    // send help
    while (!q.empty()) {
        auto current_state = q.front();
        q.pop();

        std::bitset<MAX_STATES> current_state_bitset(current_state);
        bool is_final = false;

        // for each symbol calculate the next state
        for (char symbol: symbols) {
            std::bitset<MAX_STATES> next_state;

            // for each state in the current state
            for (size_t i = 0; i < MAX_STATES; ++i) {
                if (current_state_bitset[i]) {
                    // check if there is a transition from i to another state
                    std::multimap<char, std::string> transitions;
                    try {
                        transitions = nfa_graph.at(std::to_string(i));
                    } catch (std::out_of_range &e) {
                        continue;
                    }

                    // for each transition from i
                    for (auto &transition: transitions) {
                        if (transition.first == symbol) {
                            // add the transition to the next state
                            next_state.set(stoi(transition.second));
                            is_final |= nfa_states.at(transition.second);
                        }
                    }
                }
            }

            // if the next state is empty then its dead
            if (next_state.none()) {
                next_state.set(MAX_STATES - 1);
            }

            auto next_state_str = next_state.to_string();
            graph[current_state][symbol] = next_state_str;

            // if the next state is not in the states set, add it
            if (states.find(next_state_str) == states.end()) {
                states[next_state_str] = is_final;
                q.push(next_state_str);
            }
        }
    }
}

void DFA::minimize() {
    // there is no unreachable states in the DFA, so we can skip that step, I took care of it in the transform function

    // split the states into final and non-final
    std::vector<std::string> final_states, non_final_states;
    for (auto &state: states) {
        if (state.second) {
            final_states.emplace_back(state.first);
        } else {
            non_final_states.emplace_back(state.first);
        }
    }

    // find similar states with backtracking
    std::map<std::string, std::string> to_replace;

    for (auto states_group: {final_states, non_final_states}) {
        for (auto it = states_group.begin(); it != states_group.end(); ++it) {
            // if the state is already in the to_replace map, continue
            if (to_replace.find(*it) != to_replace.end()) {
                continue;
            }

            for (auto it2 = it + 1; it2 != states_group.end(); ++it2) {
                // if the states are not similar, continue
                if (graph[*it] != graph[*it2]) {
                    continue;
                }

                // if the states are similar, add them to the to_replace map
                to_replace[*it2] = *it;
            }
        }
    }

    // replace the similar states in the graph
    for (auto &state: graph) {
        for (auto &transition: state.second) {
            if (to_replace.find(transition.second) != to_replace.end()) {
                transition.second = to_replace[transition.second];
            }
        }
    }

    // remove the replaced states
    for (auto &state: to_replace) {
        graph.erase(state.first);
    }
}

bool DFA::verify(const std::string &word) {
    std::string current_state = start_state;

    for (auto symbol: word) {
        current_state = graph[current_state][symbol];
    }

    return states[current_state];
}