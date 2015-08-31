
/* This example switches KaKu device op pin 4
 * every 5 seconds on/off
 * device id = 1 and group id = 1
 * unique id of the simulated transmitter is 1234
 */

#include "switchKaKu.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  switchKaku(4, 1234, 1, 1, true, 3);
  delay(5000);
  switchKaku(4, 1234, 1, 1, false, 3);
  delay(5000);
}

