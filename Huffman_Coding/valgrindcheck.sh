#!/bin/bash
FILENAME=valgrind.out
date -u > $FILENAME
g++ -g -std=c++11 -Wall -Wextra -Wno-sign-compare -Werror *.cpp 2>&1 | tee -a $FILENAME
valgrind --leak-check=full ./a.out  2>&1 | tee -a $FILENAME
