#!/usr/local/bin/octave -qf

x=(1:20)';
N=1:5;
for n=N
 y(:,n)=x.**n;
endfor
%
semilogy(x,y)
%
K=rainbow(length(N));
set(gca,'colororder',K)
xlabel('\delta \epsilon \times foo')
title('some non-sense with the standard colors still') 

