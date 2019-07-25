//
// Created by beebee on 7/22/19.
//

#pragma once
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <map>


class Node
{
public:
    Node(unsigned int freq)
        : freq_(freq)
    {}
    void add_children(char c, Node &n);
    void add_word(std::string word, int &freq);

private:
    int freq_;
    std::map<char, Node*> children;
};
