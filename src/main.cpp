/*********************************************************************************************************
* LILYGO T-Display-S3 KY-018 Photoresistor Sensor Project
*
* This sketch reads the analog signal from the KY-018 module and displays it on the
* built-in screen of the LilyGO T-Display-S3 using the TFT_eSPI library.
* The KY-018 module includes a photoresistor (LDR) that changes its resistance based on light intensity.

* Description:
*  This code reads the analog signal from the KY-018 module and displays it on the
*   built-in screen of the LilyGO T-Display-S3 using the TFT_eSPI library.
*  The code uses state machine logic to avoid using delays, which is code blocking.
*  The screen is only updated if there is a change in readings.
*  Sensor readings are mapped from 0-4095 (12bit resolution) to 0-99.
*
* Pin Connections:
*  - KY-018 VCC  -> 3.3V
*  - KY-018 GND  -> GND
*  - KY-018 A0   -> A0 (pin 1)

* KY-018 Specifications:
*  - Protocol: Analog
*  - Operating Voltage: 3.3V ~ 5V
**********************************************************************************************************/

/*************************************************************
******************* INCLUDES & DEFINITIONS *******************
**************************************************************/

#include <Arduino.h>
#include <TFT_eSPI.h>

// TFT_eSPI
TFT_eSPI tft = TFT_eSPI();

// Pin definitions
const int analogPin = A0; // analog pin 0

// Variables for timing
unsigned long previousMillis = 0;
const long interval = 100; // interval for reading and printing (ms)

// State Machine States
enum class State {
  READ_SENSOR,    // state for reading sensor data
  UPDATE_DISPLAY, // state for updating the display
  WAIT            // state for waiting between sensor reads
};

// Global variables
State currentState = State::READ_SENSOR; // initial state
int rawValue = 0;                        // raw analog value from the sensor
int scaledValue = 0;                     // scaled value for display
bool redrawRequired = true;              // flag to redraw the screen


/*************************************************************
********************** HELPER FUNCTIONS **********************
**************************************************************/

// Function to draw static elements on the TFT screen
void drawStaticElements() {
  // Clear the screen and set text properties
  tft.fillScreen(TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // Reset cursor to the top-left corner
  tft.setCursor(0, 0);

  // Display header
  tft.println("---------------------------");
  tft.println("   KY018 Photoresistor");
  tft.println("---------------------------");

  // Display static labels
  tft.setCursor(0, 70); // position for analog value
  tft.print("Light Intensity:");
}

// Function to update dynamic elements on the TFT screen
void updateDynamicElements() {
  // Update analog value
  tft.setCursor(0, 90);  // position for analog value
  tft.print("        "); // clear previous value (8 spaces for padding)
  tft.setCursor(0, 90);  // reset cursor
  tft.print(scaledValue);
}


/*************************************************************
*********************** MAIN FUNCTIONS ***********************
**************************************************************/

// SETUP
void setup() {
  // Set the ADC resolution to 12 bits (0-4095) & set PIN mode
  analogReadResolution(12);
  pinMode(analogPin, INPUT);

  // Initialize the TFT display
  tft.init();
  tft.setRotation(0);                     // adjust rotation (0 & 2 portrait | 1 & 3 landscape)
  tft.fillScreen(TFT_BLACK);              // black background
  tft.setTextFont(2);                     // set the font size
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // set text colour (white) and background colour (black)

  // Draw static elements once
  drawStaticElements();

  // Initial display update
  redrawRequired = true; // update display
}


// MAIN LOOP
void loop() {
  unsigned long currentMillis = millis(); // get the current millis time

  // State Machine Logic
  switch (currentState) {
    case State::READ_SENSOR:
      // Read the analog value from the sensor
      rawValue = analogRead(analogPin);

      // Scale the raw value linearly and map to 0-99
      scaledValue = map(rawValue, 0, 4095, 0, 99);

      // Move to the next state
      currentState = State::UPDATE_DISPLAY;
      break;

    case State::UPDATE_DISPLAY:
      // Update the display with the new sensor data
      updateDynamicElements();

      // Move to the WAIT state
      currentState = State::WAIT;
      previousMillis = currentMillis; // record the previous millis time
      break;

    case State::WAIT:
      // Wait for the specified interval before reading the sensor again
      if (currentMillis - previousMillis >= interval) {
        currentState = State::READ_SENSOR;
        redrawRequired = true; // update display
      }
      break;

    default:
      // Default case (should not happen)
      currentState = State::READ_SENSOR;
      break;
  }
}
