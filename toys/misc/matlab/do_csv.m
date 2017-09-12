
%game1 = input('Enter game1: ');
%game2 = input('Enter game2: ');
%game3 = input('Enter game3: ');
%x = (game1 + game2 + game3) / 2;
%disp(x);
%disp('dude');
%fprintf('dude, you suck\n');
%fprintf('the avg is %-5.2f ok?\n', x);

collective = csvread('CollectiveOut.csv',6,0);
nrows = size(collective,1);

%for col = 1:3
%    for row = 1:nrows
%        g = m(row,col); fprintf('m = %d\n', g);
%    end
%end


% https://www.mathworks.com/help/matlab/ref/colon.html
y = collective(:,3); % create an array from 3rd column of matrix

%figure('Name', 'Simple plot', 'NumberTitle', y);
%hFit   = line(xfit  , yfit   );
%hE     = errorbar(xdata_m, ydata_m, ydata_s);
%hData  = line(xVdata, yVdata );
%hModel = line(xmodel, ymodel );
%hCI(1) = line(xmodel, ymodelL);
%hCI(2) = line(xmodel, ymodelU);
%grid on

time_shifted = zeros(nrows);
k_start = -5;
k_end   = 5;


y_axis_min = min(y);
y_axis_max = max(y);
x_axis_min = -5.0;
x_axis_max = +5.0;

YLim = [y_axis_min y_axis_max];
XLim = [x_axis_min x_axis_max];


figure
plot(y);
legend({'Average Position'},'northeast')
ax = gca;
ax.XGrid = 'off';
ax.YGrid = 'on';

ax.YTick             = int32(YLim(1):5:YLim(2));
ax.YLim              = YLim;
ax.XLim              = XLim;
ax.YAxisLocation     = 'origin';

xlabel('time, sec');
ylabel('position, inches');
title('Collective Position');

disp(m);
