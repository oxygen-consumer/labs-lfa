//
// Created by zaha on 5/4/23.
//

#ifndef LAB2_NFA_HPP
#define LAB2_NFA_HPP


#include "../Automat/Automat.hpp"
#include <fstream>
#include <queue>
#include <utility>
#include <algorithm>


class NFA : public Automat {
private:
    // NFA graph representation: state -> (letter -> state)
    std::map<std::string, std::multimap<char, std::string>> graph;

    std::ifstream fin{};

    void read();

    bool dfs(std::string word, const std::string &state);

public:
    bool verify(const std::string &word) override;

    explicit NFA(const std::string &input_file);

    const std::map<std::string, std::multimap<char, std::string>> get_graph() const;

};

#endif //LAB2_NFA_HPP
