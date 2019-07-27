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
#include <vector>
#include <algorithm>


class Node
{
public:
    Node(int freq)
        : freq_(freq)
    {}
    int freq_;
    std::vector<char> characters;
    std::map<char, Node*> children;

    void add_children(char c, Node &n);
    void add_word(std::string word, int &freq);
    int find(char &c);
};
