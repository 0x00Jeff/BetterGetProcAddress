![you even bench bro ?](bench.gif)

the benchmarker runs tries to resolve the exports using 3 methods, against 28 ntdll exports, everyone starting with a different character, 100 times each, and then calculates the average each method took

	first method : using the GetProcAddress Api
	second method : checking all the exports one by one
	third method : binary search

as you can see in the following benchmark, my implementation is roughly 9 times faster (on my computer, I had different results on other ones), more or less sometimes (best case was 15 times faster, worst case 6 was times)

```
GetProcAddress took 		0.0002785584
bruteforcing took 		0.0025655994
BetterGetProcAddress took 	0.0000304231
BetterGetProcAddress was 9 times faster than GetProcAddress
```
