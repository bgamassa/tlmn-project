#include <TextMiningCompiler.hh>

Trie* init_trie()
{
    Trie* node = new Trie;
    node->endOfWord  = false;
    node->freq = 0;
    return node;
}

void insert(Trie*& root, std::string& word, int &freq)
{
    if (root == nullptr)
        root = new Trie();

    Trie* current = root;

    for(std::string::size_type i = 0; i < word.size(); ++i) {

        char c = word[i];

        if (current->children.find(c) == current->children.end())
            current->children[c] = new Trie();

        current = current->children[c];
    }

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

void serialize(Trie*& root, std::string& filename)
{
   std::ofstream ofs(filename);

    {
        boost::archive::text_oarchive oa (ofs);
        oa << root;
    }
}

Trie* deserialize(std::string& filename)
{
    Trie *t;
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia (ifs);
    ia >> t;

    return t;
}


Trie* process_file(std::string filename)
{
    std::ifstream fstream(filename);
    Trie* root = nullptr;
    std::string line;

    while (getline(fstream, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> words{
                std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>{}
        };

        auto i = std::stoi(words[1]);
        //std::cout << words[0] << std::endl;
        insert(root, words[0], i);
    }


    return root;
}

int read_file(std::string filename, std::string dest)
{
    std::ifstream fstream(filename);

    if (!fstream.is_open())
        return 0;

    auto n = process_file(filename);
    serialize(n, dest);
    //auto t = deserialize("dict.bin");
    return 1;
}

int main(int argc, char *argv[])
{
  return read_file(argv[1], argv[2]);
}