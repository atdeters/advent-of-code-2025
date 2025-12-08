#!/usr/bin/env bash

cd src
c++ -std=c++98 Vec.cpp Pair.cpp Help.cpp day08pt2.cpp -o day08pt2 -O3
./day08pt2 < ../input/input.txt
rm day08pt2
