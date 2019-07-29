#include <TextMiningApp.hh>

Trie* deserialize(std::string filename)
{
    Trie *t;
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia (ifs);
    ia >> t;

    return t;
}

void print(std::string& word, int& distance, int& freq)
{
    std::cout << '{' << "\"word\":" << word << ",\"freq\":" << freq << ",\"distance\":" << distance << '}';
}

void searchRecursive(Trie*& t, char c, std::string& word, std::vector<int>& row, int& dist)
{
    auto columns = word.size() + 1;
    std::vector<int> currentRow = {row[0] + 1};

    for (auto i = 1; i < columns; ++i)
    {
        auto insert = currentRow[i - 1] + 1;
        auto del = row[i] + 1;

        auto replace = 0;
        if (word[i - 1] != c)
            replace = row[i - 1] + 1;
        else
            replace = row[i - 1];

        currentRow.push_back(std::min({ insert, del, replace }));

        if (currentRow.back() <= dist && t->endOfWord) // fix
            print(t->word, currentRow.back(), t->freq);

        if (*std::min_element(currentRow.begin(), currentRow.end()) <= dist)
        {
            for (auto& elt: t->children)
                searchRecursive(elt.second, elt.first, word, currentRow, dist);
        }

    }
}

void search(Trie*& t, std::string& word, int dist)
{
    std::cout << word << std::endl;
    std::cout << dist << std::endl;

    auto vect = std::vector<int>();

    for (int i = 0; i < word.size() + 1; ++i)
        vect.push_back(i);

    std::cout << '[';

    for (auto& elt: t->children)
        searchRecursive(elt.second, elt.first, word, vect, dist);

    std::cout << ']';
}

int handle_pipe(char *dict)
{
    auto trie = deserialize(dict);

    char *buffer = NULL;
    size_t l = 0;
    ssize_t t = getline(&buffer, &l, stdin);

    if (buffer[t - 1] == '\n')
    {
        buffer[t - 1] = '\0';
        --t;
    }

    std::istringstream iss(buffer);
    std::vector<std::string> words{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
    };

    search(trie, words[2], std::stoi(words[1]));

    free(buffer);

    return 0;
}

int main(int argc, char *argv[])
{
    return handle_pipe(argv[1]);
}
