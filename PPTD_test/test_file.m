% generate test data
clear; clc;clf;
delta_t = 0.01;
t = 0:delta_t:2000;
[v,u,v_prime] = izhi(t,delta_t);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% the x array is defined as follows
% x = [a,b,vr,vt,I_app,d,k,c]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
n = 16; m = 8;
%x0 = [0.1,-2];
x0 = [0.01,0, -55, -45,0, 85, 0.60, -60];
% A = [1;-1];
A = zeros(n,m);
A(1,1) = 1; A(2,1) = -1;
A(3,2) = 1; A(4,2) = -1;
A(5,3) = 1; A(6,3) = -1;
A(7,4) = 1; A(8,4) = -1;
A(9,5) = 1; A(10,5) = -1;
A(11,6) = 1; A(12,6) = -1;
A(13,7) = 1; A(14,7) = -1;
A(15,8) = 1; A(16,8) = -1;

% b = [0.3,0,30,30,-45,70,-30,60,400,0,200,0,...
%     2.0, -0.001, -55,80]';
b = [0.3,0,30,30,-45,70,-30,60,400,0,200,0,...
    2.0, -0.001, -55,80]';

% b = [0.3;0];
%A = [-1,0; 1, 0 ; 0,1; 0,-1];
%b = [0;0.4;30;30];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%fmincon tests [local algorith]
%NOTE: double check the upper and lower bound conditions
algorithms = {'active-set', 'interior-point', 'sqp'};
num_opt = length(algorithms);
params = zeros(num_opt,m);
k = 1;
error_val = zeros(1,num_opt);
figure(1);
for i = 1:num_opt
    options = optimset('Algorithm',algorithms{i});

    [x,f_val] = fmincon(@E_func,x0,A,b,[],[],[],[],[],options);
    %[x,f_val] = fmincon(@E_func,x0,[],[],[],[],lb,ub);

    [vm,um,vm_prime] = izhi_test(t,delta_t,x);
    params(i,:) = x;
    error_val(i) = f_val;
    subplot(num_opt,2,k);
    k = k+1;
    plot(t,v);hold on;
    plot(t,vm,'r');
    title(algorithms{i});
    subplot(num_opt,2,k);
    k = k+1;
    plot(v,v_prime);hold on;
    plot(vm,vm_prime,'r');
    title(algorithms{i});
    
   
end
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Global Algorithms

clf;clc;clear;
delta_t = 0.01;
t = 0:delta_t:2000;
[v,u,v_prime] = izhi(t,delta_t);
% x = [a,b,vr,vt,I_app,d,k,c]
x0 = [0.01,-1, -65, -45,0, 85, 0.60, -60];

b = [0.1,0,30,30,-45,70,-30,60,400,0,200,0,...
    2.0, -0.001, -55,80]';
% options = gaoptimset('InitialPopulation',x0);
options = gaoptimset('InitialPopulation',x0,'Generations',100,...
    'TolFun', 1e-6,'PopulationSize',20);
% [x,fval] = ga(@E_func,8,[],[],[],[],[],[],[],[],options);

lb = b(2:2:16).*-1;
ub = b(1:2:16);
[x,fval] = ga(@E_func,8,[],[],[],[],lb,ub,[],[],options);
%x = ga(@E_func,8);
%%
clf;
[vm,um,vm_prime] = izhi_test(t,delta_t,x);
subplot(2,1,1);

    plot(t,v,'-k');hold on;
    plot(t,vm,'-r');
    title('Voltage Trace','FontSize', 18);
    xlabel('time(ms)','FontSize', 18);
    ylabel('voltage (mv)','FontSize', 18);
    legend('real data', 'model data');
   
    subplot(2,1,2);
    
    plot(v,v_prime,'-k');hold on;
    plot(vm,vm_prime,'-r');
    title('Phase Plane','FontSize', 18);
    xlabel('dv/dt','FontSize', 18);
    ylabel('voltage (mv)','FontSize', 18);
    legend('real data', 'model data');

