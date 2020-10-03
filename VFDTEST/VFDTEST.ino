#include <pt6311.h>

//Call the constructor for the PT6311-class
pt6311 VFD(10,12);

void setup() {
  delay(200);
  Serial.begin(9600);
}
void loop() {
  //print text
  VFD.clearBuffer();
  VFD.print(0, "Test Message");
  delay(1000);

  //Read and print high inputs
  VFD.clearBuffer();
  uint8_t curPos = 0;
  for(int i = 1; i<5; i++){
    if(!VFD.switchRead(i)){
      VFD.writeChar(curPos, '0'+i);
      Serial.print(i);
      Serial.println(" Pressed");
      curPos+=2;
    }
  }
  VFD.writeLine();
  Serial.println();
  delay(1000);

  //Read and print pressed keys
  VFD.clearBuffer();
  VFD.readKeypad();
  VFD.setCursor(0);
  for(int i = 33; i<49; i++){
    if(VFD.isPressed(i)){
      Serial.print(i);
      Serial.println(" key is pressed");
    }
  }
  Serial.println();

  //Turn all segments on
  VFD.clearBuffer();
  for(int i = 0; i<12; i++){
  VFD.writeChar(i,0x7F); 
  }
  VFD.writeLine();
  delay(1000);
  
  //Flash LED's
  static bool b = false;
  b = !b;
  for(int i=0; i<6; i++){
    VFD.ledWrite(i,b);
    b = !b;
  }
}
