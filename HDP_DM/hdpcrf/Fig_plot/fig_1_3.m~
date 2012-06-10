addpath('../../Oldtest')
name = 'fig1_pl'
xs=[1,10,30,50,100];
y=cell(1,3);
%gmn
y{1}=zeros(1,5);
for i =1:5
eval(['load ../../Oldtest/k_gmn/k_gmn' num2str(xs(i))])
y{1}(i)=prelik(2);
end
%gg
y{2}=zeros(1,5);
for i =1:5
eval(['load ../../Oldtest/k_gg/k_gg' num2str(xs(i))])
y{2}(i)=prelik(1);
end
%gmn
%gmn
y{3}=zeros(1,5);
for i =1:5
eval(['load ../../Oldtest/k_gmt/k_gmt' num2str(xs(i))])
y{3}(i)=prelik(2);
end

h=figure;
hold on;
xs=[1,10,30,50,100];
plot(xs,y{1}/156156,'r-o','LineWidth',5)
plot(xs,y{3}/156156,'g-o','LineWidth',5)
plot(xs,y{2}/156156,'b-o','LineWidth',5)

xn='K_0';
yn='log P(x^{test})/# token';
l={'ME-n','ME-z','GS'};
plot_pdf(h,name,xs,xn,yn,l);

