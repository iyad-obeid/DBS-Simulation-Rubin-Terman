%%%%%%%%Description of GA algorithm%%%%%%%%%%%%%%%%%%%%%
% [x fval] = ga(@fitnessfun, nvars, options)
% where
%  @fitnessfun is a handle to the fitness function. 
% ? nvars is the number of independent variables for the fitness function.
%  options is a structure containing options for the genetic algorithm. If you do not pass in this argument, ga uses its default options.
% Theresults are given by x ? Point at which the final value is attained 
% ? fval ? Final value of the fitness function

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% the x array is defined as follows
% x = [a,b,vr,vt,I_app,d,k,c]



clf;clc;clear;
load STN_30Inhib;
delta_t = 0.01;
a = 0.1;
b = -20;
vr = -80;
vt = -25;
I_app = 325;
d = 150;
k = 1.0;
c = -40;
x0 = [a,b,vr,vt,I_app,d,k,c];
t = 0:delta_t:2500;

% load('STN_30Inhib.mat')
% a = 100; b = 1; % define constant values
% FitnessFunction = @(x) parameterized_fitness(x,a,b);
% numberOfVariables = 2;
% [x,fval] = ga(FitnessFunction,numberOfVariables)
FitnessFunc = @(x) E_func(x,v,dv,t,delta_t);
numOfVariables = 8;
% b = [0.1,0,30,30,-45,70,-30,60,400,0,200,0,...
%     2.0, -0.001, -55,80]';

options = gaoptimset('InitialPopulation',x0,'Generations',100,...
    'TolFun', 1e-6,'PopulationSize',20);
% lb = b(2:2:16).*-1;
% ub = b(1:2:16);
[x,fval] = ga(FitnessFunc,numOfVariables,[],[],[],[],[],[],[],[],options);
%x = ga(@E_func,8);