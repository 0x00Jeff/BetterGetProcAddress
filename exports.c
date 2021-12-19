#include<stdio.h>
#include<windows.h>
#include<winternl.h>
#include"exports.h"

PVOID get_function_address(char *func, int method){
    PPEB p = (PPEB)__readgsqword(0x60);
    PLIST_ENTRY main_module = &p -> Ldr -> InMemoryOrderModuleList;
    PLIST_ENTRY module = main_module -> Flink -> Flink; // skip to ntdll
	PLDR_DATA_TABLE_ENTRY dll = (PLDR_DATA_TABLE_ENTRY)((char *)module  - sizeof(LIST_ENTRY));

	return get_export(dll -> DllBase, func, method);
}

PVOID get_export(PVOID base, char *func, int method){
	PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)base;
	PIMAGE_FILE_HEADER head = (PIMAGE_FILE_HEADER)((char *)base + dos -> e_lfanew + sizeof(DWORD));
	PIMAGE_OPTIONAL_HEADER opt_head = (PIMAGE_OPTIONAL_HEADER)(head + 1);
    ULONG export_size =  opt_head -> DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
	ULONG export_rva = opt_head -> DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

	if(!export_size)
		return NULL;

	PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY)((char *)base + export_rva);

	DWORD *name_rva = (PDWORD)((char *)base + exports -> AddressOfNames);

	DWORD *function_rva = (PDWORD)((char *)base + exports -> AddressOfFunctions);

	WORD *ordinal = (PWORD)((char *)base + exports -> AddressOfNameOrdinals);


// binary search

    if(method == MAGIC){
        unsigned long right, left, middle, old_middle;
        right = exports -> NumberOfNames;
        left = 0;


        while(right != left){
            old_middle = middle;
            middle = left + ((right - left) >> 1);
            if(middle == old_middle) break; // function doesn't exist

            int result = strcmp((char *)base + name_rva[middle], func);
            if(!result)
                return (PVOID)((char *)base + function_rva[ordinal[middle]]);
            else if(result < 0)
                left = middle - 1;
            else
                right = middle + 1;
        }
    }

    // bruteforce
    else {
        unsigned long i;
        for(i = 0; i < exports -> NumberOfNames; i++){
            if(!strcmp((char *)base + name_rva[i], func)){
                // index the AddressOfFunctions array's VA by the function ordinal
                return (PVOID)((char *)base + function_rva[ordinal[i]]);
            }
        }
    }

	return NULL;
}
