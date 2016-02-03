function du=dudt(v,u)
    global a b d vpeak vr b_rec;
    if(v>vpeak + 0.1*u)
            v = vr-0.1*u;
            u = u + d;
    end
        if(v<-65)
            b = b_rec;
        else
            b = 0;
        end 
    
    du = a*(b*(v+65)-u);
end