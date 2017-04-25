#!/usr/local/bin/octave -qf


function countdown
  # Count down for main rocket engines
  disp (3);
  disp (2);
  disp (1);
  disp ("Blast Off!");  # Rocket leaves pad
endfunction

countdown();


figure(1)
x = -10:0.1:10
plot (x, sin (x));
hist (randn (10000, 1), 30);

#figure(1);
#n = 50;
#r = rand(n,1);
# plot(r);

#figure(2);
#m = mean(r);
#hold on;
#plot([0,n],[m,m]);
#hold off;
#title('Mean of Random Uniform Data');

