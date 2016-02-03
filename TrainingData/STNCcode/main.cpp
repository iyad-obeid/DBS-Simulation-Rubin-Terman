/* 
 * File:   main.cpp
 * Author: Chris
 *
 * Created on May 4, 2011, 11:20 AM
 */

//Hodgkin Huxley Test
#include<iostream>
#include<cmath>
#include<fstream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include "STN.h"
using namespace std;




int main (int argc, char **argv)
{
  int opt = 0;
  int counter = 0;
  double sim_length,timer;
  double abs_error;
  timer = 0;
  if (argc>1){
    opt = atoi(argv[1]);
    sim_length = atof(argv[2]);
    abs_error = atof(argv[3]);
  }
  cout << "Confirming: opt = " << opt << endl;
  STN* STN_neurons;
  STN_neurons = new STN[1];
  STN_neurons[0].init(opt,sim_length);
  while(timer<sim_length){
      STN_neurons[0].update(opt,abs_error);
      timer = STN_neurons[0].t;
      cout<<"time:  "<<timer<<endl;
      counter++;
  }
  char fname [150];
    int num = 0;


    sprintf(fname,"VSTN_gsl%03i.bin",num );
    ofstream file_volt(fname);
    file_volt.write((char *)&STN_neurons[0].v[0]  , sizeof(double)*STN_neurons[0].v.size());
    file_volt.close();

    sprintf(fname,"TSTN_gsl%03i.bin",num );
    ofstream file_time (fname);
    file_time.write((char *)&STN_neurons[0].time_vector[0]  , sizeof(double)*STN_neurons[0].time_vector.size());
    file_time.close();

    sprintf(fname,"ISTN_gsl%03i.bin",num );
    ofstream file_current(fname);
    file_current.write((char *)&STN_neurons[0].synCurrent[0]  , sizeof(double)*STN_neurons[0].synCurrent.size());
    file_current.close();

  return 0;
}

