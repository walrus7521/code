Kp = 1;
Ki = 0;   % No integrator
Kd = 3;
Tf = 0.5;
C = pid(Kp,Ki,Kd,Tf)

