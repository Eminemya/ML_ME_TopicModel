mji=zeros(1,hdp.numdp-1);
mmm=zeros(1,hdp.numdp-1);
m=zeros(1,hdp.numdp-1);
for i=2:hdp.numdp
mji(i-1)=hdp.dp{i}.numtable;
mmm(i-1)=max(hdp.dp{i}.classnd);
m(i-1)=max(hdp.dp{i}.numdata);
end

count=hdp.base.numclass;
for i=1:hdp.base.numclass
count(i)=length(find(hdp.base.classqq(:,i)>mean(hdp.base.classqq(find(hdp.base.classqq(:,i)),i))));
end
%{
figure;
subplot(3,1,1)
plot(hdp.base.classnd)
xlabel('class index')
ylabel('num words')
subplot(3,1,2)
plot(count)
xlabel('class index')
ylabel('num words above mean freq')
subplot(3,1,3)
plot(hdp.base.cclik(1:end-1)./hdp.base.classnd(1:end-1))
xlabel('class index')
ylabel('Likelihood per word')
%}
disp([mean(mji),mean(mmm),mean(count),mean(hdp.base.cclik(1:end-1)./hdp.base.classnd(1:end-1))])
FF(1,hdp)

