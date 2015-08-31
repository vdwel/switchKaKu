/*  Switch Klik aan/Klik uit switches transmitter
 *  Usage: switchKaku(int pin, unsigned long id, int group, int dev, bool state, int repeat)
 *  pin = pin number
 *  id = unique id of transmitter (max 4194303)
 *  group = between 1 and 4, 
 *  device = between 1 and 4, -1 switches the entire group
 *  state = true (on) or false (off)
 *  repeat = transmit repeats
 */
 #include "switchKaKu.h"
 
void switchKaku(int pin, unsigned long id, int group, int dev, bool state, int repeat){
  if (dev == -1){
    dev = 1<<5;
  } else {
    dev -= 1;
  }
  sendKakuCode(pin, (((id<<8|dev)|state<<4)|1<<7)|(group-1)<<2, repeat);  
}

void sendKakuCode(int pin, unsigned long code, int repeat){
  int period = 230;
  pinMode(pin, OUTPUT);
  for (int j = 0; j < repeat; j++){
    //Send sync
    digitalWrite(pin, LOW);
    delayMicroseconds(47*period);
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);
    digitalWrite(pin, LOW);
    delayMicroseconds(period*12);
    //Send code  
    for (int i = 31; i>=0; i--){
      sendBit(code & (1<<i), pin, period);
    }
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);    
    digitalWrite(pin, LOW);
    //Serial.println("");
  }
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
  } else {
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);
    digitalWrite(pin, LOW);
    delayMicroseconds(period*6);
    digitalWrite(pin,HIGH);
    delayMicroseconds(period);
    digitalWrite(pin, LOW);
    delayMicroseconds(period*1.4);
    
  }
}