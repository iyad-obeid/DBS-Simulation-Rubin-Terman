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
load STNZeroInput;
delta_t = 0.01;
%all variables are shown as vectors
%[initial guess, lower bound, upper bound]
a = [0.1,0.001,0.2];
b = [0,-5,20];
vr = [-60,-80,-55];
vt = [-40,-50,-25];
I_app = [10,0,500];
d = [50,0,200];
k = [1.0,0.001,2.0];
c = -60;
C = 50;
x0 = [a(1),b(1),vr(1),vt(1),I_app(1),d(1),k(1)];
lb = [a(2),b(2),vr(2),vt(2),I_app(2),d(2),k(2)];
ub = [a(3),b(3),vr(3),vt(3),I_app(3),d(3),k(3)];
%t = 0:delta_t:2500;
subplot(3,1,1);
plot(t,v);
subplot(3,1,2);
plot(t,dv)
subplot(3,1,3);
plot(t,IProfile);
%%
% load('STN_30Inhib.mat')
% a = 100; b = 1; % define constant values
% FitnessFunction = @(x) parameterized_fitness(x,a,b);
% numberOfVariables = 2;
% [x,fval] = ga(FitnessFunction,numberOfVariables)
FitnessFunc = @(x) E_func(x,v,dv,t,delta_t,IProfile,C,c);
numOfVariables = 7;
% b = [0.1,0,30,30,-45,70,-30,60,400,0,200,0,...
%     2.0, -0.001, -55,80]';

options = gaoptimset('InitialPopulation',x0,'Generations',100,...
    'TolFun', 1e-6,'PopulationSize',20);
% lb = b(2:2:16).*-1;
% ub = b(1:2:16);
A = []; b = []; Aeq=[];beq = [];
nonlcon = [];
%ga(fitnessfcn,nvars,A,b,Aeq,beq,LB,UB,nonlcon,options)
[x,fval] = ga(FitnessFunc,numOfVariables,A,b,Aeq,beq,lb,ub,nonlcon,options);
%x = ga(@E_func,8);
%%
clf;
[vnew,vprimeNew]=genDat(t,delta_t,x,IProfile,C,c);
plot(t,vnew);hold on;
plot(t,v,'r');