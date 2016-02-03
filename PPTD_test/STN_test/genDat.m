function [ v,vprime ] = genDat( t,delta_t, x, IProfile )
%generate data set based on given parameter values
%the IProfile is the Current profile based on time
%create izhikevich test data
%%%%%%%%%%%%%%DEFAULT VALUES%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
C = 50; 
vr = -80; 
vt = -25; 
k = 1.0;
b = -20; 
a = 0.01; 
c = -40; 
d = 150;
I_app = 0;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%SET Parameter Values%%%%%%%%%%%%%%%%%%%%
n_arg = length(x);

if(n_arg>0)
    for i = 1:n_arg
       switch i 
           case 1
               a = x(i);
               
           case 2
               b = x(i);
               
           case 3
               vr = x(i);
               
           case 4
               vt = x(i);
               
           case 5
               I_app = x(i);
               
           case 6
               d = x(i);
               
           case 7
               k = x(i);
           case 8 
               c = x(i);
               
       end
    end
end
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 
%%%%%%%%%%%%%%%%%Generate Data based on the parameters%%%%%%%%%%%
vpeak = 35;

v = zeros(1,length(t));
u = zeros(1,length(v));
v_prime = zeros(1,length(v));
v(1) = vr;

    for i = 1:length(t)-1
        % the internally applied current + input current
        I = I_app + IProfile(i)*C;
        v(i+1)=v(i)+delta_t*(k*(v(i)-vr)*(v(i)-vt)-u(i)+I)/C;
        u(i+1)=u(i)+delta_t*a*(b*(v(i)-vr)-u(i));
        v_prime(i) = (v(i+1)-v(i))/delta_t;
        if v(i+1)>=vpeak % a spike is fired!
           
            v(i)=vpeak; % padding the spike amplitude
            v(i+1)=c; % membrane voltage reset
            u(i+1)=u(i+1)+d;
        end
    end
end




