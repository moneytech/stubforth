TARGET = m68k-elf
GCC = $(TARGET)-gcc
CC= $(GCC) $(CFLAGS)
CFLAGS =  -Wall -m68000 -O2 -Wcast-align
LD = $(TARGET)-ld
OBJCOPY = $(TARGET)-objcopy

TTY = /dev/ttyUSB0

VPATH = $(HOME)/src/c/vivo/:$(HOME)/ext/linux-2.6/arch/m68k/lib/

all: stub4th

config.h: .rev.h

.rev.h: .git/* .
	echo -n \#define REVISION \"  > $@
	echo -n $$(git describe --always --dirty) >> $@
	echo -n '"' >> $@

stub4th.o:  stub4th.c  *.h Makefile *.m4 config.h platform.h
	$(GCC) $(CFLAGS) -o $@ -c $<

stub4th.s:  stub4th.c  *.h Makefile *.m4 config.h platform.h
	$(GCC) $(CFLAGS) -o $@ -S $<

stub4th:  stub4th.o
	$(GCC) $(CFLAGS) -o $@ $<

%.c: %.c.m4 Makefile
	m4 -s $< > $@

%.h: %.h.m4
	m4 -s $< > $@

check: stub4th.elf
	./test.tcl $(TTY)

clean:
	rm -f *grind.out.*
	rm -f .rev.h *.o *.s stub4th.c
	rm -f *.o *.s *.elf *.srec *.brec *.bin
	rm -f flashload


init:
#	stty -F $(TTY) -isig -icanon -echo -opost -onlcr -icrnl -imaxbel
	stty -F $(TTY) 9600
	echo U > $(TTY) # baud rate calibration
	sleep 0.06
	cat init.Brec  > $(TTY)
	sleep 0.06
	echo FFFFF200022410 > $(TTY) # pllcr: sysclk ½ -> full speed
	stty -F $(TTY) 19200
	sleep 0.06
	echo FFFFF902020138 > $(TTY) # ubaud
	stty -F $(TTY) 57600
	sleep 0.06
# 	echo FFFFF902020038 > $(TTY) # ubaud
# 	stty -F $(TTY) 115200
# 	echo FFFFF902020026 > $(TTY) # ubaud
# 	stty -F $(TTY) 38400
	perl -e '($$s,$$m,$$h)=localtime(time); printf("FFFFFB0004%02X%02X00%02X\n",$$h,$$m,$$s)' > $(TTY)

%.brec : %.srec
	srec_cat $< -Output $@ -B-Record

%.srec : %.elf
	$(OBJCOPY) $< -O srec $@

%.bin : %.elf
	$(OBJCOPY) $< -O binary $@

%.prog : %.brec
	cat $< > $(TTY)

%.prog : %.4th
	./infuse.tcl $(TTY) < $<

%.size : %.elf %.bin
	m68k-elf-nm -t d --size-sort --print-size $<
	m68k-elf-strip $<
	ls -l $+

.PHONY : %.prog clean %.size init

stub4th.elf : stub4th.o start.o modsi3.o mulsi3.o divsi3.o udivsi3.o umodsi3.o
	$(LD) -T vivo.ld $+ -o $@

flash.elf : flash.o stub4th.o modsi3.o mulsi3.o divsi3.o udivsi3.o umodsi3.o
	$(LD) -T vivo.ld $+ -o $@

dummy.elf : flash.o dummy.o modsi3.o mulsi3.o divsi3.o udivsi3.o umodsi3.o
	$(LD) -T vivo.ld $+ -o $@

flashload: flashload.c
	gcc -g -Wall flashload.c -o flashload

flash.prog : flash.bin flashload
	stty -F $(TTY) raw
	echo flash dup dup funlock ferase fstrap > $(TTY)
	./flashload $< < $(TTY) > $(TTY)

dummy.prog : dummy.bin flashload
	stty -F $(TTY) raw
	echo flash dup dup funlock ferase fstrap > $(TTY)
	./flashload $< < $(TTY) > $(TTY)

boot:
	make init
	make stub4th.prog
	make user

user:
	make user.prog
	make dragon.prog
	make vivo.prog
	make display.prog

USER = user.4th dragon.4th vivo.4th display.4th

boot.4th: $(USER) Makefile
	cat $(USER) > $@
	echo 50 honk >> $@

boot.fprog: boot.4th flashload
	echo 0 fbblock dup dup funlock ferase fstrap > $(TTY)
	./flashload < $(TTY) > $(TTY) $<

TAGS: .
	ctags-exuberant -e  --langdef=forth --langmap=forth:.4th.m4 \
	--regex-forth='/: *([^ ]+)/\1/' \
	--regex-forth='/(primary|secondary|constant)\([^,]+, ([^,\)]+)/\2/' \
	--regex-forth='/(primary|secondary|constant)\(([a-z0-9_]+)/\2/' \
	 *.4th *.c.m4 platform.h *.m4
