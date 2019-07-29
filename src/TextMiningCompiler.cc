#include <TextMiningCompiler.hh>

#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Trie* init_trie()
{
    Trie* node = new Trie;
    node->endOfWord  = false;
    node->freq = 0;
    return node;
}*/

void insert(Trie*& root, std::string& word, int &freq)
{
    if (root == nullptr)
        root = new Trie("");

    Trie* current = root;

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

bool hasChildren(Trie const* current)
{
    for (auto it : current->children)
        if (it.second != nullptr)
            return true;

    return false;
}


Trie* load(std::string filename)
{
    Trie *t;
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia (ifs);
    ia >> t;

    return t;
}

void serialize(Trie*& root, std::string& filename)
{
   std::ofstream ofs(filename);

   boost::archive::text_oarchive oa (ofs);
   oa << root;
}

void free(Trie*& trie)
{
    if (trie == nullptr)
        return;

    if (hasChildren(trie))
    {
        for (auto &c : trie->children)
            free(c.second);
    }

    delete trie;
    trie = nullptr;
}

std::set<std::string> process_file(std::string filename)
{
    auto dicts = std::set<std::string>();

    std::ifstream fstream(filename);
    Trie* root = nullptr;
    std::string line;

    auto letters = std::set<char>();

    char cur = -1;
    while (getline(fstream, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> words{
                std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>{}
        };

        char c = words[0][0];
        auto i = std::stoi(words[1]);

        if (letters.find(c) == letters.end())
        {
            std::cout << c << ".bin" << std::endl;
            if (root != nullptr)
            {
                auto fname = std::string(1, cur).append(".bin");
                // compile
                serialize(root, fname);
                // free
                free(root);
                // recreate
                root = nullptr;
            }

            cur = c;
            letters.insert(c);
            auto fname = std::string(1, cur).append(".bin");
            dicts.insert(fname);
            // insert
            insert(root, words[0], i);
        }
        else if (c != cur)
        {
            if (root != nullptr)
            {
                auto fname = std::string(1, cur).append(".bin");
                // compile
                serialize(root, fname);
                // free
                free(root);
                // recreate
                root = nullptr;
            }

            // load corresponding trie and insert
            auto fname = std::string(1, c).append(".bin");
            root = load(fname);
            cur = c;
            insert(root, words[0], i);
        }
        else
        {
            // insert
            insert(root, words[0], i);
        }
    }

    auto fname = std::string(1, cur).append(".bin");
    serialize(root, fname);
    free(root);

    return dicts;
}

int read_file(std::string filename, std::string dest)
{
    std::ifstream fstream(filename);

    if (!fstream.is_open())
        return 0;

    auto n = process_file(filename);
    std::ofstream fout(dest, std::ios_base::app);

    for (auto i = n.begin(); i != n.end(); ++i)
    {
        std::ifstream fin(*i);
        std::string line;
        while( std::getline( fin, line ) ) fout << line << '\n';
        fout << "===" << '\n';
        std::cout << "deleting " << *i << std::endl;
        std::remove(i->c_str());
    }
    return 1;
}

int main(int argc, char *argv[])
{
    return read_file(argv[1], argv[2]);
}