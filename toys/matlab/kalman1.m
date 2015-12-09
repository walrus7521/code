#!/usr/bin/octave -qf

%This program uses Kalman filtering to find out the 
%prediction of underlying independent variable x as 
%described in example on page 13 in the document
%"An Introduction to the Kalman Filter"
%by  Greg Welch and Gary Bishop
%http://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf

clear all;

A=1;
B=0;
samples=100;
timeidx=1:samples;
timeidx=timeidx';
H=1;
xbar=[];
%y=-0.37727+normal_rnd(0,0.025,samples,1);
y=-0.37727+normrnd(0,0.025,samples,1);
q=1;%1e-05;
xhat=0;
P0=1;
r=1;
u=zeros(samples+1,1);

nu=size(u,2);
ny           = size(y,2);  % # of outputs
nx           = size(P0,1); % # of states
nv           = size(q,1);  % # of process noise sources
nw           = size(r,1);  % # of measurement noise sources

Pxbar = P0;                % A priori estimate = initial covariance
xhat_data = zeros(samples+1,nx); % Matrix for storing state estimates
Pmat      = zeros(samples+1,nx*nx); % Matrix for storing cov. matrices
yidx  = 1;                 % Index into y-vector 

Px   = Pxbar;
uk1=0;
yidx=1;

xhat_data(1)=xhat';
Pmat(1,:)=reshape(Px,1,nx*nx);

for k=1:samples,

  % Time Update ("Predict")
  % (1) Project the state ahead
  if nu>0 uk1 = u(k+1,:)'; end
  xbar=A*xhat+B*uk1;
  % (2) Project the error covariance ahead
  Pxbar = A*Px*A' + q;    
 

  %Measurement Update ("Correct")
  if (k<=timeidx(end) && timeidx(yidx)==k)

    %(1) Compute the Kalman gain
    K=Pxbar*H'/(H*Pxbar*H'+r);

    %(2) Update estimate with measurement zk
    xhat = xbar + K*(y(yidx,:)'- H*xbar);

    %(3) Update the error covariance
    Px   = Pxbar-K*H*Pxbar;

    yidx=yidx+1;

  end

  xhat_data(k+1,:) = xhat';
  Pmat(k+1,:)      = reshape(Px,1,nx*nx);
 
 
end

underlying_x=xhat

tmpmat=[y;0];
tmpmat=[tmpmat xhat_data];
save -ascii tmpmat.txt tmpmat;
save -ascii Pmat.txt Pmat;
