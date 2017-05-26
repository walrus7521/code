#!/usr/local/bin/octave -qf

function heat
    Ts = 38;
    To = 120;
    k = .45;
    t = 3;
    T = Ts + (To - Ts)*exp(-k*t);
    printf("final temp %f\n", T);
endfunction

function three_d
    t = 0:0.1:6*pi;
    x = sqrt(t).*sin(2*t);
    y = sqrt(t).*cos(2*t);
    z = 0.5*t;
    plot3(x,y,z,'k','linewidth',1)
    grid on
    xlabel('x'); ylabel('y'); zlabel('z')
endfunction

function do_mesh_surf
    x = -1:0.1:3;
    y = 1:0.1:4;
    [X, Y] = meshgrid(x, y);
    Z=X.*Y.^2./(X.^2+Y.^2);
    mesh(X,Y,Z)
    %surf(X,Y,Z)
    xlabel('x'); ylabel('y'); zlabel('z')
endfunction

%heat();
%three_d();
do_mesh_surf();
pause;

