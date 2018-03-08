#include <avr/sleep.h>
#include "LowPower.h"

int wakePin = 2;                 // pin used for waking up

void setup() {
  pinMode(wakePin, INPUT_PULLUP);
  attachInterrupt(0, dataCollection, LOW);
}

void loop() {
  // Only chose zero, or one option
  int option = 1;

  switch (option) {
    case 0:
      sleepInterrupt();     // sleep, but wake on interrupt
      break;
    case 1:
      sleepTime();          // sleep, but wake after 8s time
      break;
    default:
      break;
  }
}

void dataCollection() {
  // execute code here
}

void sleepInterrupt() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();          // enables the sleep bit in the mcucr register
  attachInterrupt(0, dataCollection, LOW); // use interrupt 0 on pin 2
  sleep_mode(); sleep_disable();
  detachInterrupt(0);      // disables interrupt 0 on pin 2
}

void sleepTime() {
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  dataCollection();
}

