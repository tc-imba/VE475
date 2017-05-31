global img_arr;
img_arr=read('c1.1.images/img26.jpg');
img_arr=[img_arr;read('c1.1.images/img31.jpg')];
img_arr=[img_arr;read('c1.1.images/img33.jpg')];
img_arr=[img_arr;read('c1.1.images/img35.jpg')];
img_arr=[img_arr;read('c1.1.images/img37.jpg')];

global black_arr;
black_arr=zeros(length(img_arr),5);

for i=1:length(img_arr)
    black_arr(i,1)=sum(sum(img_arr(i,:,:)==0));
    black_arr(i,2)=sum(sum(img_arr(i,1:32,:)==0));
    black_arr(i,3)=sum(sum(img_arr(i,33:64,:)==0));
    black_arr(i,4)=sum(sum(img_arr(i,:,1:16)==0));
    black_arr(i,5)=sum(sum(img_arr(i,:,17:32)==0));
end

type_num=0;
global type_arr type_standard;
type_arr=zeros(1,length(img_arr));
type_standard=[];
for i=1:length(img_arr)
    type=0;
    for j=1:length(type_standard)
        if black_similar(i,type_standard(j))
            type=j;
            break;
        end
    end
    if type==0
        type_standard=[type_standard;i];
        type=length(type_standard);
    end
    type_arr(i)=type;
end

figure(1);
imshow(combine(type_standard,50));
axis on;
axis ij;
set(gca,'xtick',-16:32:1600-16);
set(gca,'xticklabel',0:50);
set(gca,'ytick',-32:64:64*6-32);
set(gca,'yticklabel',-50:50:200);
grid on;

delete('sorted/*.bmp')
for i=1:length(type_standard)
    imwrite(combine(find(type_arr==i),25),['sorted/' num2str(i) '.bmp']);
end

function flag=black_similar(a,b)
    global black_arr;
	if abs(black_arr(a,1)-black_arr(b,1))>=5
        flag=false;
        return;
	end
    global img_arr;
    img1=zeros(64,32);
    img1(:,:)=img_arr(a,:,:);
    img2=zeros(64,32);
    img2(:,:)=img_arr(b,:,:);
    r=corr2(img1,img2);
    flag=r>=0.8;
end


