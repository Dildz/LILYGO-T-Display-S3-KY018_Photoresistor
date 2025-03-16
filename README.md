LILYGO T-Display-S3 KY-018 Photoresistor Sensor Project

This sketch reads the analog signal from the KY-018 module and displays it on the
built-in screen of the LilyGO T-Display-S3 using the TFT_eSPI library.
The KY-018 module includes a photoresistor (LDR) that changes its resistance based on light intensity.

Description:

 This code reads the analog signal from the KY-018 module and displays it on the built-in screen of the LilyGO T-Display-S3 using the TFT_eSPI library.
 The code uses state machine logic to avoid using delays, which is code blocking.
 The screen is only updated if there is a change in readings.
 Sensor readings are mapped from 0-4095 (12bit resolution) to 0-99.

Pin Connections:
 - KY-018 VCC  -> 3.3V
 - KY-018 GND  -> GND
 - KY-018 A0   -> A0 (pin 1)

KY-018 Specifications:
 - Protocol: Analog
 - Operating Voltage: 3.3V ~ 5V
