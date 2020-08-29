#include <pt6311.h>

pt6311 VFD(10,12);

void setup() {
  delay(200);
//Serial.begin(9600);
 // VFD.writeChar(1, 'C');
}

void loop() {
  for(int i=0; i<5; i++){
    static bool b = false;
    VFD.ledWrite(i, b);
    b = !b;
  }
  for(int i = 0; i<12; i++){
  VFD.writeChar(7, 'A');
  }

delay(100);

}
