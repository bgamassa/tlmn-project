#include <TextMiningCompiler.hh>
#include <fstream>

void Node::add_children(char c, Node n)
{
    this->children.insert({c, &n});
}

void add_word(std::string word, int freq)
{

}

Node process_file(std::string filename)
{
    std::ifstream fstream(filename);
    auto n = Node(0);
    std::string line;

    while (getline(fstream, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> words{
                std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>{}
        };

        for (auto w : words)
        {
            std::cout << e << "$" << std::endl;
        }
    }

    return n;
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
