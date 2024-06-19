#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "incrementing.h"
#include "led.h"
#include "switches.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 2;		/* one half cycle */
}

void
measure_1(unsigned int notes_){
  static unsigned int notes_play = 1;
  switch(notes_){
  case 1:
    notes_play = 1;
    s3_SM(notes_play);
    break;

  case 2:
    notes_play = 1;
    s3_SM(notes_play);
    break;
  case 3:
    notes_play = 6;
    s3_SM(notes_play);
    break;

  case 4:
    notes_play = 1;
    s3_SM(notes_play);
    break;

  case 5:
    //notes_play = 0;
    // s3_SM(notes_play);
    notes_play = 1;
    s3_SM(notes_play);
    break;

  case 6:
    notes_play = 5;
    s3_SM(notes_play);
    break;
    
  case 7:
    notes_play = 1;
    s3_SM(notes_play);
    break;
    
  case 8:
    //notes_play = 0;
    //s3_SM(notes_play);
    notes_play = 1;
    s3_SM(notes_play);
    break;
    
  default:
    buzzer_set_period(F_3);
  } 
}

void
measure_2(unsigned int notes_){
  static unsigned int notes_play = 1;
  switch(notes_){

  case 1:
    notes_play = 4;
    s3_SM(notes_play);
    break;

  case 2:
    notes_play = 1;
    s3_SM(notes_play);
    break;

  case 3:
    //notes_play = 0;
    //s3_SM(notes_play);
    notes_play = 1;
    s3_SM(notes_play);
    break;

  case 4:
    notes_play = 3;
    s3_SM(notes_play);
    break;

  case 5:
    notes_play = 1;
    s3_SM(notes_play);
    break;

  case 6:
    //notes_play = 0;
    //s3_SM(notes_play);
    notes_play = 1;
    s3_SM(notes_play);
    break;

  case 7:
    notes_play = 2;
    s3_SM(notes_play);
    break;

  case 8:
    notes_play = 3;
    s3_SM(notes_play);
    break;

  default:
    buzzer_set_period(F_3);
    break;
  }
} 

void
measure_3(unsigned int notes_){
  static unsigned int notes_play = 1;
  switch(notes_){
    case 1:
      notes_play = 4;
      s3_SM(notes_play);
      break;

    case 2:
      notes_play = 1;
      s3_SM(notes_play);
      break;

    case 3:
      notes_play = 0;
      s3_SM(notes_play);
      notes_play = 1;
      s3_SM(notes_play);
      break;

    case 4:
      notes_play = 3;
      s3_SM(notes_play);
      break;

    case 5:
      notes_play = 3;
      s3_SM(notes_play);
      break;

    case 6:
      notes_play = 3;
      s3_SM(notes_play);
      break;

    case 7:
      notes_play = 3;
      s3_SM(notes_play);
      break;

    case 8:
      notes_play = 3;
      s3_SM(notes_play);
      break;

    default:
      buzzer_set_period(F_3);
      break;
    } 
}
