//
//  main.cpp
//  
//
//  Created by Chris Tufts on 9/11/12.
//
//

#include <stdio.h>
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


using namespace std;

int main(){
    
    double tau = 0.01; //ms
    double T = 1000; //ms period of simulation
    int n = int(T/tau);
    cout << "n = "<< n << endl;
    
    double a = 0.01;
    double scaling_factor = 0.1;
    double b = 0;
    double C = 200.0;
    double d = 10.0;
    double k = 1.6;
    double vr = -65.0;
    double vt = -60.0;
    double vpeak = 35.0;
    double *v;
    double *u;
    v = new double[n];
    u = new double[n];
    
    for (int i = 0; i<n; i++) {
        v[i]=-65.0;
        u[i]=0;
    }
    //run simulation
    double I = 200.0;
    for (int i = 0; i<n-1; i++) {
        //test_neuron.update(i,tau,I);
        v[i+1]=v[i]+(1.0/C)*tau * (k * (v[i]-vr)*(v[i]-vt) + I -u[i]);
        u[i+1]=u[i]+ tau * a * (b * (v[i]-vt) -u[i]);
        if (v[i+1]>=(vpeak+ scaling_factor * u[i+1])) {
            v[i]=vpeak;
            v[i+1]=vr-(scaling_factor * u[i+1]);
            u[i+1]=u[i+1]+d;
            cout << "spike fired"<<endl;
            cout << "new v = "<<v[i+1]<<endl;
        }
        
        if (v[i]<vr) {
            b = 20.0;
            
        }else b = 0.0;
    }
    
    ofstream mystream;
    mystream.open("v.bin",ios::out | ios::binary);
    mystream.write((char*)&v[0], sizeof(double)*n);
    mystream.close();
    mystream.open("u.bin",ios::out | ios::binary);
    mystream.write((char*)&u[0], sizeof(double)*n);
    mystream.close();
    
    
    return 0;
   
}