// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       UNO.ino
    Created:  2019-04-14 오후 9:55:31
    Author:     KMK-GRAM\alsrb
*/

// Define User Types below here or use a .h file
//
#include "HX711.h"
#include <Adafruit_NeoPixel.h>

// Define Function Prototypes that use User Types below here or use a .h file
//
#define LOADCELL_DOUT_PIN 3
#define LOADCELL_SCK_PIN 4
#define BUZZER_PIN 5
#define STRIPLED_PIN 6

#define NUMPIXELS 4


HX711 scale;
long criteiraPressure;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, STRIPLED_PIN, NEO_GRB + NEO_KHZ800);


// Define Functions below here or use other .ino or cpp files
//
long getPressure() {
  long pressure = 0;
  if (scale.is_ready()) {
    pressure = scale.read();
  }
  else {
    Serial.println("HX711 not found.");
  }
  return pressure;
}

void setStripLed(int cnt) {
  for (int i = 0; i < NUMPIXELS; i++) {
    if (i < cnt) {
      switch (i)
      {
      case 0:
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
        break;
      case 1:
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
        break;
      case 2:
        pixels.setPixelColor(i, pixels.Color(255, 255, 0));
        break;
      case 3:
        pixels.setPixelColor(i, pixels.Color(0, 255, 0));
        break;
      }
    }
    else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    pixels.show();
  }
}

// The setup() function runs once each time the micro-controller starts
void setup()
{
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  pinMode(BUZZER_PIN, OUTPUT);

  pixels.begin();
}

// Add the main program code into the continuous loop() function
void loop()
{
  long pressure;
  if (scale.is_ready()) {
    pressure = scale.read();
    Serial.print("HX711 reading: ");
    Serial.println(pressure);
    if (pressure > 33000) {
      setStripLed(0);
      noTone(BUZZER_PIN);
    }
    else if (pressure > 10000) {
      setStripLed(1);
      noTone(BUZZER_PIN);
    }
    else if (pressure > 0) {
      setStripLed(2);
      noTone(BUZZER_PIN);
    }
    else if (pressure > -20000) {
      setStripLed(3);
      noTone(BUZZER_PIN);
    }
    else {
      setStripLed(4);
      tone(BUZZER_PIN, 1000);
    }

    delay(100);
  }
  else {
    Serial.println("HX711 not found.");
  }
}



