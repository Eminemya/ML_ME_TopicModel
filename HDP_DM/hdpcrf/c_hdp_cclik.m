function y=c_hdp_cclik(hdp)
phi0=hdp.base.hh;
num_cl=hdp.base.numclass;

if( size(phi0,2)==1)
y=ones(1,num_cl)*(gammaln(sum(phi0))-sum(gammaln(phi0)));
y=y-gammaln(sum(hdp.base.classqq(:,1:num_cl))+sum(phi0))+sum(gammaln(phi0*ones(1,num_cl)+hdp.base.classqq(:,1:num_cl)));

else

y=(gammaln(sum(phi0))-sum(gammaln(phi0)));
y=y-gammaln(sum(hdp.base.classqq(:,1:num_cl))+sum(phi0))+sum(gammaln(phi0+hdp.base.classqq(:,1:num_cl)));
end
%y=y-log(length(phi0))*hdp.base.numjunk;
end
