#! /bin/bash

cd build && cmake .. && make -j4 && echo "OK
" && ./npuzzle

