#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <map>
#include <cstdio>
#include <set>
#include <vector>
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

    bool endOfWord;
    std::string word;
    int freq;
    std::unordered_map<char, Trie*> children;

public:
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

    void insert(std::string& word, int &freq);
    bool hasChildren();
    void save(std::string& filename);
    static Trie* load(std::string filename);
    static void free();
};