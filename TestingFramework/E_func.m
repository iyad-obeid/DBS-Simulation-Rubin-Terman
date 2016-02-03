function [ error ] = E_func(x,v,v_prime,t,delta_t,IProfile,C,c)

[vm,vm_prime]=genDat(t,delta_t,x,IProfile,C,c);

n_bins = 300;% was 180, may want to experiment with different sizes
hist_size = [n_bins,n_bins];
%whos('v','v_prime','vm','vm_prime')
real_data = hist3([v,v_prime],hist_size);
model_data = hist3([vm',vm_prime'],hist_size);

% for i = 1: length(v)
%     for j = 1: length(v_prime)
%         total = total + ...
%             (norm_data(v(i,j),v_prime(i,j),t)...
%             -norm_data(vm(i,j),vm_prime(i,j)...
%             ,t))^2;
%     end
% end
num_pts_real = length(v);
num_pts_model = length(vm);
real_data = real_data./num_pts_real;
model_data = model_data./num_pts_model;
error = sum(sum((...
    (real_data - model_data).^2).^(1/2)));
end

