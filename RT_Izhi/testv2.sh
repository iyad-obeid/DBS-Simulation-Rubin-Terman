#!/bin/bash
# test.sh
echo "Parkinsons runs starting now"
make clean
make "DFLAG=-DPARKINSONS -DDBS"

echo "GPi with error = 1e-4"
./temp 1 2500 1e-4 1e-12 1e-12 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPi_1e4
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPi_1e4
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPi with error = 1e-6"
./temp 1 2500 1e-6 1e-12 1e-12 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPi_1e6
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPi_1e6
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPi with error = 1e-8"
./temp 1 2500 1e-8 1e-12 1e-12 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPi_1e8
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPi_1e8
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPi with error = 1e-10"
./temp 1 2500 1e-10 1e-12 1e-12 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D//GPi_1e10
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPi_1e10
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "All with error = 1e-12"
./temp 1 2500 1e-12 1e-12 1e-12 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/All_1e12
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/All_1e12
rm ~/Dropbox/Program_IO/PD_RK/*.bin

#start GPe Runs
echo "GPe with error = 1e-4"
./temp 1 2500 1e-12 1e-4 1e-12 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPe_1e4
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPe_1e4
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPe with error = 1e-6"
./temp 1 2500 1e-12 1e-6 1e-12 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPe_1e6
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPe_1e6
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPe with error = 1e-8"
./temp 1 2500 1e-12 1e-8 1e-12 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPe_1e8
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPe_1e8
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "GPe with error = 1e-10"
./temp 1 2500 1e-12 1e-10 1e-12 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPe_1e10
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/GPe_1e10
rm ~/Dropbox/Program_IO/PD_RK/*.bin

#stert STN runs
echo "STN with error = 1e-4"
./temp 1 2500 1e-12 1e-12 1e-4 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/STN_1e4
cp ~/Dropbox/Program_IO/PD_RK/*.bin ~/Desktop/Program_Files/Program_IO/RT_RK_D/STN_1e4
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "STN with error = 1e-6"
./temp 1 2500 1e-12 1e-12 1e-6 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/STN_1e6
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/STN_1e6
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "STN with error = 1e-8"
./temp 1 2500 1e-12 1e-12 1e-8 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/STN_1e8
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/STN_1e8
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "STN with error = 1e-10"
./temp 1 2500 1e-12 1e-12 1e-10 1e-12
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/STN_1e10
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/STN_1e10
rm ~/Dropbox/Program_IO/PD_RK/*.bin

#start TC runs

echo "TC with error = 1e-4"
./temp 1 2500 1e-12 1e-12 1e-12 1e-4
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/TC_1e4
cp ~/Dropbox/Program_IO/PD_RK/*.bin   ~/Desktop/Program_Files/Program_IO/RT_RK_D/TC_1e4
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "TC with error = 1e-6"
./temp 1 2500 1e-12 1e-12 1e-12 1e-6
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/TC_1e6
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/TC_1e6
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "TC with error = 1e-8"
./temp 1 2500 1e-12 1e-12 1e-12 1e-8
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/TC_1e8
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/TC_1e8
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "TC with error = 1e-10"
./temp 1 2500 1e-12 1e-12 1e-12 1e-10
mkdir ~/Desktop/Program_Files/Program_IO/RT_RK_D/TC_1e10
cp ~/Dropbox/Program_IO/PD_RK/*.bin  ~/Desktop/Program_Files/Program_IO/RT_RK_D/TC_1e10
rm ~/Dropbox/Program_IO/PD_RK/*.bin

echo "done" 

