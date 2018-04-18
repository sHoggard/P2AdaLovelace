%Function that calculates the number of pulses to send to wheels for it to
%rotate towards the object whenever the correction angle is given as input

function [p] = wheelImpulseCalculation(sigma)
f=41;
pc=144;
d=0; %m�tte till typ 1-200cm (jelenas m�tning:15cm)
p =(sigma * f * pc)/ (pi*d);


end

