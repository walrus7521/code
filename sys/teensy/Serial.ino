/* LED Blink, Teensyduino Tutorial #1
   http://www.pjrc.com/teensy/tutorial.html
   https://www.pjrc.com/teensy/td_serial.html
 
   This example code is in the public domain.
*/

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.0 has the LED on pin 13
const int ledPin = 13;

// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  Serial.begin(9600); // USB is always 12 Mbit/sec
  pinMode(ledPin, OUTPUT);
}

// the loop() methor runs over and over again,
// as long as the board has power

void loop() {
  unsigned char incomingByte;
  //digitalWrite(ledPin, HIGH);   // set the LED on
  //delay(1000);                  // wait for a second
  //digitalWrite(ledPin, LOW);    // set the LED off
  delay(1000);                  // wait for a second
  Serial.println("Hello World...");
  if (Serial.available()) {
    incomingByte = Serial.read();  // will not be -1
    if (incomingByte == 'a') {
        digitalWrite(ledPin, HIGH);   // set the LED on
    } else if (incomingByte == 'b') {
        digitalWrite(ledPin, LOW);   // set the LED on
    } else {
      Serial.println("invalid byte...");
    }

    // actually do something with incomingByte
    //digitalWrite(ledPin, incomingByte);   // set the LED on
  }
}

