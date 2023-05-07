//
// Created by zaha on 5/4/23.
//

#ifndef LAB2_DFA_HPP
#define LAB2_DFA_HPP


#include <bitset>
#include <set>
#include <queue>
#include "../Automat/Automat.hpp"
#include "../NFA/NFA.hpp"


class DFA : public Automat {
private:
    // DFA graph representation: state -> (letter -> state)
    // the states are represented as bitsets
    std::map<std::string, std::map<char, std::string>> graph;

    // last bit is reserved for dead state, don't use it
    static constexpr size_t MAX_STATES = 6;

    void transform(const NFA &nfa);

    void minimize();

public:
    bool verify(const std::string &word) override;

    explicit DFA(const NFA &nfa);
};


#endif //LAB2_DFA_HPP
