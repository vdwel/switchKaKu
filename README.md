# switchKaKu
Arduino library for switching with the new KaKu (Klik aan Klik uit) protocol

Switch Klik aan/Klik uit switches transmitter
Usage: switchKaku(int pin, unsigned long id, int group, int dev, bool state, int repeat)
- pin = pin number
- id = unique id of transmitter (max 4194303)
- group = between 1 and 4, 
- device = between 1 and 4, -1 switches the entire group
- state = true (on) or false (off)
- repeat = transmit repeats

