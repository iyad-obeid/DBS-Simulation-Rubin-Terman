#!/bin/bash
# test.sh
echo "Parkinsons runs starting now"
make clean
make "DFLAG=-DPARKINSONS"
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPi with error = 1e-4"
./temp 1 2500 1e-4 1e-12 1e-12 1e-12
mkdir ~/Dropbox/Program_IO/GPi_1e4
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/GPi_1e4
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPi with error = 1e-6"
./temp 1 2500 1e-6 1e-12 1e-12 1e-12
mkdir ~/Dropbox/Program_IO/GPi_1e6
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/GPi_1e6
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPi with error = 1e-8"
./temp 1 2500 1e-8 1e-12 1e-12 1e-12
mkdir ~/Dropbox/Program_IO/GPi_1e8
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/GPi_1e8
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPi with error = 1e-10"
./temp 1 2500 1e-10 1e-12 1e-12 1e-12
mkdir ~/Dropbox/Program_IO/GPi_1e10
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/GPi_1e10
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "All with error = 1e-12"
./temp 1 2500 1e-12 1e-12 1e-12 1e-12
mkdir ~/Dropbox/Program_IO/All_1e12
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/All_1e12
rm ~/Dropbox/Program_IO/PD_RK/*.bin

#start GPe Runs
echo "GPe with error = 1e-4"
./temp 1 2500 1e-12 1e-4 1e-12 1e-12
mkdir ~/Dropbox/Program_IO/GPe_1e4
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/GPe_1e4
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPe with error = 1e-6"
./temp 1 2500 1e-12 1e-6 1e-12 1e-12
mkdir ~/Dropbox/Program_IO/GPe_1e6
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/GPe_1e6
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPe with error = 1e-8"
./temp 1 2500 1e-12 1e-8 1e-12 1e-12
mkdir ~/Dropbox/Program_IO/GPe_1e8
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/GPe_1e8
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPe with error = 1e-10"
./temp 1 2500 1e-12 1e-10 1e-12 1e-12
mkdir ~/Dropbox/Program_IO/GPe_1e10
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/GPe_1e10
rm ~/Dropbox/Program_IO/PD_RK/*.bin

#stert STN runs
echo "STN with error = 1e-4"
./temp 1 2500 1e-12 1e-12 1e-4 1e-12
mkdir ~/Dropbox/Program_IO/STN_1e4
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/STN_1e4
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "STN with error = 1e-6"
./temp 1 2500 1e-12 1e-12 1e-6 1e-12
mkdir ~/Dropbox/Program_IO/STN_1e6
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/STN_1e6
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "STN with error = 1e-8"
./temp 1 2500 1e-12 1e-12 1e-8 1e-12
mkdir ~/Dropbox/Program_IO/STN_1e8
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/STN_1e8
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "STN with error = 1e-10"
./temp 1 2500 1e-12 1e-12 1e-10 1e-12
mkdir ~/Dropbox/Program_IO/STN_1e10
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/STN_1e10
rm ~/Dropbox/Program_IO/PD_RK/*.bin

#start TC runs

echo "TC with error = 1e-4"
./temp 1 2500 1e-12 1e-12 1e-12 1e-4
mkdir ~/Dropbox/Program_IO/TC_1e4
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/TC_1e4
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "TC with error = 1e-6"
./temp 1 2500 1e-12 1e-12 1e-12 1e-6
mkdir ~/Dropbox/Program_IO/TC_1e6
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/TC_1e6
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "TC with error = 1e-8"
./temp 1 2500 1e-12 1e-12 1e-12 1e-8
mkdir ~/Dropbox/Program_IO/TC_1e8
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/TC_1e8
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "TC with error = 1e-10"
./temp 1 2500 1e-12 1e-12 1e-12 1e-10
mkdir ~/Dropbox/Program_IO/TC_1e10
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Dropbox/Program_IO/TC_1e10
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "done" 

