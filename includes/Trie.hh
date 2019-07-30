#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <map>
#include <cstdio>
#include <algorithm>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/string.hpp>

class Trie
{
private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & endOfWord;
        ar & word;
        ar & freq;
        ar & children;
    }

public:
    bool endOfWord;
    std::string word;
    int freq;
    std::unordered_map<char, Trie*> children;

    Trie()
    {
        endOfWord = false;
        freq = 0;
    }

    Trie(std::string word_)
    {
        endOfWord = false;
        freq = 0;
        word = word_;

    }

    bool hasChildren();
    void save(std::string& filename);
    void free();
    static void insert(Trie*& root, std::string& word, int &freq);
    static Trie* load(std::string filename);
};