#include<stdio.h>
#include<windows.h>
#include<profileapi.h>
#include<winternl.h>
#include"bench.h"


#define ITERATIONS  100
#define NUM_OF_FUNCTIONS 28


int main(void){

    char module[] = "ntdll.dll";

    // a function from each alphabet
	char *func[] = {
		"A_SHAFinal",
		"CsrAllocateCaptureBuffer",
		"DbgBreakPoint",
		"EtwCreateTraceInstanceId",
		"LdrAccessResource",
		"MD4Final",
		"NlsAnsiCodePage",
		"PfxFindPrefix",
		"RtlAbortRXact",
		"SbExecuteProcedure",
		"TpAllocAlpcCompletion",
		"VerSetConditionMask",
		"WerReportSQMEvent",
		"__C_specific_handler",
		"_atoi64",
		"abs",
		"bsearch",
		"ceil",
		"fabs",
		"isalnum",
		"labs",
		"mbstowcs",
		"pow",
		"qsort",
		"sin",
		"tan",
		"vDbgPrintEx",
		"wcscat"
	};
    // first benchmark : GetProcAddress
    double elapsed_time = 0, start_time;

    unsigned int i, j;
    // run the function ITERATIONS times
    for(i = 0; i < ITERATIONS ; i++){
        for(j = 0; j < NUM_OF_FUNCTIONS; j++){
                start_time = get_time();
                PVOID addr = wrap_GetProcAddress(module, func[j]);
                elapsed_time += (double)(get_time() - start_time);
                if(!addr){
                        printf("couldn't find %s :(\n", func[j]);
                        exit(1);
                }
        }
    }

	printf("GetProcAddress took \t\t%.10f\n", elapsed_time / ( NUM_OF_FUNCTIONS));



    // second benchmark : bruteforce
    double brute_elapsed_time = 0, brute_start_time;

    // run the function ITERATIONS times
    for(i = 0; i < ITERATIONS ; i++){
        for(j = 0; j < NUM_OF_FUNCTIONS; j++){
                brute_start_time = get_time();
                PVOID addr = get_function_address(func[j], BRUTEFORCE);
                brute_elapsed_time += (double)(get_time() - brute_start_time);
                if(!addr){
                        printf("couldn't find %s :(\n", func[j]);
                        exit(1);
                }
        }
    }

	printf("bruteforcing took \t\t%.10f\n", brute_elapsed_time / ( NUM_OF_FUNCTIONS));

    // third benchmark : BetterGetProcAddress
    double better_elapsed_time = 0, better_start_time;
    // run the function ITERATIONS times
    for(i = 0; i < ITERATIONS; i++){
        for(j = 0; j < NUM_OF_FUNCTIONS; j++){
                better_start_time = get_time();
                PVOID addr = get_function_address(func[j], MAGIC);
                better_elapsed_time += (double)(get_time() - better_start_time);
                if(!addr){
                        printf("couldn't find %s :(\n", func[j]);
                        exit(1);
                }
        }
    }

	printf("BetterGetProcAddress took \t%.10f\n", better_elapsed_time / ( NUM_OF_FUNCTIONS));

	printf("BetterGetProcAddress was %d times faster than GetProcAddress\n", (int)(elapsed_time / better_elapsed_time));
}

PVOID wrap_GetProcAddress(char *module, char *func){
	HMODULE Hntdll = LoadLibraryA(module);
	return (PVOID)GetProcAddress(Hntdll, func);
}

double get_time()
{
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return ((double)t.QuadPart / (double)f.QuadPart);
}
