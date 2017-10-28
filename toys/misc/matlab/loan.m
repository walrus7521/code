function [mpay,tpay]  = loan(amount, rate, years)
% loan calculate t nm
% dude you know the drill
format bank
ratem = rate*0.01/12;
a = 1+ratem;
b = (a^(years*12)-1)/ratem;
global sup = 42;
mpay=amount*a^(years*12)/(a*b);
tpay=mpay*years*12;

