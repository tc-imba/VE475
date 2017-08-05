syms x y x_1 x_2 y_1 y_2 m b c y1 y2
m=(3*x_1^2+b)/(2*y_1);
x=m^2-x_1-x_1;
y=m*(x_1-x)-y_1;

p1=simplify(expand(x^3+b*x+c-y^2))
p2=p1*-(x_1-x_2)^3;
y_1=sqrt(x_1^3+b*x_1+c);
y_2=sqrt(x_2^3+b*x_2+c);
m=(3*x_1^2+b)/(2*y_1);
x=m^2-x_1-x_1;
y=m*(x_1-x)-y_1;
p1=simplify(expand(x^3+b*x+c-y^2))
