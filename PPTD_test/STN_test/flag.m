function [ nu ] = flag( x,y )
%determine if x and y are equal
    nu = 0;    
    if(abs(x-y)<1e-8)
        nu = 1;
    end

end

