function [v,h,r,t] = tc_rt_obeid(fig_type,ismHz)

gL  = 0.05;     El  = -70;
gNa = 3;        Ena =  50;
gK  = 5;        Ek  = -90;
gT  = 5;        Et  =   0;

iSm = 5;
rhoSm = 1000/ismHz;
deltaSm = 5;

dt = 0.001;
tvec = -10:dt:500;

vvec = 0*tvec - 65;
hvec = 0*tvec;
rvec = 0*tvec;

v = vvec(1);
h = hvec(1);
r = rvec(1);

for i = 2:length(tvec)
    
    t = tvec(i);
    
    Il  = gL                *(v-El );
    Ina = gNa*mInf(v)^3*h   *(v-Ena);
    Ik  = gK*(0.75*(1-h))^4 *(v-Ek );
    It  = gT*pInf(v)^2*r    *(v-Et );
    
    if strcmp(fig_type,'2a')
        if (t>125 && t<275)
            Igt = 2;
        elseif (t>425 && t<575)
            Igt = 5;
        elseif (t>725 && t<875)
            Igt = 10;
        else
            Igt = 0;
        end
        Ism = 0;
    elseif strcmp(fig_type,'2b')
        if (t>125 && t<275)
            Igt = -.5;
        elseif (t>425 && t<575)
            Igt = -1;
        else
            Igt = 0;
        end
        Ism = 0;
    elseif strcmp(fig_type,'3a')
        Igt = 0;
        Ism = iSm * H(sin(2*pi*t/rhoSm)) * (1 - H(sin(2*pi*(t+deltaSm)/rhoSm)));
        if (t<0)
            Ism = 0;
        end;
    elseif strcmp(fig_type,'3b')
        Igt = -1;
        Ism = iSm * H(sin(2*pi*t/rhoSm)) * (1 - H(sin(2*pi*(t+deltaSm)/rhoSm)));
        if (t<0)
            Ism = 0;
        end;
    end
    
    vhat = -Il -Ina -Ik -It +Igt +Ism;
    hhat = (hInf(v) - h)/tauH(v);
    rhat = 5.5*(rInf(v) - r)/tauR(v);
    
    v = v + vhat*dt;
    h = h + hhat*dt;
    r = r + rhat*dt;
    
    vvec(i) = v;
    hvec(i) = h;
    rvec(i) = r;
    
end

clf;
plot(tvec,vvec);

function y = H(x)
y = double(x>0);

function y = hInf(v)
y = 1/(1+exp((v+41)/4));

function y = rInf(v)
y = 1/(1+exp((v+84)/4));

function y = mInf(v)
y = 1/(1+exp(-(v+37)/7));

function y = pInf(v)
y = 1/(1 + exp(-(v + 60)/6.2));

function y = tauH(v)
y = 1/(ah(v) + bh(v));

function y = tauR(v)
y = 28 + 0.3*exp(-(v + 25)/10.5);

function y = ah(v)
y = .128*exp(-(v + 46)/18);

function y = bh(v)
y = 4/(1 + exp(-(v + 23)/5));
