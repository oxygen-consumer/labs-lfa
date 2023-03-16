//
// Created by Zaha on 3/11/2023.
//

#ifndef DFA_DFA_HPP
#define DFA_DFA_HPP

#include <fstream>
#include <map>
#include <string>
#include <stack>
#include <iostream>


class DFA {
private:
    std::map<int, std::map<char, int>> graph;
    std::map<int, bool> states;
    int start_state;

    std::ifstream fin{};
    std::ofstream fout{};

    void build();

    bool verify(const std::string& word, int state, std::stack<int>& path);

public:
    explicit DFA(const std::string& input_filename, const std::string& output_filename);

    void run();
};


#endif //DFA_DFA_HPP
