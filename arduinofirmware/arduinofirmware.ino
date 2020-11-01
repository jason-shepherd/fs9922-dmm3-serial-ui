#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 4);

int Byte;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial) {
    ;
  }

  mySerial.begin(2400);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySerial.available()) {
    Byte = mySerial.read();
    Serial.println(Byte, BIN);
  }
}
