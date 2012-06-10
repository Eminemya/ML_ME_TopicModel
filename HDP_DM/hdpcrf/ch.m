function hdp=ch(hdp,val,option)

switch(option)
case 0
    %alpha
    for i=2:length(hdp.dp)
        hdp.dp{i}.alpha=val;
        hdp.dp{i}.ttlik = c_hdp_ttlik(hdp.dp{i});
    end
case 1
    hdp.dp{1}.alpha=val;
    hdp.dp{1}.ttlik=c_hdp_ttlik(hdp.dp{1});
case 2
    hdp.base.hh=ones(size(hdp.base.hh))*val;
    hdp.base.cclik=[c_hdp_cclik(hdp),0];
end

end
