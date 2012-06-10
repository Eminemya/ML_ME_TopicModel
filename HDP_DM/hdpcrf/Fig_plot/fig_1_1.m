name = 'fig1_kl'
xs=[1,10,30,50,100];
y=cell(1,2);
y{1}=[0.006, 0.015,0.014,0.006,0.008];
y{2}=[0.011, 0.008,0.011,0.016,0.018];
y{3}=[0.8928    0.5716  1.1152 0.0687  0.9827];

h=figure;
hold on;
plot(xs,y{1},'r-o','LineWidth',5)
plot(xs,y{2},'g^','LineWidth',5)
plot(xs,y{3},'b-o','LineWidth',5)


xn='K_0';
yn='Mean D_{KL}';
l={'ME-n','ME-z','GS'};
plot_pdf(h,name,xs,xn,yn,l);

