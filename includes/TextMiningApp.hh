//
// Created by beebee on 7/28/19.
//

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <TextMiningCompiler.hh>

int damerau_levenshtein(std::string& w1, std::string& w2);
void search(Trie*& t, std::string& word, int dist);
void load_and_search(char *dict, std::string word, int dist);
int handle_cmd(char *dict);