#include <Multiservo.h>
char inChar;
String BufferA, BufferB, BufferC;
int readMode = 0, ColorId, DriveMode = 0;
Multiservo srv[12];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 12; i++) {

    srv[i].attach(i);

  }
}

void loop() {


  if (Serial.available()) {
    inChar = Serial.read();
    ProcessIn1(inChar);

  }
}
void ProcessIn1(char inCh) {
  switch (inCh) {
    case '(':
      BufferA = "";
      readMode = 1;
      break;
    case ')':
      readMode = 0;
      break;
    case '[':
      BufferB = "";
      readMode = 2;
      break;
    case ']':
      readMode = 0;
      break;
    case '<':
      BufferC = "";
      readMode = 3;
      break;
    case '>':
      readMode = 0;
      Execute(BufferA, BufferB, BufferC);
      break;
    default:
      switch (readMode) {
        case 1:
          BufferA = BufferA + inCh;
          break;
        case 2:
          BufferB = BufferB + inCh;
          break;
        case 3:
          BufferC = BufferC + inCh;
          break;
      }
      break;
  }
}

void Execute(String A, String B, String C) {
  if (C == "Check") {
    Serial.println("OK");
  } else
  if (C == "SetDM") {
    DriveMode = A.toInt();
  } else
  if (C == "PinMode") {
    pinMode(B.toInt(), A.toInt());
  } else
  if (C == "DigitalWrite") {
    digitalWrite(B.toInt(), A.toInt());
  } else
  if (C == "AnalogWrite") {
    analogWrite(B.toInt(), A.toInt());
  } else
  if (C == "AnalogRead") {
    Serial.println(analogRead(B.toInt()));
  } else
  if (C == "DigitalRead") {
    Serial.println(digitalRead(B.toInt()));
  } else
  if (C == "SetServo") {
    srv[B.toInt()].write(A.toInt());
  } else
  Serial.println("Unknown Command "+C);
}
