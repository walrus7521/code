
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
title('(Default) Linear Interpolation');

x
y
xq

table_data = table(x,y)

% read in x,y via csv
% pick breakpoints
% output linterp structure
