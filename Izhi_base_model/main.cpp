#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "I_neuron.h"

using namespace std;
void simulation();
int runTime = 1e5;
I_neuron a (0.03,-2.0,-50.0,100.0,35.0,runTime);

double* time_array;


int main (){
    FILE *fid, *fid2;
    fid = fopen("voltage.bin","wb");
    fid2 = fopen("times.bin","wb");
    simulation();
    cout<<"print files"<<endl;
    fwrite(a.v,sizeof(double),runTime,fid);
    if(fid == NULL)
        printf("Cannot open file");
    fclose(fid);
    fwrite(time_array,sizeof(double),runTime,fid2);
    if(fid2 == NULL)
        printf("Cannot open file");
    fclose(fid2);
    cout<<"files done printing"<<endl;
    return 0;
    

}
void simulation(){
    time_array = new double[runTime];
    double time_step = 0.1;

    for(int timer =0; timer<runTime; timer++){
        //determine I for each neuron
        a.update(timer,100);
        time_array[timer]=timer*time_step;
    }
    
    
    return;
    
}
