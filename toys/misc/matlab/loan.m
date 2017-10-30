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
% wusup
% homi1
% homi2
% homi3
% homi4
% homi5

    try
        format bank
        ratem = rate*0.01/12;
        a = 1+ratem;
        b = (a^(years*12)-1)/ratem;
        mpay=amount*a^(years*12)/(a*b);
        tpay=mpay*years*12;
        error ("you suck");
    catch
        msg = lasterror.message;
        fprintf(1, 'dude: %s\n', msg);
        
end

