#!/usr/bin/octave -qf

%%#!/usr/local/bin/octave -qf
%%#!/usr/local/octave/3.8.0/bin/octave-3.8.0 -qf
%% #!/usr/bin/octave -qf

%% https://www.youtube.com/watch?v=rUgKnoiRoY0
%% http://studentdavestutorials.weebly.com/

clear all

duration = 10
dt = .1;

A = [1 dt; 0 1];
B = [dt^2/2; dt];
C = [1 0];

u = 1.5;
Q = [0; 0];
Q_estimate = Q;
QuailAccel_noise_mag = 0.05; % process noise
NinjaVision_noise_mag = 10; % measurement noise
Ez = NinjaVision_noise_mag^2;
Ex = QuailAccel_noise_mag^2 * [dt^4/4 dt^3/2; dt^3/2 dt^2];
P = Ex; % covariance

%% initialize result variables
Q_loc = []; % ACTUAL Quail flight path
vel = []; % ACTUAL Quail velocity
Q_loc_meas = []; % Quail path that the Ninja sees

figure(2);clf
figure(1);clf

for t = 0 : dt: duration
    QuailAccel_noise = QuailAccel_noise_mag * [(dt^2/2)*randn; dt*randn ];
    Q = A * Q + B * u + QuailAccel_noise;

    NinjaVision_noise = NinjaVision_noise_mag * randn;
    y = C * Q + NinjaVision_noise;
    Q_loc = [Q_loc; Q(1)];
    Q_loc_meas = [Q_loc_meas; y];
    vel = [vel; Q(2)];
    plot(0:dt:t, Q_loc, '-r.')
    plot(0:dt:t, Q_loc_meas, '-k.')
    axis([0 10 -30 80])
    hold on
    %pause
end

%% this is if we just used a running average, instead of kalman
% plot(0:dt:t, smooth(Q_loc_meas), '-g.')

%% do kalman filtering
Q_loc_estimate = [];
vel_estimate = [];
Q = [0; 0];
P_estimate = P;
P_mag_estimate = [];
predic_state = [];
predic_var = [];

for t = 1:length(Q_loc)
    Q_estimate = A * Q_estimate + B * u;
    predic_state = [predic_state; Q_estimate(1)];

    P = A * P * A' + Ex;
    predic_var = [predic_var; P];

    K = P*C'*inv(C*P*C'+Ez);

    Q_estimate = Q_estimate + K * (Q_loc_meas(t) - C * Q_estimate);

    P = (eye(2) - K*C)*P; % eye is identity matrix 2x2
    Q_loc_estimate = [Q_loc_estimate; Q_estimate(1)];
    vel_estimate = [vel_estimate; Q_estimate(2)];
    P_mag_estimate = [P_mag_estimate; P(1)];

end

% plot the kalman results
figure(2);
tt = 0 : dt : duration;
plot(tt, Q_loc, '-r.', tt, Q_loc_meas, '-k.', tt, Q_loc_estimate, '-g.');
axis([0 10 -30 80])

% plot the evolution of the distributions
figure(3);clf
for T = 1:length(Q_loc_estimate)
clf

    x = Q_loc_estimate(T)-5:.01:Q_loc_estimate(T)+5;
    
    hold on
    mu = predic_state(T);
    sigma = predic_var(T);
    y = normpdf(x, mu, sigma); % pdf
    y = y/(max(y));
    hl = line(x, y, 'Color', 'm');

    %data measured by the ninja
    mu = Q_loc_meas(T);
    sigma = NinjaVision_noise_mag;
    y = normpdf(x, mu, sigma); % pdf
    y = y/(max(y));
    hl = line(x, y, 'Color', 'k');

    % combined position estimate
    mu = Q_loc_estimate(T); % mean
    sigma = P_mag_estimate(T);
    y = normpdf(x, mu, sigma); % pdf
    y = y/(max(y));
    hl = line(x, y, 'Color', 'g');
    axis([Q_loc_estimate(T)-5 Q_loc_estimate(T)+5 0 1]);

    % actual postion of the quail
    plot(Q_loc(T));
    ylim = get(gca,'ylim');
    line([Q_loc(T); Q_loc(T)], ylim.','linewidth',2,'color','b');
    legend('state predicted', 'measurement', 'state estimate', 'actual Quail position');
    %pause;

end

pause;

