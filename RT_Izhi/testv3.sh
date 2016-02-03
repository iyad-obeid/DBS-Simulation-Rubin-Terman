#!/bin/bash
# test.sh
echo "Parkinsons runs starting now"
rm ~/Dropbox/Program_IO/PD_RK/*.bin
make clean
make


echo "All with error = 1e-14"
./temp 1 2500 1e-14 1e-14 1e-14 1e-14
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_N/All_1e14
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_N/All_1e14
rm ~/Dropbox/Program_IO/PD_RK/*.bin


echo "done" 

