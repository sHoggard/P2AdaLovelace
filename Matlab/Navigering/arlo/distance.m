%Function to determine distance between the robot and the object

function [s] = distance(y2,y1,x2,x1)

s = sqrt(((x2-x1)^2) + ((y2-y1)^2));

end

