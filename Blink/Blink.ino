/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(8, OUTPUT);
   pinMode(6, OUTPUT);
   pinMode(7, OUTPUT);
   
   Serial.begin(9600);
 

}

// the loop function runs over and over again forever
void loop() {
  int value = analogRead(1);
  
  if (value > 200)
     digitalWrite(7, LOW); 
   else
    digitalWrite(7, HIGH); 
  Serial.println(value, DEC);
  /*digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(6, LOW);
  delay(1000);              // wait for a second
  digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(6, HIGH);
  delay(1000);              // wait for a second */
}
