.( Loading reprap.4th...) lf

hex

\ stepper z
	
f gpiodr8r pd !
f gpioden pd !
f gpiodir pd !
: sz gpiodata pd f 2 << + ! ;

\ stepper x
	
f0 gpiodr8r pc !
f0 gpioden pc !
f0 gpiodir pc !
: sx 4 << gpiodata pc f0 2 << + ! ;

\ stepper y
	
f gpiodr8r pb !
f gpioden pb !
f gpiodir pb !
: sy gpiodata pb f 2 << + ! ;

\ stepper e
	
f gpiodr8r pe !
f gpioden pe !
f gpiodir pe !
: se gpiodata pe f 2 << + ! ;

\ current half-step (0..7)
variable xpos
variable ypos
variable zpos
variable epos

: halfstep ( 0..7 -- 0..16 )
	7 and
	case
		0 of 1 endof
		1 of 3 endof
		2 of 2 endof
		3 of 6 endof
		4 of 4 endof
		5 of c endof
		6 of 8 endof
		7 of 9 endof
	endcase
;

: next @ 1+ dup halfstep swap ;
: prev @ 1- dup halfstep swap ;

: x+ xpos next xpos ! sx ;
: x- xpos prev xpos ! sx ;

: y+ ypos next ypos ! sy ;
: y- ypos prev ypos ! sy ;

: z+ zpos next zpos ! sz ;
: z- zpos prev zpos ! sz ;

: e+ epos next epos ! se ;
: e- epos prev epos ! se ;

: xc xpos @ halfstep sx ;
: yc ypos @ halfstep sy ;
: ec epos @ halfstep se ;

: zc zpos @ 7 swap - halfstep sz ;

: off 0 sx 0 sy 0 sz 0 se ;
: on xc yc zc ec ;

: xmove ( pos -- )
	begin
		dup xpos @
		= 0= while
		dup xpos @ > if
			1 xpos +!
		else
			-1 xpos +!
		then
		xc
		8 ms
    repeat drop ;

: ymove ( pos -- )
	begin
		dup ypos @
		= 0= while
		dup ypos @ > if
			1 ypos +!
		else
			-1 ypos +!
		then
		yc
		8 ms
    repeat drop ;

: zmove ( pos -- )
	begin
		dup zpos @
		= 0= while
		dup zpos @ > if
			1 zpos +!
		else
			-1 zpos +!
		then
		zc
		10 ms
    repeat drop ;