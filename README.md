this code aims to fetch a remote raw dll and load it into the current process space, you can also call it's inner exported functions

the url where to fetch the binary data must be provided as first argument when executing the program

to compile it successfully make sure that in VS project properties -> Advanced -> Character Set is NOT set

do not forget:
    -> if the remote raw dll was compiled in x64 then you must compile this code in x64 (same for x86)