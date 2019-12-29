#!/usr/bin/octave -qf

%% Create Figure with Multiple Axes Using Subplots
% This example shows how to create a figure containing multiple axes
% using the |subplot| function. The syntax, |subplot(m,n,p)|, divides the
% figure into an m-by-n grid with an axes in the pth grid location. The
% grids are numbered along each row.

% Copyright 2015 The MathWorks, Inc.


%% Create Subplots and Add Subplot Titles
% Use |subplot| to create a figure containing a 2-by-2 grid of graphs. Plot
% a sine wave in the first subplot. Then, plot three more sine waves in the
% second, third, and fourth subplots.


x = linspace(-5,5);
y1 = sin(x);
subplot(2,2,1)
plot(x,y1)
title('First subplot')

y2 = sin(2*x);
subplot(2,2,2)
plot(x,y2)
title('Second subplot')

y3 = sin(4*x);
subplot(2,2,3)
plot(x,y3)
title('Third subplot')

y4 = sin(6*x);
subplot(2,2,4)
plot(x,y4)
title('Fourth subplot')

%% Add Subplot Axis Labels
% Add subplot labels using the |xlabel| and |ylabel| functions. By default,
% |xlabel| and |ylabel| label the current axes. The current axes is
% typically the last axes created or clicked with the mouse. Reissuing the
% command, |subplot(m,n,p)|, makes the pth subplot the current axes.
%
% Make the third subplot the current axes. Then, label its _x_-axis and
% _y_-axis. 
subplot(2,2,3)
xlabel('x-axis')
ylabel('y-axis')

pause();

%% 
% Copyright 2014, The MathWorks Inc.
