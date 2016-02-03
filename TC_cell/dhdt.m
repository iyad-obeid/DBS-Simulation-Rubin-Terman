function [ dh ] = dhdt( hinf,h,Th )
  dh = (hinf - h)/Th;
end

