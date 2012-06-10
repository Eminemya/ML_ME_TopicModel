% Gibbs:
nn_gib=[38.4    39.2    44.4   123.0    27.0    32.4;
    62.8    55.2    64.8   223.2    42.4    26.8;
    64.0    87.6   113.0   461.2    43.0    31.0;
    45.8    50.8    53.0   201.2    19.6    19.6];

% ME:

nn_me= [ 18.4    20.4     19.0     30.8     15.8   10.6;
     21.0    23.6     24.8     34    18.8    11.2;
     31.8     32.0    29.6    41.0     22.8     15.8;
     22.6    25.6     25.8     33.8     22.4     19.0];

nn={'NG','KOS','NIPS','Reu'};
mm={'k','l'};
for j=1:2
for i=1:4
h=figure;
hold on;
name = ['fig4n_' nn{i}  '_' mm{j}]
if j==1
%varying K
y1=nn_me(i,1:3);
y2=nn_gib(i,1:3);
xs=[40,80,120];
xn='K_0';
else
%varying lambda
y1=nn_me(i,[4,1,5:6]);
y2=nn_gib(i,[4,1,5:6]);
xs=[0.1,1,3,5];
xn='\lambda';
end

plot(xs,y1,'r-o','LineWidth',5)
plot(xs,y2,'b-o','LineWidth',5)
plot_pdf(h,name,xs,xn,'','','',[nn_me(i,:),nn_gib(i,:)]);
end
end
