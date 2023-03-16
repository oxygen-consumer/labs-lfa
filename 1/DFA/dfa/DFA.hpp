//
// Created by Zaha on 3/11/2023.
//

#ifndef DFA_DFA_HPP
#define DFA_DFA_HPP

#include <fstream>
#include <map>
#include <string>


class DFA {
private:
    std::map<int, std::map<char, int>> graph;
    std::map<int, bool> states;
    int start_state;

    std::string input_file;
    std::string output_file;

    std::ifstream fin{};
    std::ofstream fout{};

    void build();

    bool verify(const std::string& word, int state);

public:
    explicit DFA(const std::string& input_filename, const std::string& output_filename);

    void run();
};


#endif //DFA_DFA_HPP
