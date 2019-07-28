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
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>

class Trie
{
private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & endOfWord;
        ar & freq;
        ar & children;
    }
public:
    bool endOfWord;
    int freq;
    std::unordered_map<char, Trie*> children;

    Trie()
    {
        endOfWord = false;
        freq = 0;
    }
};
