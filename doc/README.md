AUTHORS

      Binta Gamassa

NAME

      TextMining - spell checker C++ implementation

SYNOPSIS

        mkdir build
        cd build
        cmake ..
        make
        ./TextMiningCompiler [dict_file] [destination_file]
        "echo appro 1 test" | ./TextMiningApp [saved_dict]	

DOC

      mkdir build
      cd build
      cmake ..
      make doc
      xdg-open ../doc/html/index.html or firefox ../doc/html/index.html

TEST SUITE
      
      mkdir build
      cd build
      cmake ..
      make check

DESCRIPTION

      This project is a C++ implementation of a spell checker using CMake as build system.
      In the first step, the program builds a compiled dictionnary using a text file provided
      by the user. Then, the program is able to output a list of words that is at a defined
      distance of a word both given in input by the user, using a Damerau-Levenshtein function.
