
% Define the sample points, x, and corresponding sample values, y.

x = 0:pi/4:2*pi; 
y = sin(x);

% Define the query points to be a finer sampling over the range of x.

xq = 0:pi/16:2*pi;

% Interpolate the function at the query points and plot the result.

figure
vq1 = interp1(x,y,xq);

plot(x,y,'o',xq,vq1,':.');
xlim([0 2*pi]);
xlabel('samples');
ylabel('radians');
title('(Func) Linear Interpolation');

x
y
xq

table_data = table(x,y)

% read in x,y via csv
cxy = csvread('interp.csv');
xx = cxy(:,1); % all rows of column 1 -- which are the x values
yy = cxy(:,2); % all rows of column 2 -- which are the y values

% pick breakpoints
xxq = 0:pi/16:2*pi;

% output linterp table: [start, stop, slope]
figure
vvq1 = interp1(xx,yy,xxq);

plot(xx,yy,'o',xxq,vvq1,':.');
xlim([0 2*pi]);
xlabel('samples-csv');
ylabel('radians-csv');
title('(Csv) Linear Interpolation');

table_data2 = table(xx,yy) %% unknown what the heck this is

