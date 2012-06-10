%load 400_nips
load nip_train
name={'gibb1','gibb01','gibb10'};
name={'hoho','pu_bar22_0_0c'};%100
%name={'pu_bar22_-1_0c'};%5
%name={'dr1_5_1'};%10
%name={'me_10_dndb'};%50
name={'nipmn','nipnip'};%nips
name={'out'};
for i=1:1
eval(['load ' name{i}])
%most clean
score1=hdp.base.cclik(1:end-1)./hdp.base.classnd(1:end-1);
[a1,b1]=sort(score1,'descend');
for ii=b1
dlmwrite(['me_' num2str(i) '_topic'],['>> topic ', num2str(ii), ': (', num2str(hdp.base.classnd(ii)),')  ' num2str(score1(ii)) '\\'],'delimiter','','-append');
tmp=find(hdp.base.classqq(:,ii)>mean(hdp.base.classqq(find(hdp.base.classqq(:,ii)),ii)));
[aa,bb]=sort(hdp.base.classqq(tmp,ii),'descend');
dlmwrite(['me_' num2str(i) '_topic'],[wordd(tmp(bb(1:20)))' '\\'],'delimiter','','-append')
end
end
%{
%most sharable
score2=hdp.dp{1}.classnd;
[a1,b1]=sort(score2,'descend');
for ii=b1(1:hdp.base.numclass)
dlmwrite(['mee_' num2str(i) '_topic'],['>> topic ', num2str(ii), ': (', num2str(hdp.base.classnd(ii)),')  ' num2str(score2(ii))],'delimiter','','-append');
tmp=find(hdp.base.classqq(:,ii)>mean(hdp.base.classqq(find(hdp.base.classqq(:,ii)),ii)));
[aa,bb]=sort(hdp.base.classqq(tmp,ii),'descend');
dlmwrite(['mee_' num2str(i) '_topic'],wordd(tmp(bb))','delimiter','','-append')
end
%}

