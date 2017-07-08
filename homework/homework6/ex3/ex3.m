fid=fopen('1.tex', 'w');
fprintf(fid, '$$\\begin{array}{ccc}\n');
for i=1:26
    str=sprintf('L:=Dom::GaloisField(3, 3, x^3+2*x^2+1): L(x^%d)', i);
    A=char(evalin(symengine, str));
    p1=strfind(A, '(poly');
    p2=strfind(A, ',');
    p2=p2(p2>p1);
    f=A(p1+6:p2(1)-1);
    f=strrep(f, '(-1)*', '- ');
    fprintf(fid, 'x^{%d} \\equiv %s \\mod P(x) ', i, f);
    if mod(i,3)==0 && i>0
        fprintf(fid, '\\\\\n');
    else
         fprintf(fid, '& ');
    end
end
fprintf(fid, '\\end{array}$$\n');
fclose(fid);
