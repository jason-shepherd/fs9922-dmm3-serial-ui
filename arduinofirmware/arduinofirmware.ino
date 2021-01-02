#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4);

int Byte;

void setup() {
  // put your setup code here, to run once:
  pinMode(3, INPUT);
  Serial.begin(2400);
  while(!Serial) {
    ;
  }

  mySerial.begin(2400);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mySerial.available()) {
    Byte = mySerial.read();
    Serial.write(Byte);
  }
  //Serial.println(digitalRead(3));
}
