//
//  main.cpp
//  
//
//  Created by Christopher Tufts on 9/10/12.
//
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Neuron.h"

using namespace std;

int main(){
    
    double tau = 0.01; //ms
    double T = 1000; //ms period of simulation
    int n = int(T/tau);
    cout << "n = "<< n << endl;
    
    double a = 0.01;
    double b = 0;
    double C = 200.0;
    double d = 10.0;
    double k = 1.6;
    double vr = -65.0;
    double vt = -60.0;
    double vpeak = 35.0;
    Neuron test_neuron(n, a, b, C, d,
                       k,vr, vt, vpeak,tau);
    //run simulation
    
    
    double I = 200.0;
    ofstream mystream;
    mystream.open("v.bin",ios::out | ios::binary);
    
    
    for (int i = 0; i<n-1; i++) {
        test_neuron.update(I);
        mystream.write((char*)test_neuron.get_v(), sizeof(double));
    }
    
    mystream.close();
    
    
    return 0;

}