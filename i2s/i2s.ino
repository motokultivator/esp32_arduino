#include "ESP_I2S.h"

#define I2S_SCK 5
#define I2S_WS 25
#define I2S_SDOUT 26

uint16_t buf[64];
I2SClass i2s;
uint16_t l = 0;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    delay(10);
  }

  Serial.println("Initializing I2S bus...");

  i2s.setPins(I2S_SCK, I2S_WS, I2S_SDOUT);

  if (!i2s.begin(I2S_MODE_STD, 44100, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO, I2S_STD_SLOT_BOTH)) {
    Serial.println("Failed to initialize I2S bus!");
  }

  Serial.println("Setup completed...");
}

void loop()
{
  size_t bytes;

  for (int i = 0; i < 64; i++)
    buf[i] = l++;

  for (int a = 0; a < 128;) {
    bytes = i2s.write(((uint8_t *)buf) + a, 128 - a);
    if (a < 0)
      break;
    a += bytes;
    delayMicroseconds(100);
  }
}
