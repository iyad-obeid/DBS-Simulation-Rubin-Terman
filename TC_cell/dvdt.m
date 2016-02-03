function dv = dvdt(v, u, I)
    global C vr vt k d vpeak;
    if(v>vpeak + 0.1*u)
        v=vr-0.1*u;
        u=u+d;
    end
        dv=(k*(v-vr)*(v-vt)-u+I)/C;
end