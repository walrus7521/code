% This is a script to help you in determining the right Kp.
% To use it you've got to add one output port
% and connect it to the speed signal.
% Run this file from the working folder where you've got
% the "cruise_control_sim.slx" model.
% It will print a figure with the speed signal response
% having Kp varying from 0.2 to 1.2, with 0.1 steps.

open_system('cruise_control_sim')
KpSweep = 0.2:.1:1.2;

for i = 1:length(KpSweep)
    Kp = KpSweep(i);
    Ki=0;
    [t,x,y] = sim('cruise_control_sim',[],simset('OutputVariables','ty'));
    
    plot(t,y,'Color',rand(1,3)); hold on;
end
title('Testing with Ki = 0')
xlabel('Time');
hold off;