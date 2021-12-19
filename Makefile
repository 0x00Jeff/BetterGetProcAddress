FILE=	BetterGetProcAddress.exe
SRC	=	$(FILE:exe=.c) exports.c
OBJ	=	BetterGetProcAddress.o exports.o

CC	=	x86_64-w64-mingw32-gcc
CFLAGS	= -Wall -Wextra

$(FILE): $(OBJ)
	$(CC) $^ -o $@

../exports.o:	../exports.c ../exports.h

BetterGetProcAddress.o:	BetterGetProcAddress.c
