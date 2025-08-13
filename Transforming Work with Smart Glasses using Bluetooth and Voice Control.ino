#include <SoftwareSerial.h>
String voice;
// Configure the A9G module communication pins
#define A9G_RX_PIN 6
#define A9G_TX_PIN 5
SoftwareSerial A9G(A9G_RX_PIN, A9G_TX_PIN);
void setup() {
pinMode(13, OUTPUT); // LED connected to pin 13
Serial.begin(9600);
A9G.begin(9600);
delay(1000);
sendCommand("AT"); // Check if the module is responding
delay(500);
sendCommand("AT+CMGF=1"); // Set the SMS mode to text mode
delay(500);
}
void loop() {
while (Serial.available() > 0) {
delay(10);
char c = Serial.read();
if (c == '#') {
break;
}
voice += c;
}
if (voice == "*turn on") {
digitalWrite(13, HIGH); // Turn on LED
Serial.println("calling calling...");
makeCall1();
//sendSMS1("You are getting a call!"); // Send SMS with message
delay(5000);
}
else if (voice == "*turn off") {
digitalWrite(13, LOW); // Turn off LED
Serial.println("messaging messaging...");
sendSMS1("I am in danger...!!"); // Send SMS with message
delay(5000);
}
if (voice.length() > 0) {
Serial.println(voice);
voice = "";
}
}
void sendSMS1(const char* message) {
sendCommand("AT"); // Check if the module is responding
delay(500);
sendCommand("AT+CMGF=1"); // Set the SMS mode to text mode
delay(500);
sendCommand("AT+CMGS=\"+916303838668\""); // Replace with the recipient's
phone number
delay(500);
sendCommand(message); // Replace with the SMS content
delay(500);
A9G.write(0x1A); // Send the CTRL+Z character to indicate the end of
the message
delay(5000); // Wait for the module to send the SMS
Serial.println("SMS Sent");
}
void makeCall1() {
sendCommand("AT"); // Check if the module is responding
delay(500);
sendCommand("ATH");
delay(500);
sendCommand("ATD+916303838668"); // Replace with the recipient's phone
number
delay(5000); // Wait for the call to be established
Serial.println("Call Sent");
}
void sendCommand(const char* command) {
A9G.println(command); // Send the command to the A9G module
while (!A9G.available()) {} // Wait for the response
while (A9G.available()) { // Print the response
Serial.write(A9G.read());
}
Serial.println();
}
