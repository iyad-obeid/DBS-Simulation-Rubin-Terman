clear;
clc;
num=0;

v = myFileReader('VSTN_gsl',num);

t = myFileReader('TSTN_gsl',num);
IProfile = myFileReader('ISTN_gsl',num);
subplot(2,1,1);

plot(t,v);
dv = zeros(length(v),1);
for i = 2:length(v)
    dv(i) = (v(i)-v(i-1))/(t(i)-t(i-1)); 
end
subplot(2,1,2)
plot(t,IProfile)
%%
