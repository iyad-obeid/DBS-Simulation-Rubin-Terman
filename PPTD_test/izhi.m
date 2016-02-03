function [ v,u,v_prime ] = izhi( t,delta_t )
%create izhikevich test data
C = 100; vr = -60; vt = -40; k = 0.7;
a = 0.03; b = -2; c = -50; d = 100;
vpeak = 35;
v = zeros(1,length(t));
u = zeros(1,length(v));
v_prime = zeros(1,length(v));
v(1) = vr;
I = 70;
    for i = 1:length(t)-1
        v(i+1)=v(i)+delta_t*(k*(v(i)-vr)*(v(i)-vt)-u(i)+I)/C;
        u(i+1)=u(i)+delta_t*a*(b*(v(i)-vr)-u(i));
        v_prime(i) = (v(i+1)-v(i))/delta_t;
        if v(i+1)>=vpeak % a spike is fired!
            disp('spike fired');
            v(i)=vpeak; % padding the spike amplitude
            v(i+1)=c; % membrane voltage reset
            u(i+1)=u(i+1)+d;
        end
    end
end

