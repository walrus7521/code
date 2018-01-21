#!/usr/local/bin/octave -qf

function do_square()
    f = 10;
    overSampRate = 30;
    fs = overSampRate*f;
    ncy = 5;
    t = 0:1/fs:ncy*1/f-1/fs;
    g = sign(sin(2*pi*f*t));
    plot(t,g); title(['Square Wave f =' num2str(f), 'Hz']);
    pause();
end

function do_sine()
    f = 10;
    overSampRate = 30;
    fs = overSampRate*f;
    phase = 1/3*pi;
    ncy = 5;
    t = 0:1/fs:ncy*1/f-1/fs;
    g = sin(2*pi*f*t+phase);
    plot(t,g); title(['Sine Wave f =' num2str(f), 'Hz']);
    pause();
end

%do_sine();
%do_square();
