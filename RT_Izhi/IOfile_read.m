function[current] = IOfile_read(ValueName)

fname = sprintf('/Users/Chris/Dropbox/Program_IO/PD_RK/testFile%s.bin',ValueName);
disp(fname);
fid = fopen(fname,'rb');
current = fread(fid,'double');
fclose(fid);


    