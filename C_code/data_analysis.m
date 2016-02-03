clf;clear;
fid = fopen('v.bin', 'r');
v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
plot(t,v);