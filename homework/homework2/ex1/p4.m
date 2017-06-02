fid=fopen('p4.tex','w');
for m=0:30
    c=mod(m^7,31);
    fprintf(fid,' %d & %d ',m,c);
    if mod(m+1,4)==0
        fprintf(fid,'\\\\\n');
    else
        fprintf(fid,'&');
    end
end