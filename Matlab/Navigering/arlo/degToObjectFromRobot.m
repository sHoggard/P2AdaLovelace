%Function used to determine the angle between the robot and the object

function [alpha] = degToObjectFromRobot(y2,y1,x2,x1)
k = (y2-y1) / (x2-x1);
alpha = rad2deg(atan(k));
end

