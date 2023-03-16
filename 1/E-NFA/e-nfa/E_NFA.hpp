//
// Created by Zaha on 3/16/2023.
//

#ifndef E_NFA_E_NFA_HPP
#define E_NFA_E_NFA_HPP

#include <fstream>
#include <map>
#include <string>
#include <set>
#include <iostream>
#include <stack>


class E_NFA {
private:
    std::map<int, std::multimap<char, int>> graph;
    std::map<int, bool> final_states;
    std::set<int> start_states;

    std::ifstream fin{};
    std::ofstream fout{};

    void build();

    bool verify(const std::string &word, int state, std::stack<int> &path);

    void epsilon_closure(int state, std::set<int> &closure);

    void clean_graph();

    void transform_to_nfa();

public:
    explicit E_NFA(const std::string &input_file, const std::string &output_file);

    void run();
};


#endif //E_NFA_E_NFA_HPP
