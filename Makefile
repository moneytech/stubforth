
GCC = gcc
CFLAGS = -O3 -m32 -g -Wall

all: stub4th

config.h: .rev.h

.rev.h: .git/* .
	echo -n \#define REVISION \"  > $@
	echo -n $$(git describe --always --dirty) >> $@
	echo -n '"' >> $@

stub4th.o:  stub4th.c  *.h Makefile *.m4 config.h
	$(GCC) $(CFLAGS) -o $@ -c $<

stub4th:  stub4th.o
	$(GCC) $(CFLAGS) -o $@ $<

%.size: %
	nm -t d --size-sort --print-size $<

%.c: %.c.m4 Makefile
	m4 -s $< > $@

check: stub4th
	echo 42 | ./$<
	@echo

clean:
	rm -f .rev.h *.o *.s stub4th.c