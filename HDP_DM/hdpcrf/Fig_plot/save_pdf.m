function save_pdf(h,name)

% make it tight
AX = get(h, 'CurrentAxes');
ti = get(AX,'TightInset');
set(AX,'Position',[ti(1) ti(2) 1-ti(3)-ti(1) 1-ti(4)-ti(2)]);

% adjust the papersize
set(AX,'units','centimeters');
pos = get(AX,'Position');
ti = get(AX,'TightInset');
set(h, 'PaperUnits','centimeters');
set(h, 'PaperSize', [pos(3)+ti(1)+ti(3) pos(4)+ti(2)+ti(4)]);
set(h, 'PaperPositionMode', 'manual');
set(h, 'PaperPosition',[0 0  pos(3)+ti(1)+ti(3) pos(4)+ti(2)+ti(4)]);

set(h, 'renderer', 'painters');
%pause;
saveas(h,[name '.eps'],'eps2c');
%saveas(h,[name '.pdf']);
close
