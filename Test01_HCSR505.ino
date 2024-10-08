/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-motion-sensor-piezo-buzzer
 *
 * Modified by Diegooz for some tests. https://www.youtube.com/@PixelsSquad
 * Accende un led quando il sensore di movimento HCSR505 rileva qualcosa. In questo caso il pin 2 è quello del led integrato alla schedina.
 */

#define MOTION_SENSOR_PIN  13  // PIN DELL'ESP32 DOVE è CONNESSA L'USCITA DEL SENSORE HCSR505
#define LED_PIN         2  // PIN DEL LED, SULLA MIA ESP32 DI IDEASPARK L'USCITA 2 è QUELLA DEL LED INTERNO
int motionStateCurrent  = LOW; // current  state of motion sensor's pin
int motionStatePrevious = LOW; // previous state of motion sensor's pin

void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(MOTION_SENSOR_PIN, INPUT); // set ESP32 pin to input mode
  pinMode(LED_PIN, OUTPUT);          // set ESP32 pin to output mode
}

void loop() {
  motionStatePrevious = motionStateCurrent;            // store old state
  motionStateCurrent  = digitalRead(MOTION_SENSOR_PIN); // read new state

  if (motionStatePrevious == LOW && motionStateCurrent == HIGH) { // pin state change: LOW -> HIGH
    Serial.println("Movimento rilevato, accendo il led");
    digitalWrite(LED_PIN, HIGH); // accende il led
  } else if (motionStatePrevious == HIGH && motionStateCurrent == LOW) { // pin state change: HIGH -> LOW
    Serial.println("Nessun movimento, torno a dormire....");
    digitalWrite(LED_PIN, LOW);  // spegne il led
  }
}
