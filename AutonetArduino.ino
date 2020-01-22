//Color Sensor should be connected to 49(O)-53(S3)
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

int GetHue() {
  digitalWrite(50,HIGH);
  digitalWrite(51,LOW);
  digitalWrite(52, LOW);
  digitalWrite(53, LOW);
  int R = 255 - pulseIn(49, LOW);
  digitalWrite(52, HIGH);
  digitalWrite(53, HIGH);
  int G = 255 - pulseIn(49, LOW);
  digitalWrite(52, LOW);
  digitalWrite(53, HIGH);
  int B = 255 - pulseIn(49, LOW);
  int V = max(R, max(G, B));
  int M = min(R, min(G, B));

  int H = 0;

  if (V == R && G >= B) {
    H = 60 * (G - B) / (V - M);
  } else if (V == R && G < B) {
    H = 60 * (G - B) / (V - M) + 360;
  } else if (V == G) {
    H = 60 * (B - R) / (V - M) + 120;
  } else if (V == B) {
    H = 60 * (R - G) / (V - M) + 240;
  }
  return H;
}

void Execute(String A, String B, String C) {
  if (C == "Check") {
    Serial.println("OK");
  } else if (C == "SetDM") {
    DriveMode = A.toInt();
  } else if (C == "PinMode") {
    pinMode(B.toInt(), A.toInt());
  } else if (C == "DigitalWrite") {
    digitalWrite(B.toInt(), A.toInt());
  } else if (C == "AnalogWrite") {
    analogWrite(B.toInt(), A.toInt());
  } else if (C == "AnalogRead") {
    Serial.println(analogRead(B.toInt()));
  } else if (C == "DigitalRead") {
    Serial.println(digitalRead(B.toInt()));
  } else if (C == "SetServo") {
    srv[B.toInt()].write(A.toInt());
  } else if (C == "GetHue") {
    Serial.println(GetHue());
  } else
    Serial.println("Unknown Command " + C);
}
