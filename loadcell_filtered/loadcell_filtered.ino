#include "HX711.h"
HX711 loadcell;

// 1. HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

// 2. Adjustment settings
const long LOADCELL_OFFSET = 50682624;
const long LOADCELL_DIVIDER = 5895655;
void setup() {
  // 3. Initialize library
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadcell.set_scale(LOADCELL_DIVIDER);
  loadcell.set_offset(LOADCELL_OFFSET);  
  Serial.begin(115200);
}

void loop() {
  // 4. Acquire reading
  Serial.print("Weight: ");
  Serial.println(8.59 + loadcell.get_units(10), 2);  
//  delay(100);
}

