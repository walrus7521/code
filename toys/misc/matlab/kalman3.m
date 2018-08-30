#!/usr/bin/octave -qf

function [states, realstates] = filter ()
    global delta
    clg

    % initialise

    realstate = initstate;
    state = initstate;
    states = [];
    realstates = [];
    zks = [];

    sdgyro = 0.5;
    sdaccel = 0.2;
    Rk = [sdgyro^2 0; 0 sdaccel^2]; % Measurement noise variance. Dimension n x n
    
    Qk = [0.2 * delta 0.2 0.1];
    Qk = Qk' * Qk; % State noise variance: Dimension m x m

    Pk = Qk; % Dimension: m x m

    for k = 1:1000	

        % Correction
        Hk = H(state);
        Vk  = V(state);
        zk = z(realstate);
        I = identity;

        % http://omni.isr.ist.utl.pt/~mir/pub/kalman.pdf page 33

        Kk = Pk * Hk' * inv(Hk * Pk * Hk' + Vk * Rk * Vk');
        Pk = (I - Kk * Hk) * Pk; % use the same Hk as above
        state = state + Kk * (zk - h(state));


     % Save result. This is da shit we want
        savestate = state;
        states = [states savestate];
        realstates = [realstates realstate];
        zks = [zks zk];

        % Estimation
        Fk = F(state, zk);
        Wk = W(state);
        Pk = Fk * Pk * Fk' + Wk * Qk * Wk';
        state = f(state, zk);

        % Update next ideal
        realstate = nextideal(realstate, k);

    end

    graph(states, realstates, zks);

endfunction


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function state = initstate ()
    global delta
    delta = 0.025;
    initgyrobias = 0;
    inittheta = 0;
    state = [inittheta 0 initgyrobias]';
endfunction


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% return identity matrix of dimension m x m
function foo = identity
    foo = eye(3);
endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function foo = myrand (range)
    foo = (rand - 0.5) * range;
endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% what is the next real state given this real state
function state = nextideal(state, i)
    global delta
    nextindex = i;
    theta = 2 * sin(nextindex / 180 * 3.14);
    velocity = (theta - state(1)) / delta;
    gbias = state(3) + myrand(1);
    state = [theta velocity gbias]';
endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%55
% simulate measurement using the real state
function meas = z(realstate)
    ygyro = realstate(2) + realstate(3) + myrand(1); % those are the noise
    yaccel = realstate(1) + myrand(1);
    meas = [ygyro; yaccel];
endfunction

% prediction function 
function state = f(state, meas)
    global delta
    theta = state(1) + (meas(1) - state(3)) * delta;
    omega = (meas(1) - state(3));
    state = [theta, omega, state(3)]';
endfunction

% partial derivative of f with respect to each state variable
function foo = F(state, meas)
    global delta
    foo = [1 0 -delta ; 0 0 -1; 0 0 1 ];
endfunction

% state noise
function foo = W(state)
    foo = eye(3);
endfunction

% predict measurement based on of state
function foo = h(state)
    foo = [state(2) + state(3); state(1) ];
endfunction

% parital derivative of h with respect to each state variable
function foo = H(state)
    foo = [0 1 1 ; 1 0 0];
endfunction

% measurement noise
function foo = V(state)
    foo = [1 0; 0 1];
endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5

function graph(states, realstates, zks);
    % gset term dumb;
    gset term postscript;

    theta = states(1, :);
    plot(theta)
    hold on
    
    % plot(zks(1,:))
    
    realtheta = realstates(1, :);
    plot(realtheta);
    hold off

    gset output "output.ps"
    replot
endfunction
