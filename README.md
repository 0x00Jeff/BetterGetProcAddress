# BetterGetProcAddress
POC of a better/faster implementation of GetProcAddress using binary search, see the benchmark directory for more info about speed

note that I'm using mingw-gcc, if that's not the case for you, you might need to provide some struct declarations such as the PEB, instead of including winternl.h

also shoutout to hyper and base64

writeup explaining how this works : https://phasetw0.com/windows-internals/optimizing_function_resolving/
