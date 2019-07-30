#!/bin/sh

cat commands.txt | ../build/TextMiningApp ../build/dict.bin > "my_output.txt"
cat commands.txt | ref/TextMiningApp ref/dict.bin > "ref.txt"

diff --color=auto -s ref.txt my_output.txt
