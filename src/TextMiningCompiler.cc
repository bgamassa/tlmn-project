#include <TextMiningCompiler.hh>
#include <fstream>

void Node::add_children(char c, Node &n)
{
    this->children.insert({c, &n});
}

void Node::add_word(std::string word, int &freq)
{
    auto cur = this;

    for (std::string::size_type i = 0; i < word.size(); ++i)
    {
        /*std::cout << word[i] << std::endl;
        std::cout << word << "$" << std::endl;
        std::cout << "freq " << cur->freq_ << std::endl;*/

        char c = word[i];
        if (cur->children.empty() || (cur->children.find(c) == cur->children.end()))
        {
            // case when the character not in trie
            // we create a new node and add it to the current node
            // then if if is the final word, we indicate it by adding the frequency

            auto n = Node(0);
            cur->add_children(word[i], n);

            //std::cout << cur->children.size() << std::endl;

            if (i + 1 == word.size())
                cur->freq_ = freq;

            cur = &n;

            /*if (i + 1 == word.size())
                cur->freq_ = freq;

            cur = cur->children[word[i]];*/
        }

        else
        {
            if (i + 1 == word.size())
                cur->freq_ = freq;

            cur = cur->children[word[i]];

            /*auto n = Node(0);
            cur->add_children(word[i], n);

            std::cout << cur->children.size() << std::endl;

            if (i + 1 == word.size())
                cur->freq_ = freq;

            cur = &n;*/
        }
    }
}

Node process_file(std::string filename)
{
    std::ifstream fstream(filename);
    auto root = Node(0);
    std::string line;

    while (getline(fstream, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> words{
                std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>{}
        };

        auto i = std::stoi(words[1]);
        std::cout << words[0] << std::endl;
        root.add_word(words[0], i);
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
