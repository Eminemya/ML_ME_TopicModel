name = 'fig2_npl';
y1=[-6.9556, -6.9552,-6.9564,-6.9549,-6.9553]*1e5;
y2=[-6.9520   -6.9519  -6.9511 -6.9521  -6.9556]*1e5;
xs=[1,10,30,50,100];
xn='K_0';
yn='log P(x^{test})/# token';
tn='NoisyBar';
l={'ME-n','GS'};

h=figure;
hold on;
xs=[1,10,30,50,100];
plot(xs,y1/156156,'r-o','LineWidth',5)
plot(xs,y2/156156,'b-o','LineWidth',5)
plot_pdf(h,name,xs,xn,yn,l,tn,[-4.5,-4]);

