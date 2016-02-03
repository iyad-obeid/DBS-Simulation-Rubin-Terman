/* 
 * File:   Neuron.cpp
 * Author: Chris
 * 
 * Created on May 24, 2011, 12:01 PM
 */

#include "Neuron.h"
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<math.h>
using namespace std;
void Neuron::set_params(const char* _type, int _index){
    strcpy(type,_type);
    index = _index;
}
int Neuron::get_index()const{
    return index;
}
const char* Neuron ::get_type()const{
    return type;
}
double Neuron::getTime()const{
    return t;
}
void Neuron::update(){

}
void Neuron:: close_files(){}

Neuron::syn_data Neuron:: get_s(){
    return s_dat;
}
Neuron::syn_data Neuron:: get_s_G(){
    return s_dat_G;
}
void Neuron:: add_synapse(Neuron* p){
    presynaptics.push_back(p);
}
double Neuron::interpolate(syn_data temp_dat,double t_int){
    if(t_int>temp_dat.t_old &&t_int<temp_dat.t_curr){
        return temp_dat.s_old+fabs(temp_dat.s_curr-temp_dat.s_old)
                *((t_int-temp_dat.t_old)/(temp_dat.t_curr-temp_dat.t_old));
    }else{
        
        return temp_dat.s_old;
    
    }
}
