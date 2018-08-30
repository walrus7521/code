#!/usr/local/bin/octave -qf


t = linspace (0, 10, 100);
function sprime = spring (s, t, k)
  x = s(1);
  v = s(2);
  sprime(1) = v;
  sprime(2) = -k * x;
endfunction
k = 1;
x1 = lsode (@(x, t) spring (x, t, k), [1;0], t)(:, 1);
k = 2;
x2 = lsode (@(x, t) spring (x, t, k), [1;0], t)(:, 2);
plot (t, x1, t, x2)
##legend ('x1', 'x2')
printf("hello, world\n");
