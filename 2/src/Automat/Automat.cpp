//
// Created by zaha on 5/4/23.
//

#include "Automat.hpp"

/*
const std::map<std::string, std::multimap<char, std::string>> &Automat::get_graph() const {
    return graph;
}
 */

const std::set<char> &Automat::get_symbols() const {
    return symbols;
}

const std::map<std::string, bool> &Automat::get_states() const {
    return states;
}

std::string Automat::get_start_state() const {
    return start_state;
}
