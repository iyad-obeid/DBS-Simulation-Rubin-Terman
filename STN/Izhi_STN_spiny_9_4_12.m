%find tradjectories and nullclines
clear;clf;
global C k vr vt a b vpeak d;
C=50; k=1.0;
vr = -80; vt = -25;
a = 0.01; b = -20;
v_reset = -55;
d = 150;
vpeak = 40;
T = 10000; %ms
tau = 1.0; %ms
n = (T/tau);%timesteps


I_amp = 50.0;
v = (vr)*ones(1,n); 
u = zeros(1,n); % initial values

I = I_amp*C.*ones(1,n);
I_offset = 325.0;
 % pulse of input DC current

for i=1:n-1
    % forward Euler method
   if(tau*i<2500 || tau*i>3000)
       I(i) = 0;
   end
  
    
    v(i+1)=v(i)+tau*(k*(v(i)-vr)*(v(i)-vt)-u(i)+I(i)+I_offset)/C;
    u(i+1)=u(i)+tau*a*(b*(v(i)-vr)-u(i));
    if v(i+1)>=vpeak % a spike is fired!
        disp('spike fired');
        v(i)=vpeak; % padding the spike amplitude
        v(i+1)=v_reset; % membrane voltage reset
        u(i+1)=u(i+1)+d; % recovery variable update
    end
    
    %circumvent hyperpolarization
    if(v(i+1)<-80)
      u(i+1) = -350;
      v(i+1) = v_reset;
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
plot(tau.*(2000:4000),v(2000:4000));hold on;
xlabel('ms');
ylabel('v');