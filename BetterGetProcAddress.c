#include<stdio.h>
#include<windows.h>
#include<winternl.h>
#include"exports.h"

double get_time();

int main(void){
	char *func = "strlen";

	int (*my_strlen)(char *);
	my_strlen = (int(*)(char *))get_function_address(func, MAGIC);
	if(!my_strlen){
		fprintf(stderr, "%s doesn't exist in ntdll\n", func);
		exit(1);
	}
	else
		printf("the answer is %d", (my_strlen("thoughts peter ?") << 1) + 10);

	return 0;
}
