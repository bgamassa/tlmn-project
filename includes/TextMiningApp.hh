#pragma once

/*
 ** @file TextMiningApp.hh
 ** @brief File defining functions and structs to search for words according to a given distance
 ** @authors Binta Gamassa
 ** @version 1.0
 ** @date 30/07/19
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <TextMiningCompiler.hh>

/*! \struct Element
   * \brief Struct used to store the result of a search in Trie
*/
struct Element
{
    std::string word;
    int freq; /*!> variable that indicated the frequency of the word */
    int distance; /*!> variable that indicates the distance between a given word and the word in struct */
};

/*!
*  \brief This method allow us to know whether a trie has children
*
*  \return true if trie has children,
*  false else
*/
Element init_element(std::string word, int freq, int distance);

/*!
*  \brief This method defines conditions to compare whether an element is smaller then an other
*
*  \return true if rhs matches conditions,
*  false else
*/
bool elt_cmp(const Element &lhs, const Element &rhs);

/*!
*  \brief This method prints results in JSON format
*/
void print_res();

/*!
*  \brief This method computes a damerau-levenshtein distance between two strings
*  \param std::string& w1: first string
*  \param std::string& w2: second string
*  \return int: the damerau-levenshtein distance computes
*/
int damerau_levenshtein(std::string& w1, std::string& w2);

/*!
*  \brief This method allow us to search for a word in a trie
*  \param Trie *&t : the trie in which to look for
*  \param std::string& word : the word to look for
*  \param int dist: the max distance allowed
*  false else
*/
void search(Trie*& t, std::string& word, int dist);

/*!
*  \brief This method loads a trie from file and search a word in it
*  \param char *dict: the name of the file from which to load the trie
*  \param std::string& word : the word to look for
*  \param int dist: the max distance allowed
*/
void load_and_search(char *dict, std::string word, int dist);

/*!
*  \brief This method allow us to know whether a trie has children
*  \param char *dict: the name of the file from which to load the trie
*  \return int
*/
int handle_cmd(char *dict);