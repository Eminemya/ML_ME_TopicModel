function y=FF(T,hdp)
y=[0,0];
%dp
for i=2:hdp.numdp
y(1)=y(1)+hdp.dp{i}.ttlik;
end
y(1)=y(1)*T;

y(2)=hdp.dp{1}.ttlik;
%class
y(2)=y(2)+sum(hdp.base.cclik(1:hdp.base.numclass));
end

