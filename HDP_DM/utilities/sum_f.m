function y=sum_f(hdp)
y=0;
for i=2:hdp.numdp
y=y+c_hdp_ttlik(hdp.dp{i});
end

for i=2:hdp.numdp
    tmp=hdp.dp{i}.classnt;
    tmp(tmp~=0)=tmp(tmp~=0)-1;
    hdp.dp{1}.classnd=hdp.dp{1}.classnd-tmp;
end

y=y+sum(c_hdp_cclik(hdp))+c_hdp_ttlik(hdp.dp{1});
end
