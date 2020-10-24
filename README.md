# AutonetArduino
 Arduino Software for Autonet 14+ Competition made by 1932 team.
 
 ## Installation
 1. Get yourself an Arduino Mega 2560 or similar
 2. Upload software trough Arduino IDE
 3. Use Arduino IDE built-in serial monitor to send `<Check>` command. If the respond is `OK` then software uploaded correctly.
 4. ???
 5. PROFIT!
 
 ## Usage
 AutonetArduino allows usage of three registers to control Arduino's GPIO, any string of characters can be send into any registes.
 If a chunck of text recieved by Arduino is incapsulated in \(round brackets\) it is saved into register A, which is used as Value register.
 If a chunck of text recieved by Arduino is incapsulated in \[square brackets\] it is saved into register B, which is used as Destination register.
 If a chunck of text recieved by Arduino is incapsulated in <triangle brakets> it is saved into register C, which is used as Operation register and parsed as a command.
 
 Examples:
 `(255)[8]<AnalogWrite>` Gets interpreted as `analogWrite(8,255);` and sends 5V on pin 8
 `[0]<AnalogRead>` Gets interpreted as `analogRead(0)`; and reads analog value from pin A0 to then send it back.
Returned value has no formatting and sent as just a number.
 Please note, that sending messages with unbalanced brackets may lead to unexpected behavior.
 
 ## Implemented commands
 ### Native Arduino IDE
 + `(Mode)[Pin]<PinMode>`
 + `(Value)[Pin]<DigitalWrite>`
 + `[Pin]<DigitalRead>`
 + `(Value)[Pin]<AnalogWrite>`
 + `[AnalogPin]<AnalogRead>`
 ### Custom
 + `<Check>`
 + `(Angle)[Servo]<SetServo>`
 + `<GetHue>`
 + `<GetSonic>`
 + ~~`(Steps)<StepMotor>`~~ stepmotor support removed
 + `<GetDM>` `<SetDM>` - Drivemode concept is unused currently.
