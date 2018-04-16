This package provides an example of how to wrap a C++ class in a MATLAB class, via a mex interface, safely, without memory leaks, whilst achieving an interface in MATLAB that is similar to the underlying C++ interface. 
After downloading, call: 
>> run_example 
in MATLAB to see an example implementation in action.

Look in run_example.m, example_mex.cpp (and optionally example_interface.m if you don't want to use the standard interface) to see how this is implemented, and copy the structure to interface with your own C++ classes.

This submission is inspired by the following newsgroup thread: 
http://www.mathworks.com/matlabcentral/newsreader/view_thread/278243 
Thanks to all those who have contributed.