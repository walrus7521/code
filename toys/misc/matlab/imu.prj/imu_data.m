
INERTIAL = csvread('data.csv',1,0);
nrows = size(INERTIAL,1);

function gravity(accel)
    x = accel(1); y = accel(2); z = accel(3);
    g = [-x, -y, -z];
    rawZ = -g
    zAxis = rawZ/norm(rawZ);
    rawY = [0, zAxis(3), -zAxis(2)];
    yAxis = rawY / norm(rawY);
    xAxis = cross(yAxis, zAxis);
    R = [xAxis; yAxis; zAxis];
    disp(R);
    disp("\n");
    ZZ = R*g';
    disp(ZZ);
    disp("\n");    
end


for i = 1:size(INERTIAL, 1)    
%   r   = INERTIAL(i,:); % entire ith row
    acc = INERTIAL(i,1:3);
    mag = INERTIAL(i,4:6);
    gyr = INERTIAL(i,7:9);
    %disp(acc);
    gravity(acc);
    disp("\n");
end

% https://gist.github.com/sinc/2409107
% create rotation Matrix From Gravity Accelerometer
%
%  The Z axis of our rotated frame is opposite gravity
%   vec3f_t zAxis = vec3f_normalize(vec3f_init(-x, -y, -z));
%    
%  The Y axis of our rotated frame is an arbitrary vector perpendicular to gravity
%  Note that this convention will have problems as zAxis.x approaches +/-1 since the magnitude of
%  [0, zAxis.z, -zAxis.y] will approach 0
%    vec3f_t yAxis = vec3f_normalize(vec3f_init(0, zAxis.z, -zAxis.y));
%    
%  The X axis is just the cross product of Y and Z
%    vec3f_t xAxis = vec3f_crossProduct(yAxis, zAxis);
%    
%    CMRotationMatrix mat = {
%        xAxis.x, yAxis.x, zAxis.x,
%        xAxis.y, yAxis.y, zAxis.y,
%        xAxis.z, yAxis.z, zAxis.z};
%
% Thanks for this! Here's some octave code that I used to prove to myself that it works:
% 
% #1. Use an acceleration reading to compute the rotation matrix per the gist
% #    The value of g was obtained from my accelerometer at rest.
% 
% octave:33> g = [1.010040589617603, 0.0065919980468153935, 0.09399700918607135]
% g = 1.0100406   0.0065920   0.0939970
% 
% octave:34> rawZ = -g
% rawZ = -1.0100406  -0.0065920  -0.0939970
% 
% octave:35> zAxis = rawZ/norm(rawZ)
% zAxis = -0.9956766  -0.0064983  -0.0926603
% 
% octave:36> rawY = [0, zAxis(3), -zAxis(2)]
% rawY = 0.000000  -0.092660   0.006498
% 
% octave:37> yAxis = rawY / norm(rawY)
% yAxis = 0.00000  -0.99755   0.06996
% 
% octave:38> xAxis = cross(yAxis, zAxis)
% xAxis = 0.092888  -0.069656  -0.993237
% 
% octave:39> R = [xAxis; yAxis; zAxis]
% R =
%    0.09289   0.00000  -0.99568
%   -0.06966  -0.99755  -0.00650
%   -0.99324   0.06996  -0.09266

% #2. Compute the product of the rotation matrix with the original acceleration reading, and you should get around [0, 0, 1].  
% #    Or in english: If your accelerometer reading is is the same as what you've said means "earth reference" then 
% #    The rotated value of that reading should look like a object laying flat and parallel to the ground.
 
% octave:40> R*g'  # g' because we need a column vector here.
% ans =
%    2.2987e-04
%   -7.7542e-02
%   -1.0115e+00
% Conclusion: It works!

