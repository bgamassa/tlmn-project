#include <TextMiningApp.hh>

typedef std::tuple<std::string &, int &, int &> elt;
auto res = std::vector<element>();

bool elt_cmp(const element &lhs, const element &rhs)
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

int damerau_levenshtein(std::string& word1, std::string& word2)
{
    int size1 = word1.size(), size2 = word2.size();
    int suppr_dist, insert_dist, subs_dist, val;
    int *dist = new int[(size1 + 1) * (size2 + 1)];

    for (int i = 0; i < size1 + 1; ++i)
        dist[(size2 + 1) * i] = i;
    for (int j = 0; j < size2 + 1; ++j)
        dist[j] = j;
    for (int i = 1; i < size1 + 1; ++i)
    {
        for (int j = 1; j < size2 + 1; ++j)
        {
            suppr_dist = dist[(size2 + 1) * (i - 1) + j] + 1;
            insert_dist = dist[(size2 + 1) * i + j - 1] + 1;
            subs_dist = dist[(size2 + 1) * (i - 1) + j - 1];
            if (word1[i - 1] != word2[j - 1])
                subs_dist += 1;
            val = std::min(suppr_dist, std::min(insert_dist, subs_dist));
            if (((i >= 2) && (j >= 2)) && ((word1[i - 1] == word2[j - 2]) && (word1[i - 2] == word2[j - 1])))
                val = std::min(dist[(size2 + 1) * (i - 2) + j - 2] + 1, val);
            dist[(size2 + 1) * i + j] = val;
        }
    }

    int res = dist[(size1 + 1) * (size2 + 1) - 1];
    delete dist;
    return (res);
}

/* int damerau_levenshtein(std::string &w1, std::string &w2)
{
    int sub_or_exact = 0;

    int d[w1.size() + 1][w2.size() + 1] = {0};

    for (auto i = 0; i <= w1.size(); ++i)
        d[i][0] = i;
    for (auto j = 0; j <= w2.size(); ++j)
        d[0][j] = j;

    auto diff = 0;

    if (w1[0] != w2[0])
        diff = 1;

    for (auto i = 1; i <= w1.size(); ++i)
        for (auto j = 1; j <= w2.size(); ++j)
        {
            if (w1[i] == w2[j])
                sub_or_exact = 0;
            else
                sub_or_exact = 1;

            d[i][j] = std::min(d[i - 1][j] + 1, std::min(d[i][j - 1] + 1, d[i - 1][j - 1] + sub_or_exact));

            if (i > 1 && j > 1 && w1[i] == w2[j - 1] && w1[i - 1] == w2[j])
                d[i][j] = std::min(d[i][j], d[i - 2][j - 2] + sub_or_exact);
        }

    return d[w1.size()][w2.size()] + diff;
}*/

element init_element(std::string word, int freq, int distance)
{
    element elt;

    elt.word = word;
    elt.freq = freq;
    elt.distance = distance;

    return elt;
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

void search(Trie *&t, std::string &word, int dist)
{
    auto children = t->hasChildren();

    if (t->freq != 0)
    {
        auto d = damerau_levenshtein(word, t->word);

        if (d <= dist)
        {
            //std::cout << t->word << std::endl;
            res.push_back(init_element(t->word, t->freq, d));
        }

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
    /*std::string w1 = "bonjour";
    std::string w2 = "bojnour";
    std::string w3 = "alseimer";
    std::string w4 = "alzheimer";
    std::string w5 = "bonjjour";
    std::string w6 = "test";
    std::string w7 = "test";

    std::cout << damerau_levenshtein(w2, w1) << std::endl;
    std::cout << damerau_levenshtein(w3, w4) << std::endl;
    std::cout << damerau_levenshtein(w5, w1) << std::endl;
    std::cout << damerau_levenshtein(w6, w7) << std::endl;

    return 0;*/

    return handle_cmd(argv[1]);
}
