//
// Created by beebee on 7/22/19.
//

#pragma once
#include <set>
#include <vector>
#include <Trie.hh>

std::set<std::string> build_trie(std::string filename);
int process_file(std::string filename, std::string dest);