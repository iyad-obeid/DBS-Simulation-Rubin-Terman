%find tradjectories and nullclines
clear;clf;
C=200; k=0.2;
vr = -65; vt = -60;
a = 0.01; b = 0;
d = 10;
vpeak = 35;
vreset = -70;
T = 1000; %ms
tau = 0.01; %ms
n = (T/tau);%timesteps
amp = 5;
rho = 25;%25 - 40 Hz, 100 - 10 Hz
delta = 5;
trials = 6;


v = vr*ones(trials,n); 
u = zeros(trials,n); % initial values
I_amp = 0.0;
Ism = zeros(2,n);%cortical input
I = zeros(1,n);

 % pulse of input DC current
for j = 1:2
    if(j==1)
        rho = 100;
    else
        rho = 40;
    end
    for i=1:n-1
        % forward Euler method

        if(sin(2*pi*i*tau/rho)>0)
            term1=1;
        else
            term1 = 0;
        end
        if(sin(2*pi*(i*tau + delta)/rho) > 0)
            term2 = 1;
        else
            term2 = 0;
        end
        Ism(j,i)=amp*term1*(1-term2)*C;
    end
end
   
% for j = 1:trials
 for j = 1:2
    if(j==1)
        I = zeros(1,n);
        start = round(125/tau);
        end_pt = round(275/tau);
        I_amp = 2;
        I(start:end_pt)= I_amp*C;

        start = round(425/tau);
        end_pt = round(575/tau);
        I_amp = 5;
        I(start:end_pt)= I_amp*C;

        start = round(725/tau);
        end_pt = round(875/tau);
        I_amp = 10;
        I(start:end_pt)= I_amp*C;
        
    end
    if(j==2)
        I = zeros(1,n);
        start = round(150/tau);
        end_pt = round(250/tau);
        I_amp = -0.75;%0.5
        I(start:end_pt)= I_amp*C;

        start = round(600/tau);
        end_pt = round(700/tau);
        I_amp = -1.0;
        I(start:end_pt)= I_amp*C;
    end
    if(j==3)
        I_amp = 0.0;
        I(1:n) = I_amp*C+Ism(1,:);
    end
    if(j==4)
        I_amp = 0.0;
        I(1:n) = I_amp*C+Ism(2,:);
    end
    if(j==5)
        I_amp = -1.0;
        I(1:n) = I_amp*C+Ism(1,:);
    end
    if(j==6)
        I_amp = -1.0;
        I(1:n) = I_amp*C+Ism(2,:);
    end
    for i=1:n-1  
        
        v(j,i+1)=v(j,i)+tau*(k*(v(j,i)-vr)*(v(j,i)-vt)-u(j,i)+I(i))/C;
        u(j,i+1)=u(j,i)+tau*a*(b*(v(j,i)-vr)-u(j,i));
        if v(j,i+1)>=vpeak%+0.1*u(j,i+1) % a spike is fired!
            v(j,i)=vpeak; % padding the spike amplitude
            v(j,i+1)=vreset;%-0.1*u(j,i+1); % membrane voltage reset
            u(j,i+1)=u(j,i+1)+d; % recovery variable update
        end

        if(v(j,i)<vreset)
            b = 20;
            k = 1.6;
        else
            b = 0;
            k = 1.6;%0.02;
        end
    end

% subplot(2,3,j);
subplot(2,1,j);
plot(tau.*(1:n),v(j,:));hold on;
if(j==1)
    plot(tau.*(1:n),(I./100)-200,'r');hold on;
else
    plot(tau.*(1:n),(I./10)-200,'r');hold on;
end

xlabel('ms','FontSize',18);
ylabel('mv','FontSize',18);
end