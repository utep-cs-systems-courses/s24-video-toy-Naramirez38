#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

char blue = 31, green = 0, red = 31;
unsigned char step = 0;
unsigned int clear, states = 0;
static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches = 0;

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}
void
switch_interrupt_handler()

// axis zero for col, axis 1 for row

short drawPos[2] = {1,10}, controlPos[2] = {2, 10};
short colVelocity = 1, colLimits[2] = {1, screenWidth/2};

void
draw_ball(int col, int row, unsigned short color)
{
  fillRectangle(col-1, row-1, 3, 3, color);
}


void
screen_update_ball()
{
  for (char axis = 0; axis < 2; axis ++) 
    if (drawPos[axis] != controlPos[axis]) /* position changed? */
      goto redraw;
  return;			/* nothing to do */
 redraw:
  draw_ball(drawPos[0], drawPos[1], COLOR_BLACK); /* erase */
  for (char axis = 0; axis < 2; axis ++) 
    drawPos[axis] = controlPos[axis];
  draw_ball(drawPos[0], drawPos[1], COLOR_WHITE); /* draw */
}
  

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 25) {		/* 10/sec */
   
    {				/* move ball */
      short oldCol = controlPos[0];
      short newCol = oldCol + colVelocity;
      if (newCol <= colLimits[0] || newCol >= colLimits[1])
	colVelocity = -colVelocity;
      else
	controlPos[0] = newCol;
    }

    {				/* update hourglass */
      if (switches & SW3) {states = 3;}//green = (green + 1) % 64;
      if (switches & SW2) {states = 2;}//blue = (blue + 2) % 32;
      if (switches & SW1) {states = 1;}//red = (red - 3) % 32;
      if (step <= 35)
	step ++;
      else
	step = 0;
      secCount = 0;
    }
    if (switches & SW4) {states = 6;}//return;
    redrawScreen = 1;
  }
}
  
void update_shape();

void main()
{
  
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}
void
screen_update_hourglass()
{
  static unsigned char row = screenHeight / 2, col = screenWidth / 2;
  static char lastStep = 0;
  
  if (step == 0 || (lastStep > step)) {
    clearScreen(COLOR_BLUE);
    lastStep = 0;
  } else {
    for (; lastStep <= step; lastStep++) {
      int startCol = col - lastStep;
      int endCol = col + lastStep;
      int width = 1 + endCol - startCol;
      
      // a color in this BGR encoding is BBBB BGGG GGGR RRRR
      unsigned int color = (blue << 11) | (green << 5) | red;
      
      fillRectangle(startCol, row+lastStep, width, 1, color);
      fillRectangle(startCol, row-lastStep, width, 1, color);
    }
  }
}  

void
screen_update_square_down(){
  static unsigned char row = screenHeight / 2-15, col = (screenWidth/2)-17;
  static char lastStep = 0;
  if (step == 0 || (lastStep > step)){
    clearScreen(COLOR_BLACK);
    lastStep = 0;
  } else{
    for(; lastStep <= step-2; lastStep++){
      int startCol = col - lastStep;
      int endCol = col + lastStep;
      int width = 37;//1 + endCol - startCol;

      unsigned int color = ((blue << 2) | (green <<8)) | red;

      fillRectangle(col,row+lastStep,width,1,COLOR_ORANGE);
    }
  }
}
void
screen_update_square_side(){
  static unsigned char row = screenHeight/2-15, col = (screenWidth/2)-17;
  static char lastStep = 0;
  if(step == 0 ||(lastStep > step)){
    //clearScreen(COLOR_BLACK);
    lastStep = 0;
  } else {
    for(; lastStep <= step; lastStep++){
      int width = 1;
      int height = 35;
      unsigned int color = ((blue<<2)|(green<<7)|red);
      fillRectangle(col+lastStep,row,width,height,color);
      
    }
  }
}
void
box_clear(){
  clear--;
  static unsigned char row = (screenHeight/2)-15, col = (screenWidth/2)+19;
  static char lastStep = 0;
  if(step == 0 ||(lastStep > step)){
    lastStep = 0;
    } else {
    for(; lastStep <= step; lastStep++){
      int width = 1;
      int height = 35;
      unsigned int color = ((blue<<2)|(green<<7)|red);
      fillRectangle(col-lastStep,row,width,height,COLOR_WHITE);
    }
  }
}
void
update_shape()
{
  draw_SM(states);
  //screen_update_ball();
  //screen_update_hourglass();
  //screen_update_square_down();
  //box_clear();
  //screen_update_square_side();
}

void
draw_SM(unsigned int states_){
  unsigned int states = states_;

  switch(states){
  case 1:
    clearScreen(COLOR_BLACK);
    break;
  case 2:
    screen_update_hourglass();
    break;
  case 3:
    screen_update_ball();
    break;
  case 4:
    screen_update_square_side();
    break;
  case 5:
    screen_update_square_down();
    break;
  case 6:
    box_clear();
    break;
    
  default:
    clearScreen(COLOR_YELLOW);
    break;


  }
}


void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
