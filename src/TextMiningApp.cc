#include <TextMiningApp.hh>

/*
 ** @file TextMiningApp.cc
 ** @brief File containing functions to search for words according to a given distance
 ** @authors Binta Gamassa
 ** @version 1.0
 ** @date 30/07/19
 */

typedef std::tuple<std::string &, int &, int &> elt;
auto res = std::vector<Element>();

Element init_element(std::string word, int freq, int distance)
{
    Element elt;

    elt.word = word;
    elt.freq = freq;
    elt.distance = distance;

    return elt;
}

bool elt_cmp(const Element &lhs, const Element &rhs)
{
    if (lhs.distance < rhs.distance)
        return true;
    if (lhs.distance > rhs.distance)
        return false;

    if (lhs.freq > rhs.freq)
        return true;
    if (lhs.freq < rhs.freq)
        return false;

    if (lhs.word < rhs.word)
        return true;
    return false;
}

void print_res()
{
    std::cout << '[';

    for (auto it = res.begin(); it != res.end(); ++it)
    {
        std::cout << '{' << "\"word\":\"" << it->word << "\",\"freq\":" << it->freq << ",\"distance\":"
                  << it->distance << '}';

        if (it->word != res.back().word)
            std::cout << ",";
    }

    std::cout << ']' << std::endl;
}

int damerau_levenshtein(std::string &w1, std::string &w2)
{
    int sub_or_exact = 0;
    auto size1 = w1.size();
    auto size2 = w2.size();

    int d[size1 + 1][size2 + 1] = {0};

    for (auto i = 0; i <= size1; ++i)
        d[i][0] = i;
    for (auto j = 0; j <= size2; ++j)
        d[0][j] = j;

    for (auto i = 1; i <= size1; ++i)
        for (auto j = 1; j <= size2; ++j)
        {
            if (w1[i - 1] == w2[j - 1])
                sub_or_exact = 0;
            else
                sub_or_exact = 1;

            d[i][j] = std::min(d[i - 1][j] + 1, 
                std::min(d[i][j - 1] + 1, d[i - 1][j - 1] + sub_or_exact));

            if (i > 1 && j > 1 && w1[i - 1] == w2[j - 2] && w1[i - 2] == w2[j - 1])
                d[i][j] = std::min(d[i][j], d[i - 2][j - 2] + sub_or_exact);
        }

    return d[w1.size()][w2.size()];
}

void search(Trie *&t, std::string &word, int dist)
{
    auto children = t->hasChildren();

    if (t->freq != 0)
    {
        auto d = damerau_levenshtein(word, t->word);

        if (d <= dist)
            res.push_back(init_element(t->word, t->freq, d));

        if (children)
            for (auto &elt : t->children)
                search(elt.second, word, dist);
    }
    else if (children)
    {
        for (auto &elt : t->children)
            search(elt.second, word, dist);
    }
}

void load_and_search(char *dict, std::string word, int dist)
{
    std::ifstream fstream(dict);
    Trie *root = nullptr;
    std::string line;

    std::ofstream fout("tmp.tmn", std::ios_base::trunc | std::ios_base::out);

    while (getline(fstream, line))
    {
        if (line == "=")
        {
            fout.close();
            root = Trie::load("tmp.tmn");
            search(root, word, dist);
            root->free();
            root = nullptr;

            fout = std::ofstream("tmp.tmn");
        }
        else
            fout << line << '\n';
    }
    std::remove("tmp.tmn");

    std::sort(res.begin(), res.end(), elt_cmp);
    print_res();
    res.clear();
}

int handle_cmd(char *dict)
{
    std::string buffer;

    while (std::getline(std::cin, buffer))
    {
        std::istringstream iss(buffer);
        std::vector<std::string> words{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}};

        load_and_search(dict, words[2], std::stoi(words[1]));
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cerr << "Usage: ./TextMiningApp /path/to/compiled/dict.bin\n";
        return 134;
    }

    return handle_cmd(argv[1]);
}