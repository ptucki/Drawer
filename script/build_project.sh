#! /bin/bash

cd ../build
pwd
cmake -S ../ -O ../build
make
read -p "Press any key to close..."