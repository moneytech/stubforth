decimal
lxmax @ 160 16 << or lxmax !
lymax @ 240 16 << or lymax !
160 16 / lvpw c!
8 lpicf c!
0 lrra c!

0 pcsel c!

hex

: lcdon
  80 lckcon c!
  1 6 << dup pfdir set pfdata set
;

: lcdoff
  1 6 << pfdata clear
  0 lckcon c!
;

lcdon

: dac
3 4 << dup dup pfdir set
pfdata set pfdata clear
1 5 <<
begin
dup pfdata set
dup pfdata clear
swap 1 - swap 1 pick
0 < until ;

10 dac

: fb lssa @ ;
: test fb 1300 1 fill ;
: cls fb 1300 0 fill ;

decimal
160 constant xdim
240 constant ydim
hex

: pxaddr ( x y -- c a )
[ hex ]
xdim * over + 3 >> fb +
swap
7 and 80 swap >>
swap ;

: setp  ( x y -- )
pxaddr set ;

: clp  ( x y -- )
pxaddr clear ;

: getp ( x y -- n )
pxaddr c@ and ;

: sq dup * ;

hex
8fff variable max_abs
10 variable max_iter
10 variable shift

: csq ( r i -- r i )
over sq over sq - a >>
>r * 9 >> r> swap ;

: c+ ( r i r i -- r i )
swap >r + swap r> + swap ;

: zn ( cr ci zr zi )
csq >r >r 2dup r> r> c+ ;

: zabs ( r i -- n )
dup 0 < if minus then swap
dup 0 < if minus then + ;

: divp ( cr ci -- n)
0 >r 0 0 begin
zn
2dup zabs max_abs @ > if drop drop drop drop r> exit then
r> 1+ dup >r max_iter @ > if drop drop drop drop r> drop 0 exit then
again ;

: mset2nd
xdim 1- begin
." ."
ydim 1- begin
2dup
2 << swap 2 << swap
divp
0= if 2dup setp then
1- dup 0= until drop
1- dup 0= until drop
;

: mset
xdim 1- begin
." ."
ydim 1- begin
2dup
ydim 1 >> -
ydim 2 >> - c *
swap xdim 1 >> - c *
divp
0= if 2dup setp then
1- dup 0= until drop
1- dup 0= until drop
;
