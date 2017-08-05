function y = modinv(x,N)
    r1=x;r2=N;
    s1=1;s2=0;
    while r2>0
        q=floor(r1/r2);
        temp=r2;
        r2=r1-q*r2;
        r1=temp;
        temp=s2;
        s2=s1-q*s2;
        s1=temp;
    end
    y=mod(s1,N);
end