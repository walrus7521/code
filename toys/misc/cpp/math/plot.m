#!/usr/local/bin/octave -qf

%* Plot the initial and final states.
load x.txt; load a.txt; load tplot.txt; load aplot.txt;
figure(1); clf;  % Clear figure 1 window and bring forward
plot(x,aplot(:,1),'-',x,a,'--');
legend('Initial','Final');
xlabel('x');  ylabel('a(x,t)');
pause(1);    % Pause 1 second between plots
%* Plot the wave amplitude versus position and time
figure(2); clf;  % Clear figure 2 window and bring forward
mesh(tplot,x,aplot);
ylabel('Position');  xlabel('Time'); zlabel('Amplitude');
view([-70 50]);  % Better view from this angle

