#!/usr/local/bin/octave -qf

PVset = 0.5;            % set point for process variable

steps = 100;          % time periods/steps to simulate

PV = 0;               % process variable (time series)
error = 0;            % error in PV (time series)
der = 0;              % derivative of error (time series)

Ku = 1;
Tu = 2;

Kp = Ku*.2;
Ki = 2*Kp/Tu;
Kd = Kp*Tu/3;

for k=2:steps
    % calculate error
    error(end+1) = PVset-PV(end);
    % P term
    delta = Kp*error(end);
    % I term
    delta = Ki*sum(error) + delta;
    % D term
        % instantaneous derivative time series
    der = error(2:end)-error(1:end-1);
        % average derivative over x periods
    per = 4;
    if k >= per+1
        avgDer = mean(der(end-(per-1):end));
        delta = Kd*avgDer+delta;
    end
    % limit PID controller output to -1 -> 1
    if abs(delta) > 1
        delta = sign(delta);
    end
    % simulate process behaviour
    p = 5;
    PV(k+1) = (p-1)/p*PV(k-1) + 1/p*delta;
end

figure
hold on
plot((0:steps), PV)
plot((1:steps), error, 'r')
