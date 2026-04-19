#!/bin/bash
FILENAME=lint.out
uname -r > $FILENAME
date >> $FILENAME
#NOTE:  The following command should all be on one line!
clang-tidy *.cpp -checks="-*,bugprone-*,performance-*,clang-analyzer-*,readability-*,misc-*" -- -std=c++11 | tee -a $FILENAME