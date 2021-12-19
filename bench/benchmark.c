#include<stdio.h>
#include<windows.h>
#include<profileapi.h>
#include<winternl.h>
#include"bench.h"


#define ITERATIONS  100
#define NUM_OF_FUNCTIONS 6

double get_time();
PVOID wrap_GetProcAddress(char *, char *func);
PVOID get_function_address(char *func);

int main(void){

    char module[] = "ntdll.dll";
    char *func[] = {
		"NtOpenProcess",
		"NtMapViewOfSection",
		"NtCreateFile",
		"NtAllocateVirtualMemory",
		"NtCreateSection",
		"LdrLoadDll",
	};

    // first benchmark : GetProcAddress
    double elapsed_time = 0, start_time;


    // run the function ITERATIONS times
    unsigned int i, j;
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

	printf("GetProcAddress took = \t\t%.10f\n", elapsed_time / ( NUM_OF_FUNCTIONS));

    // second benchmark : BetterGetProcAddress
    double better_elapsed_time = 0, better_start_time;

    // run the function ITERATIONS times
    for(i = 0; i < ITERATIONS; i++){
        for(j = 0; j < NUM_OF_FUNCTIONS; j++){
                better_start_time = get_time();
                PVOID addr = get_function_address(func[j]);
                better_elapsed_time += (double)(get_time() - better_start_time);
                if(!addr){
                        printf("couldn't find %s :(\n", func[j]);
                        exit(1);
                }
        }
    }

	printf("BetterGetProcAddress took = \t%.10f\n", better_elapsed_time / ( NUM_OF_FUNCTIONS));


}

PVOID wrap_GetProcAddress(char *module, char *func){
	HMODULE Hntdll = LoadLibrary(module);
	return (PVOID)GetProcAddress(Hntdll, func);
}

double get_time()
{
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return ((double)t.QuadPart / (double)f.QuadPart);
}