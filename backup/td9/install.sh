#!/bin/bash

cd memLoader_dir
make install
cd ../assembly
progmem -v -o compiled.bin instructions.txt
serieViaUSB -e -f compiled.bin
sleep 1
cd ../lib_dir
make
cd ../exec_dir
make install
cd ..
