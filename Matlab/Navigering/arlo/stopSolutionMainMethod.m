%--------------------------------------------------------------------%

%   Stanna upp och rotera roboten påväg till objektet                %

%--------------------------------------------------------------------%

function stopSolutionMainMethod(xR,yR)

%------Variable Declaration------------------------------------------%
xO =0; %Objects Position in the room along the X-axis
yO =0; %Objects Position in the room along the Y-axis
distanceToObjectIsClose=false;
%N = 0; %size of vector
alphaVectorCounter=0;%Counter for alphaVector, which allows for storing of alpha-variables after each iteration/calculation
taskCompleted = false; %boolean variable for our main Task

%-----Vector Declaration---------------------------------------------%
alpha = zeros(1,alphaVectorCounter+1); %Alphavector for the angles needed for future calculations


%------WHILE FUNCTION------------------------------------------------%
while(taskCompleted ==false)  %While function for the majority of the task
    
distanceFromRobotToObject = distance(yO,xO,yR,xR);%Distance calculation between Robot and Object

if(distanceFromRobotToObject < 100)
    distanceToObjectIsClose=true;
elseif (distanceFromRobotToObject >=100)
    distanceToObjectIsClose=false;
end
    
    
%------IF FUNCTION - NOT CLOSE TO OBJECT--------------------------------------------%
   if(distanceToObjectIsClose == false)
alpha(alphaVectorCounter) = degToObjectFromRobot(yO,yR,xO,xR);%Angle calculation and then save to vector

%If function to distinguish between the first angle and the following
%sigma-correction angles throughout the demonstration and movement of the
%robot
if(alphaVectorCounter == 0)
     rotateRobotTowardsObject(alpha);
else
    alpha(alphaVectorCounter) = correctionAngleCalc(alpha);
    rotateRobotTowardsObject(alpha);
end     

alphaVectorCounter = alphaVectorCounter + 1; %Incrementation of the alphaVectors Counter variable

moveRobotTowardsObject(distanceFromRobotToObject);%Moves 25% of the distance towards the Object

%------IF FUNCTION - CLOSE TO OBJECT--------------------------------------------%

   elseif (distanceToObjectIsClose == true)
       
       alpha(alphaVectorCounter) = degToObjectFromRobot(yO,yR,xO,xR);%Angle calculation and then save to vector

%If function to distinguish between the first angle and the following
%sigma-correction angles throughout the demonstration and movement of the
%robot
if(alphaVectorCounter == 0)
     rotateRobotTowardsObject(alpha);
else
    alpha(alphaVectorCounter) = correctionAngleCalc(alpha);
    rotateRobotTowardsObject(alpha);
end     

alphaVectorCounter = alphaVectorCounter + 1; %Incrementation of the alphaVectors Counter variable

moveRobotTowardsObjectClose(distanceFromRobotToObject);%Moves 25% of the distance towards the Object
   end    
end
end

