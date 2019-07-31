#pragma once

/*
 ** @file TextMiningCompiler.hh
 ** @brief File containing functions to build a trie from a list of words
 ** @authors Binta Gamassa
 ** @version 1.0
 ** @date 30/07/19
 */

#include <set>
#include <vector>
#include <Trie.hh>

/*!
*  \brief This method builds a trie from a text file
*  \param std::string filename: the text file from which to build the trie
*  \return std::set<std::string> : list of tries built
*/
std::set<std::string> build_trie(std::string filename);

/*!
*  \brief This method process a text file to build a trie and save it to a destination file
*  \param std::string filename: the text file from which to build the trie
*  \param std::string dest: the destinaton file in which to save the trie
*  \return int
*/
int process_file(std::string filename, std::string dest);