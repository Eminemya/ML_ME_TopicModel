function y = c_hdp_ttlik(dp)
alpha=dp.alpha;
y=gammaln(alpha)-gammaln(alpha+sum(dp.classnd));
ind=(dp.classnd~=0);
y=y+sum(gammaln(dp.classnd(ind)))+sum(ind)*log(alpha);
if(dp.numdata~=0)
ind=sum(dp.tabless,2);
y=y+sum(gammaln(ind(find(ind))+1))-sum(sum(gammaln(dp.tabless(find(dp.tabless))+1)));
end
end
