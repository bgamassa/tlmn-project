#include <Trie.hh>

void Trie::insert(std::string& word, int &freq)
{
    Trie* current = this;

    for(std::string::size_type i = 0; i < word.size(); ++i) {

        char c = word[i];

        if (current->children.find(c) == current->children.end())
            current->children[c] = new Trie("");

        current = current->children[c];
    }

    current->word = word;
    current->endOfWord = true;
    current->freq = freq;
}

bool Trie::hasChildren()
{
    for (auto it : this->children)
        if (it.second != nullptr)
            return true;

    return false;
}

Trie* Trie::load(std::string filename)
{
    Trie *t;
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia (ifs);
    ia >> t;

    return t;
}

void Trie::save(std::string& filename)
{
   std::ofstream ofs(filename);

   boost::archive::text_oarchive oa (ofs);
   oa << this;
}

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