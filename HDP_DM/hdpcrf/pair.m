function y=pair(ns,lams,step)

y=psi(lams+ns)-psi(lams);
%y(1)>y(2)

while y(1)<=y(2)

lams(1)=lams(1)-step;
lams(2)=lams(2)+step;
y=psi(lams+ns)-psi(lams);
end

%one step back
y=lams-[-step,step];

end
