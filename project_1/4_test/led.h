#ifndef led_included
#define  led_included

#include <msp430.h>

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

void led_init();		/* initialize LEDs */
void led_update();		/* update leds */

void blinkLim();
void green_Control(int on);
void red_Control(int on);
void blink_green();
void blink_red();
void blink_Update_Red();
void blink_Update_Green();
void wdt_init();
void time_Adv_SM_Green();
void time_Adv_SM_Red();
void s2_SM();
void blinkers_Green();
void blinkers_Red();
void change_State(short new_state);
void buzzer_Update();
void s3_SM(unsigned int input);
void s3_SM_Measures(unsigned int measures_, unsigned int notes_);
void change_Note(unsigned char new_Note);
// these are boolesan flags
extern unsigned char play_Tune, was_Pressed, gone_Once, state, led_Flags, leds_changed, green_led_state, red_led_state;
extern unsigned long frqz;

#endif
