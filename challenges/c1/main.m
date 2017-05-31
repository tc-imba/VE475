img_arr=read('c1.1.images/img26.jpg');
img_arr=[img_arr;read('c1.1.images/img31.jpg')];
img_arr=[img_arr;read('c1.1.images/img33.jpg')];
img_arr=[img_arr;read('c1.1.images/img35.jpg')];
img_arr=[img_arr;read('c1.1.images/img37.jpg')];

black_arr=zeros(1,length(img_arr));

for i=1:length(img_arr)
    black_arr(i)=sum(sum(img_arr(i,:,:)==0));
%     break;
end

img=zeros(640,320);
num=0;

for i=1:length(img_arr)
    if black_arr(i)==165&&num<100
        x=floor(num/10)+1;
        y=mod(num,10)+1;
        num=num+1;
        img((x-1)*64+1:x*64,(y-1)*32+1:y*32)=img_arr(i,:,:);
    end
end
    
imshow(img);

% small=zeros(0,0);
% small(:,:)=img_arr(1,:,:);
% imshow(small);