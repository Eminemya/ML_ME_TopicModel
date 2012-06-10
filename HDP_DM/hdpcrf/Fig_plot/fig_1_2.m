name = 'fig1_nt'

h=figure;
hold on;
xs=[1,10,30,50,100];
plot(xs,50*ones(1,5),'r-o','LineWidth',5)
plot(xs,50*ones(1,5),'g^','LineWidth',5)
plot(xs,[57,54,50.2,51.8,53.4],'b-o','LineWidth',5)

xn='K_0';
yn='# Topics';
l={'ME-n','ME-z','GS'};
plot_pdf(h,name,xs,xn,yn,l);

