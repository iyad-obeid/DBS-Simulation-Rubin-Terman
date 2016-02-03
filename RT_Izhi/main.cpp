/*
 * File:   main.cpp
 * Author: Chris
 *
 * Created on April 29, 2011, 1:23 PM
 */


//Hodgkin Huxley Test
#include<iostream>
#include<typeinfo>
#include <queue>
#include<list>
#include<cmath>
#include<fstream>
#include "Neuron.h"
#include <string.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include <queue>
#include <list>
#include "GPi.h"
#include "GPe.h"
#include "STN.h"
#include "TC.h"
#define TC_net_size 2
#define STN_net_size 16
#define GPe_net_size 16
#define GPi_net_size 16







using namespace std;
Neuron** net;

int main (int argc, char **argv)
{

  

  int index,neuron_type;
  //neuron_type 0-GPe,1-GPi,2-TC,3-STN/////////////////////////////////
  double minTime,oldTime;
  int counter = 0;
  double temp_time;
  int opt = 0;
  double sim_length = 500.0;
  double abs_error_gpi = 1e-12;
  double abs_error_gpe = 1e-12;
  double abs_error_stn = 1e-12;
  double abs_error_tc  = 1e-12;
  double timer = 0;

  if (argc>1)
    opt = atoi(argv[1]);
  if (argc>2)
    sim_length = atof(argv[2]);
  if (argc>3)
    abs_error_gpi = atof(argv[3]);
  if (argc>4)
    abs_error_gpe = atof(argv[4]);
  if (argc>5)
    abs_error_stn = atof(argv[5]);
  if (argc>6)
    abs_error_tc = atof(argv[6]);

  cout << "Confirming: opt = " << opt << endl;
  cout<<"Simulation length: "<<sim_length<<"ms"<<endl;
  #ifdef PARKINSONS
  cout<<"parkinsons"<<endl;
  #endif
  #ifdef DBS
  cout<<"DBS"<<endl;
  #endif
#ifdef ALLDATA
    cout<<"ALLDATA"<<endl;
#endif
  int net_size = GPi_net_size+GPe_net_size+STN_net_size+TC_net_size;

  GPi GPi_neurons[GPi_net_size];
  GPe GPe_neurons[GPe_net_size];
  STN STN_neurons[STN_net_size];
  TC TC_neurons[TC_net_size];
  net = new Neuron*[net_size];

  for(int i = 0; i<GPi_net_size;i++){
      GPi_neurons[i].init(opt,sim_length,abs_error_gpi,i);
      net[counter]=GPi_neurons+i;
      counter++;
  }

//  create GPe neurons
    for(int i = 0; i<GPe_net_size;i++){
      GPe_neurons[i].init(opt,sim_length,abs_error_gpe,i);
      net[counter]=GPe_neurons+i;
      counter++;
   }

//  create STN neurons
   for(int i = 0; i<STN_net_size;i++){
      STN_neurons[i].init(opt,sim_length,abs_error_stn,i);
      net[counter]=STN_neurons+i;
      counter++;

   }

   for(int i = 0; i<TC_net_size;i++){
      TC_neurons[i].init(opt,sim_length,abs_error_tc,i);
      net[counter]=TC_neurons+i;
      counter++;
  }
//add synaptic connections///////////////////////////////////////

  for(int i = 0; i<GPi_net_size;i++){
      GPi_neurons[i].add_synapse(STN_neurons+i);
      GPi_neurons[i].add_synapse(GPe_neurons+i);
  }

  //  create GPe neurons
    for(int i = 0; i<GPe_net_size;i++){
        if(i==STN_net_size-2){
            GPe_neurons[i].add_synapse(STN_neurons+i);//[i]
            GPe_neurons[i].add_synapse(STN_neurons+i+1);//[i+1]
            GPe_neurons[i].add_synapse(STN_neurons);//[0]
            GPe_neurons[i].add_synapse(GPe_neurons+i+1);//index+1
            GPe_neurons[i].add_synapse(GPe_neurons);//[0]
        }else if(i==(STN_net_size-1)){
            GPe_neurons[i].add_synapse(STN_neurons+i);//[i]
            GPe_neurons[i].add_synapse(STN_neurons);//[0]
            GPe_neurons[i].add_synapse(STN_neurons+1);//[1]
            GPe_neurons[i].add_synapse(GPe_neurons);//[0]
            GPe_neurons[i].add_synapse(GPe_neurons+1);//[1]
        }else{
            GPe_neurons[i].add_synapse(STN_neurons+i);//[i]
            GPe_neurons[i].add_synapse(STN_neurons+i+1);//[i+1]
            GPe_neurons[i].add_synapse(STN_neurons+i+2);//[i+2]
            GPe_neurons[i].add_synapse(GPe_neurons+i+1);//[i+1]
            GPe_neurons[i].add_synapse(GPe_neurons+i+2);//[i+2]

        }
  }

//  create STN neurons
   for(int i = 0; i<STN_net_size;i++){
       if(i==GPe_net_size-1){
           STN_neurons[i].add_synapse(GPe_neurons+i);//[i]
           STN_neurons[i].add_synapse(GPe_neurons);//[0]
       }else{
           STN_neurons[i].add_synapse(GPe_neurons+i);
           STN_neurons[i].add_synapse(GPe_neurons+i+1);
       }
   }
   for(int i = 0; i<TC_net_size;i++){
       if(i<1){
           for(int k = 0; k<(GPi_net_size/2);k++){
                  TC_neurons[i].add_synapse(GPi_neurons+k);
           }
       }else{
           for(int k = (GPi_net_size/2);k<GPi_net_size;k++){
               TC_neurons[i].add_synapse(GPi_neurons+k);
           }
       }
   }



////////////////////////RUN SIMULATION//////////////////////////
 while(timer<sim_length){
    minTime = 1e9;
    for(int i=0;i<net_size;i++){
      temp_time =net[i]->getTime();
      if(temp_time<minTime){
	minTime =temp_time;
	index = i;
      }
    }
/*
    if (floor(minTime-oldTime)>1){
      oldTime = minTime;
      cout<<"time = "<<minTime<<endl;
    }
*/
    net[index]->update();
    timer = minTime;
  }






      for(int i =0;i<net_size;i++)
          net[i]->close_files();
  delete[] net;

}
