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

class Node
{
public:
    Node(unsigned int freq)
        : freq_(freq)
    {}
    void add_children(char c, Node n);

private:
    int freq_;
    std::unordered_map<char, Node*> children;
};
