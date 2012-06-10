function hdp = c_hdp_beta2crf(hdp)
index=2:hdp.numdp;
%0) add clik to hdp
hdp.base.cclik=[c_hdp_cclik(hdp),0];
tmp=zeros(1,hdp.base.numclass+1);
%hdp.base.numword=zeros(1,hdp.base.numclass+1);
%hdp.base.ctindex=zeros(hdp.numdp-1,hdp.base.numclass+1);
hdp.base.ctindex=cell(1,hdp.base.numclass+1);
%tmp_ct=cell(1,hdp.base.numclass+1);
%hdp.base.wwindex=cell(1,hdp.base.numclass+1);
for i=1:hdp.base.numclass+1
tmp(i)=sum(hdp.base.classqq(:,i));
%hdp.base.numword(i)=sum(hdp.base.classqq(:,i)~=0);
%hdp.base.wwindex{i}=find(hdp.base.classqq(:,i)~=0);
end
hdp.base.classnd=tmp;

%1) for dps that are still beta, simply froze them
%except the first root node
beta_index=ones(1,hdp.numdp);
index=[index,1];
beta_index(index)=0;
hdp.dpstate(find(beta_index))=0;


%2) for dps that will be crf, add tabless,tablecc and datatt in additon to ttlik,numtable and type
for i=index
%no 2 tables in the restaurant serving the same dish
dishes=unique(hdp.dp{i}.datacc);
n_dishes=length(dishes);
n_words=length(hdp.base.hh);
hdp.dp{i}.datatt=zeros(size(hdp.dp{i}.datacc));
hdp.dp{i}.tablecc=zeros(1,n_dishes+1);
hdp.dp{i}.tabless=sparse(n_words,n_dishes+1);
hdp.dp{i}.numtable=n_dishes;
if(i~=1)
hdp.conparam{1}.totalnd=hdp.conparam{1}.totalnd+n_dishes-hdp.conparam{2}.totalnt(i-1);
hdp.conparam{2}.totalnt(i-1)=n_dishes;
end
for ii=1:n_dishes
tmp_ind=hdp.dp{i}.datacc==dishes(ii);
hdp.dp{i}.datatt(tmp_ind)=ii;
hdp.dp{i}.tablecc(ii)=dishes(ii);
%tmp_ct{dishes(ii)}=[tmp_ct{dishes(ii)};i];
hdp.base.ctindex{dishes(ii)}=[hdp.base.ctindex{dishes(ii)},i];
hdp.dp{i}.tabless(:,ii)=dat2ma(sparse(hdp.dp{i}.datass(tmp_ind)),n_words,1);
end
hdp.dp{i}.tabless=full(hdp.dp{i}.tabless);
ttmm=hdp.dp{i}.classnt(hdp.dp{i}.classnt~=0);
ind=find(ttmm>1);

if(~isempty(ind))
hdp.dp{1}.classnd(hdp.dp{i}.tablecc(ind))=hdp.dp{1}.classnd(hdp.dp{i}.tablecc(ind))-(ttmm(ind)-1);
%disp(hdp.dp{1}.classnd)
end
hdp.dp{i}.classnd=[hdp.dp{i}.classnd(hdp.dp{i}.classnd~=0),0];

hdp.dp{i}=rmfield(hdp.dp{i},'classnt');
hdp.dp{i}=rmfield(hdp.dp{i},'datacc');
hdp.dp{i}=rmfield(hdp.dp{i},'beta');
%{
for i=1:hdp.base.numclass
hdp.base.ctindex(1:length(tmp_ct{i}),i)=tmp_ct{i};
end
%}
hdp.dp{i}.ttlik=c_hdp_ttlik(hdp.dp{i});

end

hdp.dp{1}.numtable=hdp.conparam{1}.totalnd;
end

%bin the customers into counts 
function a=dat2ma(dat,imrow,imcol)
a=sparse(imrow,imcol);
for i=1:imrow*imcol
a(i)=length(find(dat==i));
end
end

