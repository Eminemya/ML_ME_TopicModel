load real_Gib
load real_ME
len =[49608,46200,175586,63096];
nn={'NG','KOS','NIPS','Reu'};
mm={'k','l'};
for j=1:2
for i=1:4
h=figure;
hold on;
name = ['fig4pl_' nn{i}  '_' mm{j}]
if j==1
%varying K
y1=pl_me(i,1:3);
y2=pl_gib(i,1:3);
xs=[40,80,120];
xn='K_0';
else
%varying lambda
y1=pl_me(i,[4,1,5:6]);
y2=pl_gib(i,[4,1,5:6]);
xs=[0.1,1,3,5];
xn='\lambda';
end

plot(xs,y1/len(i),'r-o','LineWidth',5)
plot(xs,y2/len(i),'b-o','LineWidth',5)
if i==2&&j==1
plot_pdf(h,name,xs,xn,'',{'ME-n','GS'},'',[pl_me(i,:),pl_gib(i,:)]/len(i));
else
plot_pdf(h,name,xs,xn,'','','',[pl_me(i,:),pl_gib(i,:)]/len(i));
end
end
end
