% this is the thalamic cortical relay neuron as specifically defined
% by Eugene Izhikevich ( p305 Izhi)

clear; clf; clc;

C=200; vr=-60; vt=-50; k = 1.6;%k=0.009;
a=0.01; b=0; d=10; % neocortical pyramidal neurons
vpeak=35; % spike cutoff
count = 0;% # of firings
T=1000; tau=0.001; % time span and step (ms)
n=round(T/tau); % number of simulation steps
v=vr*ones(1,n); u=0*v; % initial values


% sensory motor input from cortex
ism = 5;%amplitude
rho = 100;%period
delta = 5;%ontime
Ism = zeros(1,n);
% synaptic input from GPI
Igi = 0.0;
Igiv=Igi*ones(1,n);% pulse of input DC current


for i=1:n-1 % forward Euler method
%determing ISM
t=i*tau;
term_a=sin(2*pi*t/rho);
term_b = sin(2*pi*(t+delta)/rho);
if(term_a>=0)
    H1=1;
else
    H1=0;
end
if(term_b>=0)
    H2=1;
else
    H2=0;
end

Ism(i) = ism*H1*(1-H2);

% test settings
Ism(i) = 0;
if(tau*i>125&&tau*i<275)
 Ism(i) = 2.0/2;
end
if(tau*i>425&&tau*i<575)
 Ism(i) = 5.0/2;
end
if(tau*i>725&&tau*i<875)
  Ism(i) = 10.0/2;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
v(i+1)=v(i)+tau*(k*(v(i)-vr)*(v(i)-vt)-u(i)+Igiv(i)*C+Ism(i)*C)/C;
u(i+1)=u(i)+tau*a*(b*(v(i)+65)-u(i));
  if (v(i+1)>=(vpeak+0.1*u(i+1))) % a spike is fired!
      disp('spike')
    v(i)=vpeak; % padding the spike amplitude
    v(i+1)=-60-0.1*u(i+1); % membrane voltage reset
    u(i+1)=u(i+1)+d; % recovery variable update
    
    
  end
  if(v(i+1)>-65)
      b=0;
          
  else
      b=15;
      
  end
     
end
plot(tau*(1:n), v); hold on; % plot the result
%plot(tau*(1:n), u); hold on; % plot the result

