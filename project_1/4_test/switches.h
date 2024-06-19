#ifndef switches_included
#define switches_included

#define SW1 BIT3		/* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */
#define EXP_SWITCH (BIT0 | BIT1 | BIT2 | BIT3)
#define S1 BIT0
#define S2 BIT1
#define S3 BIT2
#define S4 BIT3

void switch_init();
void switch_init_2();
void switch_interrupt_handler();
void switch_sense();

extern char switch_state_down, switch_state_changed; /* effectively boolean */

#endif // included
