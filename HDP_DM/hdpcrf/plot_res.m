function y=plot_res(dp,N)   
figure
subplot(1,2,1)
colormap gray
D=dat2ma(dp.datass,N^2,1);
imlayout(1-D./(ones(N^2,1)*sum(D,1)),[N N 1 1],1-[0.2 0]);
subplot(1,2,2)
colormap gray
D=dp.tabless(:,1:end-1);
imlayout(1-D./(ones(N^2,1)*sum(D,1)),[N N 1 dp.numtable],1-[0.02 0]);
end

function a=dat2ma(dat,imrow,imcol)
a=zeros(imrow,imcol);
for i=1:imrow*imcol
a(i)=length(find(dat==i));
end
end


function handle = imlayout(w,shape,s,varargin);
if nargin<2,
 shape = [size(w,1) size(w,2) size(w,3) size(w,4)];
 s = [min(w(:)) max(w(:))];
elseif nargin<3,
 w = reshape(w,shape);
 s = [min(w(:)) max(w(:))];
else
 w = reshape(w,shape);
 w(:) = min(s(2),max(s(1),w(:)));
end

if length(shape)<4,
 shape(end+1:4) = 1;
end
w = (w-s(1))/(s(2)-s(1));

v = shape(1)*shape(3);
h = shape(2)*shape(4);
w = reshape(permute(w,[1 3 2 4]),[v h]);
w = w(:,:,ones(1,3));
handle = image(w);
hold on; axis equal; axis off;
for i=0:shape(4),
 plot([i*shape(2)+.5 i*shape(2)+.5],[+.5 v+.5],varargin{:});
end;
for j=0:shape(3),
 plot([+.5 h+.5],[j*shape(1)+.5 j*shape(1)+.5],varargin{:});
end;
hold off
end
