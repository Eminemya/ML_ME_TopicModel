name = 'fig2_nbpl';
y1=[-6.2932   -6.2834  -6.2871 -6.2935  -6.2868]*1e5;
y2=[-6.2972, -6.4254,-6.4117,-6.3484,-6.2848]*1e5;
xs=[1,10,30,50,100];
xn='K_0';
yn='log P(x^{test})/# token';
tn='BurstyBar';
l={'ME-n','GS'};

h=figure;
hold on;
xs=[1,10,30,50,100];
plot(xs,y1/156156,'r-o','LineWidth',5)
plot(xs,y2/156156,'b-o','LineWidth',5)
plot_pdf(h,name,xs,xn,yn,l,tn,[-4.5,-4]);

