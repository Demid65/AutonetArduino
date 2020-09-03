//Color Sensor should be connected to 49(O)-53(S3)
#include <Multiservo.h>
#include <Ultrasonic.h>
char inChar;
String RegA, RegB, RegC;
int readMode = 0, ColorId, DriveMode = 0;
Multiservo srv[12];
Ultrasonic USonic(11,12);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 12; i++) {
    
    srv[i].attach(i);
 
  }
 pinMode(49,INPUT);
 pinMode(50,OUTPUT);
 pinMode(51,OUTPUT);
 pinMode(52,OUTPUT);
 pinMode(53,OUTPUT);
 pinMode(13,OUTPUT);
 pinMode(2,OUTPUT);
 digitalWrite(2,LOW);
  pinMode(8,OUTPUT);
pinMode(7,OUTPUT);
pinMode(6,OUTPUT);
pinMode(5,OUTPUT);
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
      RegA = "";
      readMode = 1;
      break;
    case ')':
      readMode = 0;
      break;
    case '[':
      RegB = "";
      readMode = 2;
      break;
    case ']':
      readMode = 0;
      break;
    case '<':
      RegC = "";
      readMode = 3;
      break;
    case '>':
      readMode = 0;
      Execute(RegA, RegB, RegC);
      break;
    default:
      switch (readMode) {
        case 1:
          RegA = RegA + inCh;
          break;
        case 2:
          RegB = RegB + inCh;
          break;
        case 3:
          RegC = RegC + inCh;
          break;
      }
      break;
  }
}

int GetHue() {
  digitalWrite(13,HIGH);
  delay(30);
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
  digitalWrite(13,LOW);
  return H;
}

int getBrightness(){
   digitalWrite(13,HIGH);
  delay(30);
  digitalWrite(50,HIGH);
  digitalWrite(51,LOW);
  digitalWrite(52, HIGH);
  digitalWrite(53, LOW);

   return 255 - pulseIn(49, LOW);
   digitalWrite(13,LOW);
}

void Execute(String A, String B, String C) {
  if (C == "Check") {
    Serial.println("OK");
  } else if (C == "SetDM") {
    DriveMode = A.toInt();
  } else if(C == "GetDM"){
    Serial.println(DriveMode);
  }else if (C == "PinMode") {
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
  } else if (C == "GetSonic") {
    Serial.println(USonic.read());
  } else if (C == "StepMotor"){
    StepMotor(A.toInt());
  } else
    Serial.println("Unknown Command " + C);
}

void StepMotor(int steps){
  //int steps = degree/7;
  if (steps>0){
  for(int i=0;i<steps;i++)
  motStep(); 
  } else {
  steps = -steps;  
  for(int i=0;i<steps;i++)
  antiStep(); 
  }
  
}


void motStep() {
 digitalWrite(8,1);
 digitalWrite(7,0);
 digitalWrite(6,1);
 digitalWrite(5,0);
 delay(10);
 digitalWrite(8,0);
 digitalWrite(7,1);
 digitalWrite(6,1);
 digitalWrite(5,0);
 delay(10);
 digitalWrite(8,0);
 digitalWrite(7,1);
 digitalWrite(6,0);
 digitalWrite(5,1);
 delay(10);
 digitalWrite(8,1);
 digitalWrite(7,0);
 digitalWrite(6,0);
 digitalWrite(5,1);
 delay(10);
 digitalWrite(8,1);
 digitalWrite(7,0);
 digitalWrite(6,1);
 digitalWrite(5,0);
/* digitalWrite(8,1);
 digitalWrite(7,0);
 digitalWrite(6,0);
 digitalWrite(5,0);
 delay(10);
 digitalWrite(8,1);
 digitalWrite(7,0);
 digitalWrite(6,1);
 digitalWrite(5,0);
 delay(10);
 
 digitalWrite(8,0);
 digitalWrite(7,0);
 digitalWrite(6,1);
 digitalWrite(5,0);
 delay(10);
 digitalWrite(8,0);
 digitalWrite(7,1);
 digitalWrite(6,1);
 digitalWrite(5,0);
 delay(10);

 digitalWrite(8,0);
 digitalWrite(7,1);
 digitalWrite(6,0);
 digitalWrite(5,0);
 delay(10);
 digitalWrite(8,0);
 digitalWrite(7,1);
 digitalWrite(6,0);
 digitalWrite(5,1);
 delay(10);
 
 digitalWrite(8,0);
 digitalWrite(7,0);
 digitalWrite(6,0);
 digitalWrite(5,1);
 delay(10);
 digitalWrite(8,1);
 digitalWrite(7,0);
 digitalWrite(6,0);
 digitalWrite(5,1);
 delay(10);

 digitalWrite(8,0);
 digitalWrite(7,0);
 digitalWrite(6,0);
 digitalWrite(5,0);*/
}

void antiStep() {
 digitalWrite(8,1);
 digitalWrite(7,0);
 digitalWrite(6,0);
 digitalWrite(5,1);
 delay(10);
 digitalWrite(8,0);
 digitalWrite(7,0);
 digitalWrite(6,0);
 digitalWrite(5,1);
 delay(10);
 
 digitalWrite(8,0);
 digitalWrite(7,1);
 digitalWrite(6,0);
 digitalWrite(5,1);
 delay(10);
  digitalWrite(8,0);
 digitalWrite(7,1);
 digitalWrite(6,0);
 digitalWrite(5,0);
 delay(10);

 digitalWrite(8,0);
 digitalWrite(7,1);
 digitalWrite(6,1);
 digitalWrite(5,0);
 delay(10);
 digitalWrite(8,0);
 digitalWrite(7,0);
 digitalWrite(6,1);
 digitalWrite(5,0);
 delay(10);

 digitalWrite(8,1);
 digitalWrite(7,0);
 digitalWrite(6,1);
 digitalWrite(5,0);
 delay(10);
  digitalWrite(8,1);
 digitalWrite(7,0);
 digitalWrite(6,0);
 digitalWrite(5,0);
 delay(10);

  digitalWrite(8,0);
 digitalWrite(7,0);
 digitalWrite(6,0);
 digitalWrite(5,0);
}
