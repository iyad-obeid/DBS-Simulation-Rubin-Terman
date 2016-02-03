%find tradjectories and nullclines
clear;clf;
global C k vr vt a b vpeak d;
C=100; k=0.7;
vr = -60; vt = -40;
a = 0.03; b = -2;
.0;
d = 100;
vpeak = 35;
T = 2500; %ms
tau = 0.01; %ms
n = (T/tau);%timesteps


I_amp = 50.0;
v = (vr)*ones(1,n); 
u = zeros(1,n); % initial values

I = I_amp*C.*ones(1,n);
I_offset = 57.0;
 % pulse of input DC current

for i=1:n-1
    % forward Euler method
    if(i*tau <1000 || i*tau>1500)
        I(i)=0;
    end
    
    
    v(i+1)=v(i)+tau*(k*(v(i)-vr)*(v(i)-vt)-u(i)+I(i)+I_offset)/C;
    u(i+1)=u(i)+tau*a*(b*(v(i)-vr)-u(i));
    if v(i+1)>=0 % a spike is fired!
        disp('spike fired');
        v(i)=vpeak; % padding the spike amplitude
        v(i+1)=-50; % membrane voltage reset
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
plot(tau.*(1:n),v);hold on;
xlabel('ms');
ylabel('v');