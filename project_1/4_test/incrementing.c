//Initial test for just the LEDs make Red LED on and Green blink
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "incrementing.h"
#include "buzzer.h"
unsigned char state_Note = 1;
unsigned char measures = 1;

void wdt_init(){
  
  configureClocks();
  enableWDTInterrupts();

}

static int blinkLimit = 3;
void blink_Update_Red(){
  static int blinkCount_g = 0;
  blinkCount_g--;
  if(blinkCount_g <= blinkLimit){
    blinkCount_g=7;
    //P1OUT &= ~BIT0;
    red_Control(1);
  } else {
    //P1OUT &= ~BIT0;
    red_Control(0);
  }
}

void blink_Update_Green(){
  static int blinkCount_r = 0;
  blinkCount_r++;
  if(blinkCount_r >= blinkLimit){
    blinkCount_r = 0;
    //P1OUT &= ~BIT6;
    green_Control(1);
  } else {
    //P1OUT &= ~BIT6;
    green_Control(0);
  }
}

void blink_green(){ //controls and calls the 2 updates for green and red led
  blink_Update_Red(); //self explanatory
  
}

void blink_red(){
  blink_Update_Green();// self explanatory
}

void green_Control(int on){ //control red LED
  if(on){
    P1OUT |= LED_RED;
  } else{
    P1OUT &= ~LED_RED;
  }
}

void red_Control(int on){ //controls green LED
  if(on){
    P1OUT |= LED_GREEN;
  } else{
    P1OUT &= ~LED_GREEN;
  }
}

void second_Update(){ //called 250 times per second 250 calls/ 1 sec = 1 call = 1/250sec
  static int countsec = 0;
  countsec++;
  if(countsec >= 250){ 
    countsec = 0;
    blink_Lim();
  }
}
static unsigned int notes = 0;
static unsigned int measure = 1;
void timing_BPM(){ //240 BPM more or less
  static int change_notes = 0;
  change_notes++;
  if(change_notes >= 32){//increment eighth notes
    change_notes = 0;
    notes++;
    if(notes >= 9){//controls where beat is
      notes = 0;
      measures++;
      if(measures >= 5){//controls which measure is played
	measures = 1;
      }
    }
    s3_SM_Measures(measures,notes);
   }
}
void blink_Lim(){
  blinkLimit++;
  if(blinkLimit >= 8)
    blinkLimit= 0;
}

void time_Adv_SM_Green(){
  blink_green(); // handles green LED statemachines
  second_Update(); // updates seconds same clock as red
}
void time_Adv_SM_Red(){
  blink_red();//handles red LED statemachine
  second_Update(); // updates seconds same clock as green
}

