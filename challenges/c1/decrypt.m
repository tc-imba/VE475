global type_arr_simple type_simple;

freq=zeros(length(type_simple),1);
map=zeros(length(type_simple),1);

for i=1:length(type_simple)
    freq(i)=sum(type_arr_simple==i);
end

[freq,I]=sort(freq,'descend');
map(2)='e';
map(17)='e';
map(10)='t';
map(4)='a';


fid=fopen('c1.1.txt','w');

for i=1:length(type_arr_simple)
    output=' ';
    if map(type_arr_simple(i))
        output=char(map(type_arr_simple(i)));
    end
    fprintf(fid,output);
    if mod(i,80)==0
        fprintf(fid,'\n');
    end
end