/*  Switch Klik aan/Klik uit switches transmitter
 *  Usage: switchKaku(int pin, unsigned long id, int group, int dev, bool state, int repeat)
 *  pin = pin number
 *  id = unique id of transmitter (max 4194303)
 *  group = between 1 and 4, 
 *  device = between 1 and 4, -1 switches the entire group
 *  state = true (on) or false (off)
 *  repeat = transmit repeats
 *  dimlevel = -1 (no dimmer), between 0 and 15 for the dimlevel
 */
 #include "switchKaKu.h"
 
void switchKaku(int pin, unsigned long id, int group, int dev, bool state, int repeat, int dimlevel){
  if (dev == -1){
    dev = 1<<5;
  } else {
    dev -= 1;
  }
  if (dimlevel > -1) {
  sendKakuCode(pin, (((id<<8|dev)|state<<4)|1<<7)|(group-1)<<2, repeat);
  } else {
  sendKakuDimCode(pin, ((((id<<8|dev)|state<<4)|1<<7)|(group-1)<<2)<<4|dimlevel, repeat);
  }
}

void sendKakuCode(int pin, unsigned long code, int repeat){
  int period = 230;
  pinMode(pin, OUTPUT);
  for (int j = 0; j < repeat; j++){
    sendSyc(pin, period);
    for (int i = 31; i>=0; i--){
      sendBit(code & (1<<i), pin, period);
    }
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);    
    digitalWrite(pin, LOW);
  }
}

void sendKakuDimCode(int pin, unsigned long code, int repeat){
  int period = 230;
  pinMode(pin, OUTPUT);
  for (int j = 0; j < repeat; j++){
    sendSyc(pin, period);  
    for (int i = 35; i>=0; i--){
      if (i == 27) {
      sendBit(-1, pin, period);
      } else {
      sendBit(code & (1<<i), pin, period);
    }
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);    
    digitalWrite(pin, LOW);
    //Serial.println("");
  }
}


void sendSyc(int pin, int period){
	digitalWrite(pin, LOW);
    delayMicroseconds(47*period);
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);
    digitalWrite(pin, LOW);
    delayMicroseconds(period*12);

}

void sendBit(int value, int pin, int period){
  if (value == 0){
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);
    digitalWrite(pin, LOW);
    delayMicroseconds(period*1.4);
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);
    digitalWrite(pin, LOW);
    delayMicroseconds(period*6);
  } else if (value == 1) {
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);
    digitalWrite(pin, LOW);
    delayMicroseconds(period*6);
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);
    digitalWrite(pin, LOW);
    delayMicroseconds(period*1.4);
  } else {
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);
    digitalWrite(pin, LOW);
    delayMicroseconds(period*1.4);
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);
    digitalWrite(pin, LOW);
    delayMicroseconds(period*1.4);
  }
}