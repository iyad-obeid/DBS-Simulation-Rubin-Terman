%find tradjectories and nullclines
clear;clf;
global C k vr vt a b vpeak d;
C=100; k=0.4;
vr = -60; vt = -40;
a = 0.03; b = -2;
v_reset = -50;
d = 100;
vpeak = 35;
T = 1000; %ms
tau = 0.01; %ms
n = (T/tau);%timesteps


I_amp = 2.0;
v = (vr)*ones(1,n); 
u = zeros(1,n); % initial values

I = I_amp*C.*ones(1,n);
I_offset = 155.0;
 % pulse of input DC current
num_spikes = 0;
for i=1:n-1
    % forward Euler method
   
   
    
    v(i+1)=v(i)+tau*(k*(v(i)-vr)*(v(i)-vt)-u(i)+I(i)+I_offset)/C;
    u(i+1)=u(i)+tau*a*(b*(v(i)-vr)-u(i));
    if v(i+1)>=vpeak % a spike is fired!
        
        num_spikes = num_spikes +1;
        v(i)=vpeak; % padding the spike amplitude
        v(i+1)=v_reset; % membrane voltage reset
        u(i+1)=u(i+1)+d; % recovery variable update
    end
    
      
end

        
    


figure(1);
subplot(2,1,1);
% plot(v,u,'k');hold on;
plot(tau.*(1:n), u);
% axis([-90,vpeak,-200,100]);
xlabel('voltage');
ylabel('recovery variable u');

subplot(2,1,2);
plot(tau.*(1:n),v(1:n));hold on;
xlabel('ms');
ylabel('v');
disp(num_spikes);