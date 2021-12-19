![you even bench bro ?](bench.gif)

the benchmarker runs the function with 3 methods, against 6 random ntdll exports, 100 times each, and then calculate the average time for each method

	first method : using the GetProcAddress Api
	second method : checking all the exports one by one
	third method : binary search

as you can see in the following benchmark, my implementation is roughly 4 times faster, more or less sometimes (best case was 11 times faster, worst case 4 was times)

```
GetProcAddress took             0.0002773809
bruteforcing took               0.0008147637
BetterGetProcAddress took       0.0000723216
```
