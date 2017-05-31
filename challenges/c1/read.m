function img=read(path)
    img=imread(path);
    img=rgb2gray(img);
    img=adjust(img,200);
    
    rows=read_rows(img);
    for i=1:length(rows)
        cols=read_cols(img(rows(i,1):rows(i,2),:));
        for j=1:length(cols)
            
        end
    end
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