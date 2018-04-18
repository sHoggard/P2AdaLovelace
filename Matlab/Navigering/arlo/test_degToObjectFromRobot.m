function test_degToObjectFromRobot()

d1 = degToObjectFromRobot(2,1,2,1) %45degrees
disp('Test for 45 degrees. Calculations gives the answer');

d2 = degToObjectFromRobot(2,2,2,1) %0degrees-x axle
disp('Test for 0 degrees. Calculations gives the answer');

d3 = degToObjectFromRobot(2,1,2,2) %90degrees
disp('Test for 90 degrees. Calculations gives the answer');

d4 = degToObjectFromRobot(0,0,-1,1) %180degrees
disp('Test for 180 degrees. Calculations gives the answer');

d5 = degToObjectFromRobot(2,5,2,5) %225degrees
disp('Test for 225 degrees. Calculations gives the answer');

d6 = degToObjectFromRobot(2,5,2,2) %270degrees
disp('Test for 270 degrees. Calculations gives the answer');

end

