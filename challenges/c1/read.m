function img_arr=read(path)
    img=imread(path);
    img=rgb2gray(img);
    img=adjust(img,200);
    %imshow(img);
    width=32;
    height=64;
    block_data=zeros(0,4);
    num=0;
    rows=read_rows(img);
    for i=1:length(rows)
        cols=read_cols(img(rows(i,1):rows(i,2),:));
        for j=1:length(cols)
            num=num+1;
            block_data(num,:)=[rows(i,1),rows(i,2),cols(j,1),cols(j,2)];
        end
    end
    img_arr=zeros(length(block_data),height,width);
    for i=1:num
        img_arr(i,:,:)=crop(img(block_data(i,1):block_data(i,2),block_data(i,3):block_data(i,4)),height,width);
    end
end

function img=crop(block,height,width)
    img=block;
    s=size(img);
    if s(1)>height||s(2)>width
        display('error');
    end
    if s(1)<height
        fill=height-s(1);
        a=floor(fill/2);b=fill-a;
        img=[255.*ones(a,s(2)); img; 255.*ones(b,s(2))];
    end
    s=size(img);
    if s(2)<width
        fill=width-s(2);
        a=floor(fill/2);b=fill-a;
        img=[255.*ones(s(1),a), img, 255.*ones(s(1),b)];
    end
    %imshow(img);
end

function rows=read_rows(img)
    rows=[];
    row=1;row_start=1;
    blank_flag=true;
    for i=1:length(img)
        black=sum(img(i,:)~=255);
        if black==0
            if ~blank_flag
                rows=[rows;row_start,i-1];
                blank_flag=true;
            end
            continue;
        end
        if blank_flag
            row_start=i;
            blank_flag=false;
        end
    end
end

function cols=read_cols(row)
    cols=[];
    col=1;col_start=1;
    blank_flag=true;
    for i=1:length(row(1,:))
        black=sum(row(:,i)~=255);
        if black==0
            if ~blank_flag
                cols=[cols;col_start,i-1];
                blank_flag=true;
            end
            continue;
        end
        if blank_flag
            col_start=i;
            blank_flag=false;
        end
    end
end

function img=adjust(img,threshold)
    img(img>threshold)=255;
    img(img<=threshold)=0;
end