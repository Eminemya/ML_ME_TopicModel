function mat2txt(foldername,hdp)
%%%include shift
if(exist(foldername)==0)
    eval(['mkdir ' foldername])
else
    eval(['delete ' foldername '/*'])
end

eval(['cd ' foldername])

prec=16;
%hdp general
dlmwrite('hdp.txt', hdp.numdp);
dlmwrite('hdp.txt', hdp.numconparam, '-append');
dlmwrite('hdp.txt', hdp.dpstate, '-append','delimiter',' ');
dlmwrite('hdp.txt', hdp.ppindex-1, '-append','delimiter',' ');
dlmwrite('hdp.txt', hdp.cpindex-1, '-append','delimiter',' ');
dlmwrite('hdp.txt', hdp.ttindex-1, '-append','delimiter',' ');

%base
dlmwrite('base.txt', hdp.base.numclass);

%hh: K*W
if size(hdp.base.hh,2)==1
    %old version of initialization
    hdp.base.hh=repmat(hdp.base.hh,1,hdp.base.numclass);
end

dlmwrite('base.txt', size(hdp.base.hh,1), '-append');
dlmwrite('base.txt', hdp.base.hh',  '-append','delimiter',' ','precision', ['%.' num2str(prec) 'f']);

dlmwrite('base.txt', hdp.base.classnd,  '-append','delimiter',' ','precision', 8);

dlmwrite('base.txt', hdp.base.classqq',  '-append','delimiter',' ','precision', 8);

dlmwrite('base.txt', hdp.base.cclik,  '-append','precision', ['%.' num2str(prec) 'f'],'delimiter',' ');



if(iscell(hdp.base.ctindex))
aa=hdp.base.ctindex;
bb=zeros(hdp.numdp-1,hdp.base.numclass+1);
for i=1:hdp.base.numclass
bb(aa{i}-1,i)=bb(aa{i}-1,i)+1;
end
hdp.base.ctindex=bb;
end


dlmwrite('base.txt', [hdp.dp{1}.classnd;hdp.base.ctindex]',  '-append','delimiter',' ','precision', 8);


%{
for i=1:hdp.base.numclass
dlmwrite('base.txt', [hdp.dp{1}.classnd(i),hdp.base.ctindex{i}-2] ,  '-append','delimiter',' ');
end
%}
%dp
for i=1:hdp.numdp
if(i==1)
dlmwrite('dp.txt', hdp.dp{i}.numtable,'precision', ['%.' num2str(ceil(log(hdp.dp{i}.numtable)/log(10))) 'd']);
else
dlmwrite('dp.txt', hdp.dp{i}.numtable,  '-append');
end
dlmwrite('dp.txt', hdp.dp{i}.classnd,  '-append','delimiter',' ');
dlmwrite('dp.txt', hdp.dp{i}.alpha,  '-append','precision', ['%.' num2str(prec) 'f']);
dlmwrite('dp.txt', hdp.dp{i}.ttlik ,  '-append','precision', ['%.' num2str(prec) 'f']);
dlmwrite('dp.txt', hdp.dp{i}.numdata,  '-append');
if(i~=1)
dlmwrite('dp.txt', hdp.dp{i}.datass,  '-append','delimiter',' ');
dlmwrite('dp.txt', hdp.dp{i}.datatt-1,  '-append','delimiter',' ');
dlmwrite('dp.txt', hdp.dp{i}.tablecc-1,  '-append','delimiter',' ');
dlmwrite('dp.txt', hdp.dp{i}.tabless',  '-append','delimiter',' ');
end
end

%conparam
for i=1:hdp.numconparam
if(i==1)
dlmwrite('conparam.txt', hdp.conparam{i}.alphaa);
else
dlmwrite('conparam.txt', hdp.conparam{i}.alphaa,  '-append');
end
dlmwrite('conparam.txt', hdp.conparam{i}.alphab,  '-append');
dlmwrite('conparam.txt', hdp.conparam{i}.numdp,  '-append');
dlmwrite('conparam.txt', hdp.conparam{i}.alpha,  '-append');
dlmwrite('conparam.txt', hdp.conparam{i}.totalnd,  '-append','delimiter',' ');
dlmwrite('conparam.txt', hdp.conparam{i}.totalnt,  '-append','delimiter',' ');
end

%{
%gamln... to match c code, start from 0
papa=max(hdp.conparam{2}.totalnd);
dlmwrite('gamln.txt', papa+1,'delimiter',' ');
dlmwrite('gamln.txt', [0,gammaln(1:papa)],'precision', ['%.' num2str(prec) 'f'],'delimiter',' ','-append');
dlmwrite('gamln.txt', gammaln(hdp.dp{2}.alpha+[0:papa]),'precision', ['%.' num2str(prec) 'f'],'-append','delimiter',' ');

dlmwrite('gamln.txt', hdp.numdp,'delimiter',' ','-append');
dlmwrite('gamln.txt', [gammaln(hdp.dp{1}.alpha+(0:(hdp.numdp-1)))],'-append','delimiter',' ','precision', ['%.' num2str(prec) 'f']);
papa=floor(sum(sum(hdp.base.classqq))/2);
dlmwrite('gamln.txt', papa+1,'delimiter',' ','-append');
dlmwrite('gamln.txt', [gammaln(hdp.base.hh(1)+(0:papa))],'-append','delimiter',' ','precision', ['%.' num2str(prec) 'f']);
dlmwrite('gamln.txt', [gammaln(sum(hdp.base.hh)+(0:papa))],'-append','delimiter',' ','precision', ['%.' num2str(prec) 'f']);
%}
%gamln... to match c code, start from 0
N=10000;

%stirling number of first kind max over mjk
dlmwrite('gamln.txt', [0,gammaln(1:N)],'precision', ['%.' num2str(prec) 'f'],'delimiter',' ');
%dlmwrite('gamln.txt', [0,maxstir(N)],'precision', ['%.' num2str(prec) 'f'],'delimiter',' ');


dlmwrite('gamln.txt', gammaln(hdp.dp{2}.alpha+[0:N]),'precision', ['%.' num2str(prec) 'f'],'-append','delimiter',' ');

dlmwrite('gamln.txt', [gammaln(hdp.dp{1}.alpha+(0:N))],'-append','delimiter',' ','precision', ['%.' num2str(prec) 'f']);

%dlmwrite('gamln.txt', [gammaln(hdp.base.hh(1)+(0:N))],'-append','delimiter',' ','precision', ['%.' num2str(prec) 'f']);

if size(hdp.base.hh,2)==1
    dlmwrite('gamln.txt', [gammaln(sum(hdp.base.hh)+(0:N))],'-append','delimiter',' ','precision', ['%.' num2str(prec) 'f']);
else
    dlmwrite('gamln.txt', [gammaln(sum(hdp.base.hh(:,1))+(0:N))],'-append','delimiter',' ','precision', ['%.' num2str(prec) 'f']);
end

cd ..
end
