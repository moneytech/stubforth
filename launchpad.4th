hex

.( Loading launchpad.4th...) lf

: red 8 << tmtbmatchr timer0 + ! ;
: green 8 << tmtbmatchr timer1 + ! ;
: blue 8 << tmtamatchr timer1 + ! ;

: col
	dup 10 >> ff and red
	dup 8 >> ff and green
	ff and blue
;

decimal
7 syst_csr !
: ms 40000 syst_cvr ! 40000 syst_rvr ! 0 tick ! begin wfi dup tick @ < until drop ;
: 100us 4000 syst_cvr ! 4000 syst_rvr ! 0 tick ! begin wfi dup tick @ < until drop ;

: heartbeat begin 900 ms [ hex ] 300000 col [ decimal ] 100 ms [ hex ] 000000 col again ;

\ gpio

hex

: pa gpioa_apb ;
: pb gpiob_apb ;
: pc gpioc_apb ;
: pd gpiod_apb ;
: pe gpioe_apb ;
: pf gpiof_apb ;

\ 1. Enable the clock to the port by setting the appropriate bits in
\ the RCGCGPIO register (see page 310). In addition, the SCGCGPIO and
\ DCGCGPIO registers can be programmed in the same manner to enable
\ clocking in Sleep and Deep-sleep modes.

3f rcgcgpio !

\ 2. Set the direction of the GPIO port pins by programming the
\ GPIODIR register. A write of a '1' indicates output and a write of a
\ '0' indicates input.

e gpiodir pf !
			
\ 3. Configure the GPIOAFSEL register to program each bit as a GPIO or
\ alternate pin. If an alternate pin is chosen for a bit, then the
\ PMCx field must be programmed in the GPIOPCTL register for the
\ specific peripheral required. There are also two registers,
\ GPIOADCCTL and GPIODMACTL, which can be used to program a GPIO pin
\ as a ADC or DMA trigger, respectively.

\ 4. Set the drive strength for each of the pins through the GPIODR2R,
\ GPIODR4R, and GPIODR8R registers.

e gpiodr8r pf !
	

\ 5. Program each pad in the port to have either pull-up, pull-down,
\ or open drain functionality through the GPIOPUR, GPIOPDR, GPIOODR
\ register. Slew rate may also be programmed, if needed, through the
\ GPIOSLR register.

\ 6. To enable GPIO pins as digital I/Os, set the appropriate DEN bit
\ in the GPIODEN register. To enable GPIO pins to their analog
\ function (if available), set the GPIOAMSEL bit in the GPIOAMSEL
\ register.

e gpioden pf !
	
\ 7. Program the GPIOIS, GPIOIBE, GPIOBE, GPIOEV, and GPIOIM registers
\ to configure the type, event, and mask of the interrupts for each
\ port.

\ 8. Optionally, software can lock the configurations of the NMI and
\ JTAG/SWD pins on the GPIO port pins, by setting the LOCK bits in the
\ GPIOLOCK register.

\ pf0 - sw2
\ pf1 - red led
\ pf2 - blue led
\ pf3 - green led
\ pf4 - sw1

: led 1 << gpiodata pf e 2 << + ! ;
1 led

4c4f434b gpiolock pf !
ff gpiocr pf !
1f gpioden pf !
11 gpiopur pf !

: sw1? gpiodata pf 10 2 << + @ 0= ;
: sw2? gpiodata pf 1 2 << + @ 0= ;

