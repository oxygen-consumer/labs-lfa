//
// Created by Zaha on 3/16/2023.
//

#ifndef NFA_NFA_HPP
#define NFA_NFA_HPP

#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <stack>


class NFA {
private:
    std::map<int, std::multimap<char, int>> graph;
    std::map<int, bool> states;
    int start_state;

    std::ifstream fin{};
    std::ofstream fout{};

    void build();

    bool verify(const std::string &word, int state, std::stack<int> &path);

public:
    explicit NFA(const std::string &input_file, const std::string &output_file);

    void run();
};


#endif //NFA_NFA_HPP
