function y=plot_rd2(hdp)
N=floor(sqrt(length(hdp.base.hh)));
classqq=hdp.base.classqq(1:N^2,:);
D=classqq(:,1:end-1);

numclass=size(classqq,2)-1;
len=ceil(numclass/10);
ppp=ones(len*N,10*N,3);
nppp=ones(ceil(len*N/3),30*N,3);
for i=1:len
    %subplot(len,1,i)
    if(i==len)
        ind=((len-1)*10+1):numclass;
    else
         ind=((i-1)*10+1):(i*10);
    end
    D=classqq(:,ind);
    ppp((i-1)*N+1:i*N,1:length(ind)*N,:) = ww(1-D./(ones(N^2,1)*sum(D,1)),[N N 1 length(ind)],1-[0.05 0]);
    ii = ceil(i/3)-1;jj=mod((i-1),3);
    nppp(ii*N+1:(ii+1)*N,jj*10*N+(1:length(ind)*N),:)= ww(1-D./(ones(N^2,1)*sum(D,1)),[N N 1 length(ind)],1-[0.05 0]);     
end
figure
%imlayout(ppp,len,numclass,N);   
imlayout(nppp,ceil(len*N/3),numclass,N);   
end

function y = imlayout(w,len,numclass,N,varargin)
[v,h] = size(w(:,:,1));
image(w);
colormap gray    
hold on; 
axis equal; axis off;
shape=[N,N,len,numclass-10*(len-1)];
%col for the first rows
for i=0:shape(4)
 plot([i*shape(2)+.5 i*shape(2)+.5],[+.5 v+.5],varargin{:});
end
%col for the last rows
for i=shape(4)+1:10
 plot([i*shape(2)+.5 i*shape(2)+.5],[+.5 v-N+.5],varargin{:});
end

%all row
for j=0:shape(3),
 plot([+.5 h+.5],[j*shape(1)+.5 j*shape(1)+.5],varargin{:});
end
hold off
end

function w = ww(w,shape,s)
 w = reshape(w,shape);
 w(:) = min(s(2),max(s(1),w(:)));
 shape(end+1:4) = 1;
w = (w-s(1))/(s(2)-s(1));

v = shape(1)*shape(3);
h = shape(2)*shape(4);
w = reshape(permute(w,[1 3 2 4]),[v h]);
w = w(:,:,ones(1,3));
end
