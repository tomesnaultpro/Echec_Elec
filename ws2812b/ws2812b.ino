#include <Adafruit_NeoPixel.h>

#define PIN 11
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();
    int i1 = data.indexOf(',');
    int i2 = data.indexOf(',', i1 + 1);
    int i3 = data.indexOf(',', i2 + 1);

    int index = data.substring(0, i1).toInt();
    int r     = data.substring(i1 + 1, i2).toInt();
    int g     = data.substring(i2 + 1, i3).toInt();
    int b     = data.substring(i3 + 1).toInt();

    if (index >= 0 && index < NUMPIXELS) {
      pixels.setPixelColor(index, pixels.Color(r, g, b));
      pixels.show();
    }
  }
}