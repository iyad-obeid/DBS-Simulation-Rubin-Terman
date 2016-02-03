%%
STN_v = IOfile_read('_n_STN_gsl001');
STN_t = IOfile_read('Times_n_STN_gsl001');
plot(STN_t, STN_v);
title('STN')
%%
TC_v = IOfile_read('_n_TC_gsl001');
TC_t = IOfile_read('Times_n_TC_gsl001');
plot(TC_t, TC_v);
title('TC')
%%
GPi_v = IOfile_read('_n_GPi_gsl001');
GPi_t = IOfile_read('Times_n_GPi_gsl001');
plot(GPi_t, GPi_v);
title('GPi')
%%
GPe_v = IOfile_read('_n_GPe_gsl001');
GPe_t = IOfile_read('Times_n_GPe_gsl001');
plot(GPe_t, GPe_v);
title('GPe')