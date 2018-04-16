% Connect to the arduino, change COM-number as neccessary.
if(~exist('a','var'))
    a = arduino_com('COM3');
end

analogWrite(a,0,'DAC1')