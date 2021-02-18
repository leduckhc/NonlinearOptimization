#!/bin/bash

g++ -Wall -pedantic -Wextra -O3 -std=c++11 -g \
    ukol1.cpp matrix.cpp prettyprint.cpp permutation.cpp \
    -o bin/ukol1
