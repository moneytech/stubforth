hex

\ flash chip control

: flash 800000 ;
: c? c@ . ;
: fcmd flash c! ;
: funlock 60 fcmd D0 swap c! ;
: fsr 70 fcmd flash 1 + c@ ;
: flstatus 90 fcmd 5 + c? ;
: fcsr 50 fcmd ;
: farr FF fcmd ;

: ferase ( a -- )
dup funlock 20 fcmd D0 swap c! ;

: fwrite ( c a -- )
dup 1 and
if
 1 xor
 swap FF00 or
else
 swap 8 << FF or
then
10 << FFFF or
swap
10 fcmd
! ;

: fwait
begin
 fsr 80 and until ;

\ Write raw input bytes to flash, starting at the specified address.
\ Use out-of-band BREAK to stop flashing.
: fstrap ( a -- )
raw
quiet
begin
 dup key dup emit swap
 fwait
 fwrite
 1 +
 0 until ;

: fchiperase ( -- )
flash
begin
 dup .
 dup funlock
 dup ferase fwait
 10000 + dup
 flash 1F0000 +
 1 - 
 >
  until
flash 1F0000 +
begin
 dup .
 dup funlock
 dup ferase fwait
 2000 + dup
 flash 200000 +
 1 -
 >
  until ;

hex 

\ power control

: sleep 80 pctlr c! ;

\ non-platform-specific TODO: move somewhere else

: fib dup 0= if else dup 1 = if else 1 - dup recurse swap 1 - recurse + then then ;
: tuck swap over ;
: gcd dup if tuck mod recurse else drop then ;
: 2dup 1 pick 1 pick ;

: dump ( addr n -- )
over + swap
( endaddr addr )
begin
dup c@ emit
1 + 2dup <
until
lf ;
: depth sp@ s0 - cell + cell / ;
: .s 23 emit depth dup . begin dup 0 > while dup pick . 1 - repeat lf drop ;

: DUMP flash 400 raw dump ;

: delay ( n --, pause for approx n milliseconds)
 [ decimal ]
  27 * begin 1 - dup while repeat drop ;

: honk ( n -- )
[ hex ]
80 pwmc c!
3c pwmc 1+ c!
4 pwms 1+ c!
8 pwmp c!
delay
0 pwmc 1+ c! ;
