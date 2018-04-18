%Function used to determine the angle between the robot and the object

function [alpha,xDif,yDif,k,cosValue,sinValue] = degToObjectFromRobot(yO,yR,xO,xR)

%difference in length units between the object and the robot
yDif = yO-yR;
xDif = xO-xR;

%absolute values of the difference and the lean (k) of the line between the
%object and the robot
yAbs = abs(yDif);
xAbs = abs(xDif);
k = yAbs / xAbs;

%distance in length units between object and robot
s = distance(yO,yR,xO,xR);

%Cosinus and Sinus values to determine quadrant for the Cartesian
%Coordinate-system
cosValue = xDif/s;
sinValue = yDif/s;

%If-statements that determine alpha angle along with quadrant placement
if(sinValue == 0 && cosValue >0)
   alpha = 0;
 elseif(sinValue > 0 && cosValue == 0)
   alpha = 90;
 elseif(sinValue == 0 && cosValue <0)
   alpha = 180;
 elseif(sinValue < 0 && cosValue == 0)
    alpha = 270;
    
elseif(sinValue > 0 && cosValue >= 0)%kvadrant 1
alpha = rad2deg(atan(k));
elseif(sinValue >= 0 && cosValue < 0)%kvadrant 2
alpha = rad2deg(atan(k))+ 90;
elseif(sinValue <= 0 && cosValue < 0) %kvadrant 3
    alpha = 270 - rad2deg(atan(k));
elseif(sinValue < 0 && cosValue >= 0)%kvadrant 4
    alpha = 360 - rad2deg(atan(k));
end
end

