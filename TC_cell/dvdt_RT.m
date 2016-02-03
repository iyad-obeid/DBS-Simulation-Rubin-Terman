function [ dv ] = dvdt_RT(Il, Ina, Ik, It, Igi, Ism, C)
  dv = (-Il-Ina-Ik-It-Igi+Ism)/C;
end

