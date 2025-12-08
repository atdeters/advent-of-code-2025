#!/usr/bin/env bash

cd src
c++ -std=c++98 day08pt1.cpp -o day08pt1 -O3
./day08pt1 < ../input/example.txt
rm day08pt1
