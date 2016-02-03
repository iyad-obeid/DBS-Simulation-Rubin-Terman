clf;clear;
path = '/Users/chris/Dropbox/NIL_references';
path = sprintf('%s/Code_Masters_Thesis/C_code/',path);
path = sprintf('%sIzhi_net/Izhikevich_Network',path);
fileName = sprintf('%s/voltages_net.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
fileName = sprintf('%s/Ism.bin',path);
fid = fopen(fileName, 'r');

ism = fread(fid,'double');
fclose(fid);

tau = 0.01;
net_size = 16;
total_n = 16*3 + 2;
samples = round(length(v)/total_n);
GPi = zeros(net_size, samples);
GPe = zeros(net_size, samples);
STN = zeros(net_size, samples);
TC = zeros(net_size, samples);
% GPi, GPe, STN, TC
gpe_count = 1;
stn_count = 1;
gpi_count = 1;
tc_count = 1;
for i = 1:total_n
    if(i<=net_size)
        disp(gpi_count)
        GPi(gpi_count,:) = v(i : total_n : end);
        gpi_count = gpi_count+1;
    end
    if(i>net_size && i<=net_size*2)
        GPe(gpe_count,:) = v(i : total_n : end);
        gpe_count = gpe_count+1;
    end
    if(i>net_size*2 && i<=net_size*3)
        STN(stn_count,:) = v(i : total_n : end);
        stn_count = stn_count+1;
    end
    
    if( i>net_size*3)
        TC(tc_count,:) = v(i : total_n : end);
        tc_count = tc_count+1;
    end
    
end

  t = 0:tau:tau*(samples-1);
  subplot(2,2,1)
  plot(t,STN(1,:));
  xlabel('time (ms))');
  ylabel('voltage (mv)');
  title('STN');
  
  subplot(2,2,2)
  plot(t,TC(1,:)); hold on;
  plot(t,ism-100);
  xlabel('time (ms))');
  ylabel('voltage (mv)');
  title('TC');
  
  subplot(2,2,3)
  plot(t,GPe(1,:));
  xlabel('time (ms))');
  ylabel('voltage (mv)');
  title('GPe');
  
  subplot(2,2,4)
  plot(t,GPi(1,:));
  xlabel('time (ms))');
  ylabel('voltage (mv)');
  title('GPi');