function hdp = c_hdp_crf2beta(hdp)

load func
hdp.func=aa;
%base
hdp.base=rmfield(hdp.base, 'cclik');
hdp.base=rmfield(hdp.base, 'classnd');
hdp.base=rmfield(hdp.base, 'ctindex');

%dp
sss=size(hdp.dp{1}.classnd);
%first
hdp.dp{1}=rmfield(hdp.dp{1}, 'numtable');
hdp.dp{1}=rmfield(hdp.dp{1}, 'ttlik');
hdp.dp{1}.datacc=[];
hdp.dp{1}.datass=[];
hdp.dp{1}.classnt=ones(sss);
hdp.dp{1}.beta=1./ones(sss);

%rest
for i=2:hdp.numdp

tmp=hdp.dp{i}.classnd;
hdp.dp{i}.classnd=zeros(sss);
hdp.dp{i}.classnd(hdp.dp{i}.tablecc(1:end-1))=tmp(1:end-1);
hdp.dp{i}.classnt=zeros(sss);
hdp.dp{i}.classnt(hdp.dp{i}.tablecc(1:end-1))=1;
tmp=hdp.dp{i}.datatt;
hdp.dp{i}.datacc=hdp.dp{i}.datatt;
for ii=1:hdp.dp{i}.numtable
hdp.dp{i}.datacc(tmp==ii)=hdp.dp{i}.tablecc(ii);
end
hdp.dp{i}.beta=(1/sss(2))*ones(sss);
hdp.dp{i}=rmfield(hdp.dp{i}, 'numtable');
hdp.dp{i}=rmfield(hdp.dp{i}, 'tabless');
hdp.dp{i}=rmfield(hdp.dp{i}, 'ttlik');
hdp.dp{i}=rmfield(hdp.dp{i}, 'tablecc');
hdp.dp{i}=rmfield(hdp.dp{i}, 'datatt');
end
