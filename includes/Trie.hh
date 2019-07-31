#pragma once

/*
 ** @file Trie.hh
 ** @brief File defining the Trie class and its methods
 ** @authors Binta Gamassa
 ** @version 1.0
 ** @date 31/07/19
 */

#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <map>
#include <cstdio>
#include <algorithm>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/string.hpp>

/*! \class Trie
   * \brief Class for the data stucture used in the project
*/
class Trie
{
private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & end_of_word;
        ar & word;
        ar & freq;
        ar & children;
    }

public:
    bool end_of_word; /*!> variable that indicates whether we reach a leaf or the end of a word */
    std::string word; /*!> variable that contains a word when we reach the end of the word */
    int freq; /*!> variable that indicated the frequency of the word */
    std::unordered_map<char, Trie*> children; /*!> children of the trie */

    /*!
     *  \brief Empty constructor of class
     */
    Trie()
    {
        end_of_word = false;
        freq = 0;
    }

    /*!
     *  \brief Second constructor of class
     *  \param std::string word_: the word to insert in trie
     */
    Trie(std::string word_)
    {
        end_of_word = false;
        freq = 0;
        word = word_;
    }

    /*!
     *  \brief This method allow us to know whether a trie has children
     *
     *  \return true if trie has children,
     *  false else
     */
    bool hasChildren();

    /*!
     *  \brief This method allow us to serialize a trie
     *  \param std::string& filename : destination file to save the trie
     *  \return void
     */
    void save(std::string& filename);

    /*!
     *  \brief This method deletes a trie and frees its allocated memory
     *
     *  \return void
     */
    void free();

    /*!
     *  \brief This method allow us to inser a word in a trie
     *  \param Trie*& root: the trie in which to insert the word
     *  \param std::string& word: the word to insert in trie
     *  \param int &freq: the frequency of apparition of the word
     *  \return void
     */
    static void insert(Trie*& root, std::string& word, int &freq);

    /*!
     *  \brief This method allow us to load a trie from a file
     *  \param std::string filename: the name of the file from which to load the trie
     *  \return Trie*
     */
    static Trie* load(std::string filename);
};