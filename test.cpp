#include <Arduino.h>

int sensorPin = 1; //define analog pin
int value = 0; 

void setup() {
	Serial.begin(115200); 
} 

void loop() {
	value = analogRead(sensorPin); 
	Serial.println(value, DEC); // light intensity | high values for bright environment | low values for dark environment
	delay(100); 
}