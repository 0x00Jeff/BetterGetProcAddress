# BetterGetProcAddress

POC of a better/faster implementation of GetProcAddress using binary search, see the benchmark directory for more info about speed

note that I'm using mingw-gcc, if that's not the case for you, you might need to provide some struct declarations such as the PEB, instead of including winternl.h

also note that this is just a POC that only parses ntdll exports, shouldn't be hard to generalize it tho

lastly shoutout to hyper and base64
