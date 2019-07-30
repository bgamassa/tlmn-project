#include <Trie.hh>

/*
 ** @file Trie.cc
 ** @brief File containing method from Trie
 ** @authors Binta Gamassa
 ** @version 1.0
 ** @date 30/07/19
 */

void Trie::insert(Trie*& root, std::string& word, int &freq)
{
    if (root == nullptr)
        root = new Trie("");

    Trie* current = root;

    for (std::string::size_type i = 0; i < word.size(); ++i) {

        char c = word[i];

        if (current->children.find(c) == current->children.end())
            current->children[c] = new Trie("");

        current = current->children[c];
    }

    current->word = word;
    current->endOfWord = true;
    current->freq = freq;
}

/** My function doing something...
    @param filename first parameter
    @return value return value
*/

bool Trie::hasChildren()
{
    for (auto it : this->children)
        if (it.second != nullptr)
            return true;

    return false;
}

/** My function doing something...
    @param filename first parameter
    @return value return value
*/

Trie* Trie::load(std::string filename)
{
    Trie *t;
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia (ifs);
    ia >> t;

    return t;
}

/** My function doing something...
    @param filename first parameter
    @return value return value
*/

void Trie::save(std::string& filename)
{
   std::ofstream ofs(filename);

   boost::archive::text_oarchive oa (ofs);
   oa << this;
}

/** My function doing something...
    @param filename first parameter
    @return value return value
*/

void Trie::free()
{
    if (this == nullptr)
        return;

    if (this->hasChildren())
    {
        for (auto &c : this->children)
            c.second->free();
    }

    delete this;
}