
#ifndef _LED_H_
#define _LED_H_

enum {
	LED_RED,
	LED_GREEN,
	LED_ALL,
};

void LED_Configure(void);
void LED_toggle_red(void);
void LED_toggle_green(void);
void LED_toggle(int color);
void LED_red_on(void);
void LED_green_on(void);
void LED_red_off(void);
void LED_green_off(void);
void LED_all_toggle(void);

#endif //_LED_H_
