//
// Created by zaha on 5/4/23.
//

#ifndef LAB2_AUTOMAT_HPP
#define LAB2_AUTOMAT_HPP


#include <string>
#include <map>
#include <set>
#include <bitset>


class Automat {
protected:
    // last bit is reserved for dead state
//    static const size_t MAX_STATES = 32;

    // graph representation: state -> (letter -> state)
    //std::map<std::string, std::multimap<char, std::string>> graph;

    // initial state
    std::string start_state;

    // set of symbols
    std::set<char> symbols;

    // what states we have, if marked as true, then it is a final state
    std::map<std::string, bool> states;

public:
    // pure virtual function, must be implemented in derived classes
    // returns true if the word is accepted by the automata
    virtual bool verify(const std::string &word) = 0;

    // getters
//    [[nodiscard]] const std::map<std::string, std::multimap<char, std::string>> &get_graph() const;

    [[nodiscard]] const std::set<char> &get_symbols() const;

    [[nodiscard]] const std::map<std::string, bool> &get_states() const;

    [[nodiscard]] std::string get_start_state() const;
};


#endif //LAB2_AUTOMAT_HPP
