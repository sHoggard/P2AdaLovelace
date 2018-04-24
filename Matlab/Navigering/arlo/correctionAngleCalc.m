%Function described to calculate a correctional angle based on the two
%latest calculated angles towards the object from the robotS

function [sigma] = correctionAngleCalc(angleVector)

    if(angleVector(end) > angleVector(end-1))
        sigma = angleVector(end-1)-angleVector(end);
    elseif (angleVector(end) < angleVector(end-1))
        sigma = angleVector(end)-angleVector(end-1);
    end

end

