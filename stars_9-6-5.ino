/******************************************************************************
*
* Автор SerGO 
* sergo83@mail.ru
*
*******************************************************************************/
#include <Adafruit_NeoPixel.h>

#define PIN 5

#define LEN_ROW 5    // кол-во точек в луче
#define LEN_STAR 31  // кол-во точек в звезде
#define NUM_ROW  6   //кол-во лучей в звезде
#define NUM_STARS 9  //кол-во звезд в гирлянде
#define MAX_LEDS 280 //количство светодидов в ленте

int cnt_j, cnt_i,cnt_k, num_kadr, stage;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(MAX_LEDS, PIN, NEO_KHZ800+NEO_GRB);

void setup() {
  strip.begin();
}

void loop() {
  unsigned char i;

  for (i = 0; i<6; i++) { effect008();}  dimmer_off();
  for (i = 0; i<6; i++) { effect007();}  dimmer_off();
  for (i = 0; i<6; i++) { effect006();}  dimmer_off();
  for (i = 0; i<6; i++) { effect005();}  dimmer_off();
  for (i = 0; i<20; i++) { effect004();}  dimmer_off();
  for (i = 0; i<300; i++) { effect003();}  dimmer_off();
  for (i = 0; i<100; i++) { test_spinner_spiral_dot();}  dimmer_off();
  for (i = 0; i<10; i++) { effect001();}  dimmer_off();
  for (i = 0; i<10; i++) { effect002();}  dimmer_off();
}
