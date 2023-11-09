# Simulation for GEM5 Makefile
CC = riscv32-unknown-elf-gcc
DEFS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_POSIX_C_SOURCE=200809L
CFLAGS = -Wall -O3 -g -std=c99 -pedantic $(DEFS)
ifneq (,$(filter custom,$(MAKECMDGOALS)))
	DEFS += -DCUSTOM_INSTR=1
endif


.PHONY: all clean custom
all: knn clean_after
custom: knn clean_after

knn: knn.o util.o libhelper.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

util.o: util.c util.h
libhelper.o: libhelper.c libhelper.h

clean_after:
	rm -rf *.o

clean:
	rm -rf *.o knn
