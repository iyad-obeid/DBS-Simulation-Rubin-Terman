function[current] = myFileReader(ValueName,num)

fname = sprintf('%s%03i.bin',ValueName,num);
disp(fname)
fid = fopen(fname,'rb');
current = fread(fid,'double');
fclose(fid);


    