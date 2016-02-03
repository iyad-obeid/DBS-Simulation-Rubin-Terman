class I_neuron {
    double a,b,c,d,threshold;
    double tau,vr,vt,C,k;
    int num_steps;
    public:
    double* v;double* u;
public:
    I_neuron ();
    I_neuron (double,double,double,double,double,int);
    ~I_neuron ();
    void update(int, double);
};
