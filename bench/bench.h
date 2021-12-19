enum SEARCH_METHOD {MAGIC, BRUTEFORCE};
double get_time();
PVOID wrap_GetProcAddress(char *, char *func);
PVOID get_function_address(char *func, int meth);