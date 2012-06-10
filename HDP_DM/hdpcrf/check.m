function y=check(hdp)
%datatt
y=0;
for i=1:hdp.numdp-1
for ii=1:hdp.dp{i+1}.numtable
y=y+abs(sum(hdp.dp{i+1}.datatt==ii)-hdp.dp{i+1}.classnd(ii));
end
if(y~=0)
disp([i,y])
break
end
end

%tabless
tmps=zeros(1,hdp.numdp);
for i=2:hdp.numdp
tmps(i)=sum(abs(sum(hdp.dp{i}.tabless)-hdp.dp{i}.classnd));
end
if(sum(abs(tmps))>0.0001)
disp(find(tmps~=0))
end

%ttlik
tmps=zeros(1,hdp.numdp);
ttk=zeros(1,hdp.numdp);
for i=1:hdp.numdp
tmps(i)=hdp.dp{i}.ttlik-c_hdp_ttlik(hdp.dp{i});
ttk(i)=hdp.dp{i}.ttlik;
end
if(max(abs(tmps))>0.0001)
[aa,bb]=max(abs(tmps))
end
%cclik
tmps2=hdp.base.cclik(1:hdp.base.numclass)-c_hdp_cclik(hdp);
if(max(abs(tmps2))>0.001)
tmps2
end
cck=sum(hdp.base.cclik);
%%ctindex
tt=cell(1,hdp.base.numclass);
start=1;
if(isfield(hdp.dp{2},'numjunk'))
start=2;
end
for i=2:hdp.numdp
for ii=start:hdp.dp{i}.numtable
tt{hdp.dp{i}.tablecc(ii)}=[tt{hdp.dp{i}.tablecc(ii)},i];
end
end
aa=0;

for i=1:hdp.base.numclass
if(iscell(hdp.base.ctindex))
aa=aa+sum(abs(sort(hdp.base.ctindex{i},'ascend')-sort(tt{i},'ascend')));
else
www=[];
for ii=find(hdp.base.ctindex(:,i))'
www=[www,ii*ones(1,hdp.base.ctindex(ii,i))];
end
aa=aa+sum(abs(1+www-sort(tt{i},'ascend')));
end
if(aa~=0)
[i,aa]
%return
end
aa=0;
end
%dp_1

aa=0;
for i=1:hdp.base.numclass
if(iscell(hdp.base.ctindex))
aa=aa+length(hdp.base.ctindex{i})-hdp.dp{1}.classnd(i);
else
aa=aa+sum(hdp.base.ctindex(:,i))-hdp.dp{1}.classnd(i);
end
if(aa~=0)
[i,aa]
%return
end
aa=0;
end

%%classqq
ttt=zeros(size(hdp.base.classqq));
for i=2:hdp.numdp
for ii=1:hdp.dp{i}.numtable
ttt(:,hdp.dp{i}.tablecc(ii))=ttt(:,hdp.dp{i}.tablecc(ii))+hdp.dp{i}.tabless(:,ii);
end
end
aa=sum(sum(abs(ttt-hdp.base.classqq)));
if(aa~=0)
aa
end
%aa=find(hdp.base.classnd==0);
aa=hdp.dp{1}.numtable-sum(hdp.dp{1}.classnd);
if(aa~=0)
aa
end
ll=hdp.base.classnd-sum(hdp.base.classqq);
if(sum(ll~=0)>1)
find(ll~=0)
end
end
