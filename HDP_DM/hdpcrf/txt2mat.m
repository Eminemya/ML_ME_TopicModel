function hdp=txt2mat(loc,fff)
eval(['cd ' loc])
fid = fopen(['hdp' fff '.txt'],'rt'); 
  nextline = fgetl(fid);     
  hdp.numdp=str2num(nextline);
  nextline = fgetl(fid);     
  hdp.numconparam=str2num(nextline);
  nextline = fgetl(fid);     
  hdp.dpstate=str2num(nextline);
  nextline = fgetl(fid);     
  hdp.ppindex=str2num(nextline);
  hdp.ppindex=hdp.ppindex+1;
  nextline = fgetl(fid);     
  hdp.cpindex=str2num(nextline);
  hdp.cpindex=hdp.cpindex+1;
  nextline = fgetl(fid);     
  hdp.ttindex=str2num(nextline);
    hdp.ttindex=  hdp.ttindex+1;


fid = fopen(['base' fff '.txt'],'rt'); 
  nextline = fgetl(fid);     
  
  numclass=str2num(nextline);
  hdp.base.numclass=numclass;
  nextline = fgetl(fid);     
  numword=str2num(nextline);

  hdp.base.hh=zeros(numword,numclass);
  for i=1:numclass  
  nextline = fgetl(fid);     
  hdp.base.hh(:,i)=str2num(nextline);    
  end

  nextline = fgetl(fid);     
  hdp.base.classnd=str2num(nextline);
  hdp.base.classqq=zeros(numword,hdp.base.numclass+1);
  for i=1:hdp.base.numclass+1
  nextline = fgetl(fid);     
  hdp.base.classqq(:,i)=str2num(nextline)';
  end  
  hdp.base.classqq(:,end)=0;
  nextline = fgetl(fid);     
  hdp.base.cclik=str2num(nextline);

  hdp.base.ctindex=cell(1,hdp.base.numclass+1);
  for i=1:hdp.base.numclass
  nextline = fgetl(fid);     
  tmp=str2num(nextline);
  %tmp=tmp(find(tmp));
  %hdp.base.ctindex{i}=tmp(2:end);
  tmpp=[];
  for ii=find(tmp(2:end)~=0)
    tmpp=[tmpp,ones(1,tmp(ii+1))*ii+1];
  end
  hdp.base.ctindex{i}=tmpp;
  end

fid = fopen(['dp' fff '.txt'],'rt'); 
%dp
hdp.dp=cell(1,hdp.numdp);

for i=1:hdp.numdp
  nextline = fgetl(fid);     
hdp.dp{i}.numtable=str2num(nextline);
  nextline = fgetl(fid);     
hdp.dp{i}.classnd=str2num(nextline);
  nextline = fgetl(fid);     
hdp.dp{i}.alpha=str2num(nextline);
  nextline = fgetl(fid);     
hdp.dp{i}.ttlik=str2num(nextline);
  nextline = fgetl(fid);     
hdp.dp{i}.numdata=str2num(nextline);

if(i~=1)
  nextline = fgetl(fid);     
hdp.dp{i}.datass=str2num(nextline);
  nextline = fgetl(fid);     
hdp.dp{i}.datatt=str2num(nextline);
hdp.dp{i}.datatt=hdp.dp{i}.datatt+1;
  nextline = fgetl(fid);     
hdp.dp{i}.tablecc=str2num(nextline);
hdp.dp{i}.tablecc=hdp.dp{i}.tablecc+1;
hdp.dp{i}.tabless=zeros(numword,hdp.dp{i}.numtable+1);
for j=1:hdp.dp{i}.numtable+1
  nextline = fgetl(fid);     
hdp.dp{i}.tabless(:,j)=str2num(nextline)';
end
end
end
hdp.dp{1}.numdata=0;

fid = fopen(['conparam' fff '.txt'],'rt');  
%conparam
for i=1:hdp.numconparam
  nextline = fgetl(fid);     
hdp.conparam{i}.alphaa=str2num(nextline);
  nextline = fgetl(fid);     
hdp.conparam{i}.alphab=str2num(nextline);
  nextline = fgetl(fid);     
hdp.conparam{i}.numdp=str2num(nextline);
  nextline = fgetl(fid);     
hdp.conparam{i}.alpha=str2num(nextline);
  nextline = fgetl(fid);     
hdp.conparam{i}.totalnd=str2num(nextline);
  nextline = fgetl(fid);     
hdp.conparam{i}.totalnt=str2num(nextline);
end

cd ..
end
