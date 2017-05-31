global type_simple type_standard type_arr type_arr_simple;
type_simple=type_standard;
type_arr_simple=type_arr;

order=[1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 13 27 22 2 30 31 15 33 5 21 6 37 10 1 18 16 24 13 17 25 46 47 48 19 20 ...
    4 46 7 54 27 15 16 58 14 18 17 62 22 31 9 24 25 7 69 10 8 37 23 2 75 76 21 78 79 12 81 82 19 84 85 86 87 88 11 12 24 12 31 37 46 37 20 46 17 46 ...
    101 102 4 104 78 24 12 23 37 75 25 112 113 27 75 16 18 78 31 13 121 21 7 124 125 126 127 128 27 46 20 104 133 134 31 113 14 88 139 31 62 19 143 82 18 2 37 5 149 128 ...
    151 69 25 19 27 20 15 128 16 70 17 37 18 10 75 30 12 151 15 31 69 23 24 113 8 23 17 3 179 88 30 2 1 184 4 69 48 85 134 190 191 82 151 179 88 81 179 12 179 124 ...
    125 84 128 76 69 2 18 133 81 113 23 5 139 121 88 216 48 218 21 22 151 6 17 11 46 78 23 76 10 7 7 11 233 19 127 151 69];

[B,I]=sort(order);
last=0;arr=[];
for i=1:length(B)
    if last==B(i)
        arr=[arr,I(i)];
    else
        set_repeat(arr);
        last=B(i);
        arr=[B(i)];
    end
end

simplify_type();

figure(3);
imshow(combine(type_simple,25));

delete('simplified/*.bmp')
for i=1:length(type_simple)
    imwrite(combine(find(type_arr_simple==i),25),['simplified/' num2str(i) '.bmp']);
end

function set_repeat(arr)
    global type_arr_simple type_simple;
    l=length(arr);
    if l<2
        return;
    end
    arr=sort(arr);
    for i=2:l
        type_arr_simple(type_arr_simple==arr(i))=arr(1);
        type_simple(arr(i))=0;
    end
end

function simplify_type()
    global type_simple type_arr_simple;
    offset=0;
    for i=1:length(type_simple)
        if type_simple(i)==0
            offset=offset+1;
        else
            type_arr_simple(type_arr_simple==i)= ...
                type_arr_simple(type_arr_simple==i)-offset;
        end
    end
    type_simple(type_simple==0)=[];
end
