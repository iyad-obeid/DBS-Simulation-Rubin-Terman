clf;clear;
path = '/Users/chris/Dropbox/NIL_references';
path = sprintf('%s/Code_Masters_Thesis/C_code/',path);
path = sprintf('%sIzhi_net/Izhikevich_Network',path);
fileName = sprintf('%s/v_fig4A.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
plot(t,v)