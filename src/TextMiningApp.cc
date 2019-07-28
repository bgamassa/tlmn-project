//
// Created by beebee on 7/28/19.
//

#include <TextMiningApp.hh>

Trie* deserialize(std::string filename)
{
    Trie *t;
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia (ifs);
    ia >> t;

    return t;
}

int main(int argc, char *argv[])
{
    auto t = deserialize("dict.bin");
    return 0;
}
