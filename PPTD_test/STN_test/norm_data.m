function [ sigma ] = norm_data( x,y,t )
%normalize points on phase plane
    N = length(x);
    total = 0;
    for i = 1:length(t)
        total = total + flag(x(i),y(i));
    end
    sigma = total/N;
     

end

