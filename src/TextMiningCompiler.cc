#include <TextMiningCompiler.hh>
#include <fstream>

struct Trie
{
    bool endOfWord;
    int freq;
    std::unordered_map<char, Trie*> children;
};

Trie* init_trie()
{
    Trie* node = new Trie;
    node->endOfWord  = false;
    node->freq = 0;
    return node;
}

void insert(Trie*& root, std::string word, int &freq)
{
    if (root == nullptr)
        root = init_trie();

    Trie* current = root;

    for(std::string::size_type i = 0; i < word.size(); ++i) {

        char c = word[i];

        if (current->children.find(c) == current->children.end())
            current->children[c] = init_trie();

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


void Node::add_children(char c, Node &n)
{
    this->children.insert({c, &n});
    this->characters.push_back(c);
}

int Node::find(char &c)
{
    for (auto i = 0; i < this->characters.size(); ++i)
    {
        std::cout << this->characters[i] << std::endl;
        if (this->characters[i] == c)
            return 1;
    }

    return 0;
}

void Node::add_word(std::string word, int &freq)
{
    if (word == "")
        return;

    char c = word[0];
    if (this->find(c) == 0)
    {
        // case when the character not in trie
        // we create a new node and add it to the current node
        // then if if is the final word, we indicate it by adding the frequency

        Node n(0);
        this->add_children(word[0], n);


        if (word.length() == 1)
            this->freq_ = freq;

        this->children[c]->add_word(word.substr(1, std::string::npos), freq);
    }

    else
    {
        if (word.length() == 1)
            this->freq_ = freq;

        std::cout << "hi there" << std::endl;
        this->children[c]->add_word(word.substr(1, std::string::npos), freq);
    }
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
        insert(root, words[0], i);
    }

    return root;
}

int read_file(std::string filename)
{
    std::ifstream fstream(filename);

    if (!fstream.is_open())
        return 0;

    auto n = process_file(filename);
    return 1;
}

int main(int argc, char *argv[])
{
  return read_file(argv[1]);
}