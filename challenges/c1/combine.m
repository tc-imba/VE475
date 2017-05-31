function img=combine(arr,width)
    global img_arr;
    img=zeros(0,32*width);
    num=0;
    for i=1:length(arr)
        x=floor(num/width)+1;
        y=mod(num,width)+1;
        num=num+1;
        img((x-1)*64+1:x*64,(y-1)*32+1:y*32)=img_arr(arr(i),:,:);
    end
end