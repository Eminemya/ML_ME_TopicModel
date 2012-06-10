name = 'fig1_gm'
h=figure;
hold on;
y=zeros(1,5);
xs=[1,10,30,50,100];
for i =1:5
eval(['load ../../Oldtest/k_gg/kkbar_' num2str(xs(i)) '_0'])
plot(1:100,Lik2(401:500)/1567566,'g-','LineWidth',3);
plot(101:600,Lik2(501:1000)/1567566,'b-','LineWidth',3);
eval(['load ../../Oldtest/k_gmg/gmg_' num2str(xs(i)) '_0'])
plot(100:600,[Lik2(500) Likm]/1567566,'r-','LineWidth',3);
end

xn='# Iterations';
yn='log P(x^{train})/# token';
%l = {'10,000 iterations GS','+10,000 iterations GS','+ME-n+10,000 iterations GS'};
l = {'Initial GS','+GS','+ME-n+GS'};
xlabel(xn,'fontsize',25,'FontName','Times','FontWeight','bold')
ylabel(yn,'fontsize',25,'FontName','Times','FontWeight','bold')
axis square
axis tight
set(gca,'XTick',[1,180,380,580],'fontsize',15,'FontName','Times','FontWeight','bold')
set(gca,'XTickLabel',['8,000 ';'12,000';'16,000';'20,000'])
le=legend([l(:)]);
leg = findobj(le,'type','text');
set(leg,'fontsize',20,'FontName','Times','FontWeight','bold')

%save_pdf(h,name);
