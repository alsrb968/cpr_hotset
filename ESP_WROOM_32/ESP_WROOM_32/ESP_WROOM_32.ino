/*
 Name:		ESP_WROOM_32.ino
 Created:	2019-03-23 오후 6:32:02
 Author:	Kang Minkyu
*/

#include <BluetoothSerial.h>
#include <HX711.h>


#define LED_BUILTIN 2
boolean ledState = LOW;

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 13
#define LOADCELL_SCK_PIN 14

BluetoothSerial SerialBT;
HX711 scale;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);

	Serial.begin(115200);
	SerialBT.begin("ESP32test"); //Bluetooth device name
	Serial.println("The device started, now you can pair it with bluetooth!");
	scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (scale.is_ready()) {
		long reading = scale.read();
		Serial.print("HX711 reading: ");
		Serial.println(reading);
		SerialBT.println(reading);
	}
	else {
		Serial.println("HX711 not found.");
	}

	delay(100);
	digitalWrite(LED_BUILTIN, !ledState);
}
