MU = [0.5,2.5;-1 0];
SIGMA = cat(3,[0.1505,0.0113;0.0113,0.2518],[0.033,0;0,0.033]);
p = [.5,.5];
obj = gmdistribution(MU,SIGMA,p);
y = random(obj,500);
xlim=([-1.5 2]);
ylim=([-0.5 4]);
axis tight equal
plot(y(:,1),y(:,2),'r.')
title('2d-Gaussian Samples from B0')