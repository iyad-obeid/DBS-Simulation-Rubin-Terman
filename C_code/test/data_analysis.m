clc;clear;
%% figure 1/(Figure 2 in RT)
figure(1); clf;
path = '/Users/chris/Dropbox/NIL_references';
path = sprintf('%s/Code_Masters_Thesis/C_code/',path);
path = sprintf('%sIzhi_net/Izhikevich_Network',path);
fileName = sprintf('%s/v_fig2_bottom.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);

subplot(2,1,2);
plot(t,v);
xlabel('time(ms)','FontSize',18);
ylabel('voltage(mv)','FontSize',18);


fileName = sprintf('%s/v_fig2_top.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
figure(1)
subplot(2,1,1);
plot(t,v);
xlabel('time(ms)','FontSize',18);
ylabel('voltage(mv)','FontSize',18);

%%
figure(2);clf;
fileName = sprintf('%s/v_fig3_A1.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
subplot(2,2,1);
plot(t,v);
xlabel('time(ms)','FontSize',18);
ylabel('voltage(mv)','FontSize',18);

fileName = sprintf('%s/v_fig3_A2.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
subplot(2,2,3);
plot(t,v);
xlabel('time(ms)','FontSize',18);
ylabel('voltage(mv)','FontSize',18);

fileName = sprintf('%s/v_fig3_B1.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
subplot(2,2,2);
plot(t,v);
xlabel('time(ms)','FontSize',18);
ylabel('voltage(mv)','FontSize',18);

fileName = sprintf('%s/v_fig3_B2.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
subplot(2,2,4);
plot(t,v);
xlabel('time(ms)','FontSize',18);
ylabel('voltage(mv)','FontSize',18);


%% figure (3)/figure 4 in RT
figure(3);clf;

fileName = sprintf('%s/v_fig4A.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
subplot(2,2,1);
plot(t,v);
axis([1000, 3500, -120,50]);
xlabel('time(ms)','FontSize',20);
ylabel('voltage(mv)','FontSize',20);

fileName = sprintf('%s/v_fig4B.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
subplot(2,2,3);
plot(t,v);
axis([1000, 3500, -120,50]);
xlabel('time(ms)','FontSize',20);
ylabel('voltage(mv)','FontSize',20);

fileName = sprintf('%s/v_fig4C.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
subplot(2,2,2);
plot(t,v);
xlabel('time(ms)','FontSize',20);
ylabel('voltage(mv)','FontSize',20);

fileName = sprintf('%s/v_fig4D.bin',path);
fid = fopen(fileName, 'r');

v = fread(fid,'double');
fclose(fid);
tau = 0.01;
t = 0:tau:tau*(length(v)-1);
subplot(2,2,4);
plot(t,v);
axis([250, 2000, -120,50]);
xlabel('time(ms)','FontSize',20);
ylabel('voltage(mv)','FontSize',20);



