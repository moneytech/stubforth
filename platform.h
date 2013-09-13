#ifndef PLATFORM_H
#define PLATFORM_H

#include "symbols.h"
#include "stubforth.h"

static void ehex(int);

void warmstart(void) {
      led_dsl(2);
      led_chan1(2);
      led_chan2(2);
      my_puts("warmstart...\n");
      asm (" mov.l .restart, r1");
/*       asm (" jmp @r1"); */
      asm (" ldc r1, spc");
      asm (" rte");
      asm (" nop");
      asm (" .align 2");
      asm (".restart:");
      asm (" .long _restart");
}


__attribute__((interrupt_handler))
__attribute__((section(".interrupt_handler")))
void interrupt_handler (void) {
  (void) INTEVT; /* bits 11-0 */
  my_puts("x_x interrupt_handler x_x \n\r");
  my_puts("INTEVT:");
  ehex(*INTEVT);
  my_puts("\n\r");
  warmstart();
}

__attribute__((interrupt_handler))
__attribute__((section(".exception_handler")))
void exception_handler (void) {

  my_puts("x_x exception_handler x_x\n\r");
  my_puts("EXPEVT:");
  ehex(*EXPEVT);
  my_puts("\n\r");
  warmstart();
}

static int lowest_bit_set (int value) {
  int i;
  for (i=0; (i<32) && !(1 & value); i++)
    value>>=1;
  return i;
}

void set_vbr(void *addr) {
  asm("ldc %0, vbr" : /* no outputs */ : "r"(addr));
}

void led_pwr(int new) {
  int state = *LED18;
  state &= ~LED1_MASK;
  state |= new << lowest_bit_set(LED1_MASK);
  *LED18 = state;
}


void led_dsl(int new) {
  int state = *LED18;
  state &= ~LED8_MASK;
  state |= new << lowest_bit_set(LED8_MASK);
  *LED18 = state;
}

int led34_state;

void led_chan1(int new) {
  led34_state &= ~LED3_MASK;
  led34_state |= new << lowest_bit_set(LED3_MASK);
  *LED34 = led34_state;
}

void led_chan2(int new) {
  led34_state &= ~LED4_MASK;
  led34_state |= new << lowest_bit_set(LED4_MASK);
  *LED34 = led34_state;
}

/* flags.break_condition can be set in an ISR to interrupt the
   interpreter. */

extern void vector_base;

static void initio()
{

  set_vbr(&vector_base);

  led_pwr(0);
  led_dsl(0);
  led_chan1(0);
  led_chan2(0);

  *SCSCR = 0x31;

  *SCSSR = 0;

/*               Initialize */
/* Clear TE and RE bits in SCSCR to 0 */

  *SCSCR &= ~0x30;

/* Set CKE1 and CKE0 bits in SCSCR */
/*        (TE and RE bits are 0)        (1) */
  *SCSCR = 0x01;


/*       Select transmit/receive        (2) */
/*          format in SCSMR */
  *SCSMR = 0;


/*         Set value to SCBRR           (3) */
  *SCBRR = 0x5;


/*                             Wait */
/*             Has a 1-bit            No */
/*          interval elapsed? */
/*                      Yes */
  { int i=0;
    while (i++ < 10000) {
      *LED18 = 0x10;
      *LED18 = 0x20;
    }
  }

/*  Set TE and RE bits in SCSCR to 1 */
/*  and set RIE, TEIE, and MPIE bits    (4) */


  *SCSCR |= 0x30;

/*                 End */


}

int putchar(int c) {

  char status;

  led_dsl(2);
  do {
    status = *SCSSR;
  } while (! (TDRE & status));

  *SCTDR = c;
  status &= ~TDRE;
  *SCSSR = status;

  if (!terminal.raw)
    if (c == '\n')
      putchar('\r');

  led_dsl(0);

  return c;
}

static void ehex(int i) {
  const char *hexchars="0123456789abcdefghijklmnopqrstuvwxyz";
  if(i) {
    ehex(i>>4);
    putchar(hexchars[0xf & i]);
  }
}

int getchar(void) {
  char status;
  int data;

  led_dsl(1);

  while (1) {
    status = *SCSSR;

    if ((ORER|FER|PER) & status) {
      *SCSSR &= ~(ORER|FER|PER);
      continue;
    }

    if (RDRF & status)
      break;
  }

  data = *SCRDR;
  *SCSSR &= ~RDRF;


  if (!terminal.raw) {
    if (data == 3) {
      warmstart();
    }
    if (data == '\r')
      data = '\n';
  }
  if (!terminal.quiet)
    putchar(data);

  led_dsl(0);

  return data;
}

#endif
