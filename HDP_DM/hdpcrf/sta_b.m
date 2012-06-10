mji=zeros(1,hdp.numdp-1);
for i=2:hdp.numdp
mji(i-1)=sum(hdp.dp{i}.classnd~=0);
end
mean(mji)

count=hdp.base.numclass;
for i=1:hdp.base.numclass
count(i)=length(find(hdp.base.classqq(:,i)>mean(hdp.base.classqq(find(hdp.base.classqq(:,i)),i))));
end

tmp2=sum(hdp.base.classqq);
figure;
subplot(3,1,1)
plot(tmp2)
xlabel('class index')
ylabel('num words')
subplot(3,1,2)
plot(count)
xlabel('class index')
ylabel('num words above mean freq')
subplot(3,1,3)
tmp=c_hdp_cclik(hdp);
plot(tmp./tmp2(1:end-1))
xlabel('class index')
ylabel('Likelihood per word')
FF(1,hdp)
