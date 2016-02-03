#!/bin/bash
# test.sh
echo "Normal runs starting now"
make clean
make "DFLAG = -DALLDATA"

#start TC runs

rm ~/Dropbox/Program_IO/PD_RK/*.bin
echo "All neurons at 1e-10"
time ./temp 1 2500 1e-10 1e-10 1e-10 1e-10
#mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_test
#rm ~/Desktop/Program_Files/Program_IO/RT_RK_test/*.bin
#cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_test
#rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "done" 

