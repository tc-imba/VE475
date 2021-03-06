F={};
fid=fopen('1.tex', 'w');
fprintf(fid, '$$\\begin{array}{ccc}\n');
for i=1:26
    str=sprintf('L:=Dom::GaloisField(3, 3, X^3+2*X^2+1): L(X^%d)', i);
    A=char(evalin(symengine, str));
    p1=strfind(A, '(poly');
    p2=strfind(A, ',');
    p2=p2(p2>p1);
    f=A(p1+6:p2(1)-1);
    f=strrep(f, '(-1)*', '- ');
    F=[F f];
    fprintf(fid, 'X^{%d} \\equiv %s \\mod P(X) ', i, f);
    if mod(i,3)==0 && i>0
        fprintf(fid, '\\\\\n');
    else
         fprintf(fid, '& ');
    end
end
fprintf(fid, '\\end{array}$$\n');
fclose(fid);

m='goodmorning';
m=double(m)-double('a')+1;
c=zeros(1,length(m));

fid=fopen('2.tex', 'w');
fprintf(fid, '$$');
for i=1:length(m)
    fprintf(fid, char(F(m(i))));
    if i<length(m)
        fprintf(fid, ',');
    end
end
fprintf(fid, '$$\n');
fclose(fid);

fid=fopen('3.tex', 'w');
fprintf(fid, '$$');
for i=1:length(m)
    str=sprintf('L:=Dom::GaloisField(3, 3, X^3+2*X^2+1): L((X+1)^18*(%s))', char(F(m(i))));
    A=char(evalin(symengine, str));
    p1=strfind(A, '(poly');
    p2=strfind(A, ',');
    p2=p2(p2>p1);
    f=A(p1+6:p2(1)-1);
    fprintf(fid, f);
    if i<length(m)
        fprintf(fid, ',');
    end
    for j=1:26
        if strcmp(F(j), f)
            c(i)=j;
            break;
        end
    end
end
fprintf(fid, '$$\n');
fclose(fid);
char(c+double('a')-1)