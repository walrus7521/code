#!/usr/bin/octave -qf

%!demo
%! ## Moving average & Savitzky-Golay
x     = linspace (0, 4*pi, 150);
y     = sin (x) + 1*(rand (1, length (x)) - 0.5);
y_ma  = smooth (y, 21, 'moving');
y_sg  = smooth (y, 21, 'sgolay', 2);
y_sg2 = smooth (y, 51, 'sgolay', 2);
figure
plot (x,y, x,y_ma)
legend('Original', 'Moving Average (span 21)')
%plot (x,y, x,y_ma, x,y_sg, x,y_sg2)
%legend('Original', 'Moving Average (span 21)', 'Savitzky-Golay (span 21, degree 2)', 'Savitzky-Golay (span 51, degree 2)')
pause;
