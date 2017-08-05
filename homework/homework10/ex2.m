calc(8,9,8,9,11,3);
calc(10,6,10,6,11,3);
calc(5,2,8,9,11,3);
calc(5,2,5,2,11,3);
calc(10,5,10,6,11,3);
calc(1,0,1,0,11,3);

fprintf('\n');

x1=8;y1=9;
x=8;y=9;
for i=1:9
    [x,y]=calc(x,y,x1,y1,11,3);
end

function [x,y]=calc(x1,y1,x2,y2,n,b)
    if x1==x2 && y1==y2
        m=sym(3*x1^2+b)/sym(2*y1);
    else
        m=sym(y2-y1)/sym(x2-x1);
    end
    [a,b]=numden(m);
    b=modinv(b,n);
    m=mod(a*b,n);
    x=mod(m^2-x1-x2,n);
    y=mod(m*(x1-x)-y1,n);
    fprintf('m=%d, x=%d, y=%d\n',m,x,y);
end