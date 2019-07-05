.( set up 20ms pulses on LED2 for controlling a servo motor...) lf

2 8 << 3 6 << or 2 4 << or tactl !
ec70 fc20 + 2 / taccr1 !
: s 4 << ec88 + taccr1 ! ;
: loop begin word number s again ;
f0 s

 \ output mode 6
6 4 << tacctl1 !

\ p1.6/ta0.1 out1 output
1 6 << p1sel +!

2 8 << 3 6 << or
1 4 << or t1ctl !
.( set up 20ms pulses on LED2 for controlling a servo motor...done) lf

\ ffff t1ccr0 !
\ 0 p2out !

\ : us 2* 0 t1r ! begin dup t1r @ u< until drop ;

\ : l begin 1 p2dir ! 1 ms 0 p2dir ! 0 t1r !
\ 		begin p2in @ 1 and until
\ 		t1r @ e00 < p1out !  again ;

\ \ p2.1 T1.1
\ \ p2.4 T1.2

\ 1 1 << dup p2sel +! p2dir +!
\ 1 4 << dup p2sel +! p2dir +!

\ \ : on
\ 3 5 << t1cctl1 !
\ 7 5 << t1cctl2 !
\ \ : off 0 t1cctl1 ! 0 t1cctl2 ! ;

\ \ : duty off
\ \ 	dup t1ccr0 @ swap - t1ccr1 ! t1ccr2 ! on ;

\ 20 duty

\ : period off
\ 	t1ccr0 ! on ;
	
\ variable state
\ variable delay
\ 10 state !
\ ffff delay !

\ : s? p1in c@ 1 5 << and 0= ;

\ : loop
\ 	begin rot?
\ 		?dup if
\ 			10 * s? if
\ 				10 * minus
\ 				delay +!
\ 				delay @ -1 > if
\ 					-1 delay ! then
\ 				delay @ period
\ 				state @ duty
\ 			else
\ 				state +!
\ 				state @ 0< if
\ 					20 state ! then
\ 				state @ duty
\ 			then
\ 		then
\ 	again
\ ;


\ adc

\ 0 adc10ctl1 ?
\ 0 adc10ctl0 ?
\ 0 adc10ctl1 !
\ 0 adc10ctl0 !
\ 10 adc10ctl0 |! \ ADCON
\ 1 d << adc10ctl0 |! \ internal reference
\ 3 b << adc10ctl0 |! \ 64clk s&h
\ \ 3 5 << adc10ctl1 |! \ clk/4
\ 7 5 << adc10ctl1 |! \ clk/8
\ \ 3 5 << adc10ctl0 |! \ REF2_5V | REFON
\ 1 5 << adc10ctl0 |! \ !REF2_5V | REFON
\ a c << adc10ctl1 |! \ temperature sensor
\ b c << adc10ctl1 |! \ vcc/2
\ \ 2 3 << adc10ctl1 |! \ smclk


\ : sample
\   3 adc10ctl0 |!
\   begin
\   adc10ctl1 @ 1 and while \ adcbusy
\   [char] . emit
\   repeat
\   3 adc10ctl0 ~&!
\   adc10mem @ ;

\ : avg
\   0 1f
\   begin
\   swap sample + swap
\   ?dup while 1-
\   repeat
\   5 >> ;

\ : avg2
\   0 1f
\   begin
\   swap avg + swap
\   ?dup while 1-
\   repeat
\   5 >> lf ;
