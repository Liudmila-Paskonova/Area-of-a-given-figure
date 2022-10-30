CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC = gcc

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm

AS=nasm

ASMFLAGS = -f elf32

.PHONY: all clean

all: integral

integral: functions.o integral.o
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

integral.o: integral.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
functions.o: functions.asm
	$(AS) $(ASMFLAGS) $^ -o $@
	
test: integral
	./integral -R 4:5:-2:-0.5:0.0001:-1
	./integral -R 4:6:2:4:0.0001:3
	./integral -R 5:6:-4:-2:0.001:-3
	./integral -I 4:3:6:0.0001:69
	./integral -I 5:1:2:0.001:0.5
	./integral -I 6:-9:-8:0.0001:-0.5
	
clean:
	rm -rf *.o
