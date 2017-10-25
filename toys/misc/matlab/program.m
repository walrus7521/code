
lambda % include lambda.m

cube(2) % use function inside lambda.m

% user defined function function
function xyout=funplot(Fun, a, b)
% funplot makes a plot of the function Fun which is passed in
% when funplot is called in the domain [a, b].
% 
% Input arguments are:
% Fun: Function handle of the function to be plotted.
% a: the first point of the domain
% b: the last point of the domain
%
% Output argument is:
% xyout: The values of x and y at x=a, x=(a+b)/2 and x=b
% listed in A 3 by 2 matrix.

    x = linspace(a,b,100);
    y = Fun(x);
    xyout(1,1) = a; xyout(2,1) = (a+b)/2; xyout(3,1) = b;
    xyout(1,1) = y(1);
    xyout(2,2) = Fun((a+b)/2);
    xyout(3,2) = y(100);
    plot(x,y);
    xlabel('x'), ylabel('y');

end

% function handle
%demo = funplot(@cos,0,3);

%hcos = @cos;
%hdemo = funplot(hcos,0,3);

%function y = Fdemo(x)
%    y = exp(-0.17*x).*x.^3-2*x.^2+0.8*x-3;
%end
%ydemo = funplot(@Fdemo,0.5,4);

x = 'b';
switch (x)
    case 'a'  fprintf(1, 'dude = a\n');
    case 'b'  fprintf(1, 'dude = b\n');
    case 'c'  fprintf(1, 'dude = c\n');
    case 'd'  fprintf(1, 'dude = d\n');
    case 'e'  fprintf(1, 'dude = e\n');
    otherwise fprintf(1, 'dude, you suck %c\n', x);
end

x = 'd';
if (x == 'b')
    {
    fprintf(1, 'dude = nice\n');
    }
elseif (x == 'c')
    {
    fprintf(1, 'dude, swell\n');
    }
else
    {
    fprintf(1, 'dude, you bite %c\n', x);
    }
end

xx = 0;
for k = 1:0.1:2
    fprintf(1, 'k = %d -> %d\n', k, xx);
    xx += k;
end
fprintf(1, 'final = %d\n', xx);

yy = 9;
while (yy > 0)
    fprintf(1, 'yy = %d\n', yy);
    yy--;
    if (yy == 7) 
        continue;
        break;
    end
end


