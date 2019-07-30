#include <TextMiningCompiler.hh>

std::set<std::string> build_trie(std::string filename)
{
    auto dicts = std::set<std::string>();

    std::ifstream fstream(filename);
    Trie* root = new Trie("");
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
            std::cout << c << ".tmn" << std::endl;
            if (root != nullptr)
            {
                auto fname = std::string(1, cur).append(".tmn");
                root->save(fname);
                root->free();
                root = nullptr;
            }

            cur = c;
            letters.insert(c);
            auto fname = std::string(1, cur).append(".tmn");
            dicts.insert(fname);
            Trie::insert(root, words[0], i);
        }
        else if (c != cur)
        {
            if (root != nullptr)
            {
                auto fname = std::string(1, cur).append(".tmn");
                root->save(fname);
                root->free();
                root = nullptr;
            }

            auto fname = std::string(1, c).append(".tmn");
            root = Trie::load(fname);
            cur = c;
            Trie::insert(root, words[0], i);
        }
        else
            Trie::insert(root, words[0], i);
    }

    auto fname = std::string(1, cur).append(".tmn");
    root->save(fname);
    root->free();
    root = nullptr;

    return dicts;
}

int process_file(std::string filename, std::string dest)
{
    std::ifstream fstream(filename);

    if (!fstream.is_open())
        return 0;

    auto n = build_trie(filename);
    std::ofstream fout(dest);

    for (auto i = n.begin(); i != n.end(); ++i)
    {
        std::ifstream fin(*i);
        std::string line;
        while( std::getline( fin, line ) ) fout << line << '\n';
        fout << "=" << '\n';
        std::cout << "deleting " << *i << std::endl;
        std::remove(i->c_str());
    }

    return 1;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "Usage: ./TextMiningCompiler /path/to/word/freq.txt /path/to/output/dict.bin\n";
        return 134;
    }

    return process_file(argv[1], argv[2]);
}