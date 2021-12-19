FILE=	bench.exe
SRC	=	$(FILE:.exe=.c) ../exports.c
OBJ	=	$(SRC:.c=.o)

CC	=	x86_64-w64-mingw32-gcc
CFLAGS	= -Wall -Wextra

$(FILE): $(OBJ)
	$(CC) $^ -o $@

../exports.o:	../exports.c ../exports.h

bench.o:	bench.c bench.h