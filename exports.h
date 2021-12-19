PVOID get_function_address(char *func, int method);
PVOID get_export(PVOID base, char *func, int method);
enum SEARCH_METHOD {MAGIC, BRUTEFORCE};