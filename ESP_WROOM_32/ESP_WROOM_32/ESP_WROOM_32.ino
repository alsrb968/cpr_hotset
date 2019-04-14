/*
 Name:		ESP_WROOM_32.ino
 Created:	2019-03-23 오후 6:32:02
 Author:	Kang Minkyu
*/

#include "ESP_WROOM_32.h"

#if(1 == BLUETOOTH_SERIAL)
#include <BluetoothSerial.h>
#endif
#include <HX711.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Build in LED
#if(1 == BOARD_ESP32)
#define LED_BUILTIN 2
#elif(1 == BOARD_UNO)
#define LED_BUILTIN 2
#endif
boolean ledState = LOW;

// HX711 circuit wiring
#if(1 == BOARD_ESP32)
#define LOADCELL_DOUT_PIN 13
#define LOADCELL_SCK_PIN 14
#elif(1 == BOARD_UNO)
#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 3
#endif
HX711 scale;
long criteiraPressure;

// Bluetooth
#if(1 == BLUETOOTH_SERIAL)
BluetoothSerial SerialBT;
#endif

// Buzzer
#if(1 == BOARD_ESP32)
#define BUZZER_PIN 32
#elif(1 == BOARD_UNO)
#define BUZZER_PIN 4
#endif

// NeoPixel
#if(1 == BOARD_ESP32)
#define STRIPLED_PIN 35
#elif(1 == BOARD_UNO)
#define STRIPLED_PIN 5
#endif
#define NUMPIXELS 4
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, STRIPLED_PIN, NEO_GRB + NEO_KHZ800);

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);

	Serial.begin(115200);
#if(1 == BLUETOOTH_SERIAL)
	SerialBT.begin("ESP32test"); //Bluetooth device name
#endif
	Serial.println("The device started, now you can pair it with bluetooth!");
	scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
	criteiraPressure = getPressure();

	pinMode(BUZZER_PIN, OUTPUT);
	
	pixels.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	long pressure = abs(getPressure() /*- criteiraPressure*/);
	Serial.print("HX711 reading: ");
	Serial.print(pressure);
	Serial.print(" : ");
	Serial.println(criteiraPressure);
#if(1 == BLUETOOTH_SERIAL)
	SerialBT.println(pressure);
#endif

	if (pressure > 20000) {
		digitalWrite(BUZZER_PIN, HIGH);
	}
	else {
		digitalWrite(BUZZER_PIN, LOW);
	}

	for (int i = 0; i < NUMPIXELS; i++) {
		// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
		pixels.setPixelColor(i, pixels.Color(0, 150, 0));
		pixels.show();
		//delay(500);
	}
	
	digitalWrite(LED_BUILTIN, !ledState);
	delay(100);
}


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
