#include <SPI.h>

#include <TFT_eSPI.h>       
#include <XPT2046_Touchscreen.h>    

// SPI of the LCD and the XPT2046 are not in the same bus

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

auto hspi = new SPIClass(HSPI);

XPT2046_Touchscreen touch(33, 36);

void setup() {
  Serial.begin( 115200 );
    
  hspi->begin(25, 39, 32, 33);
  hspi->setFrequency( 60000000 );

  pinMode(hspi->pinSS(), OUTPUT);
  
  tft.init();
  touch.begin(*hspi);  
  
  touch.setRotation(1);

  //RIGHT COLORS ?
  //tft.writecommand(TFT_MADCTL);
  //tft.writedata(0x40);
  //tft.setRotation(1); // Vertical

  // NOTE: tft.width() and tft.height() never changes 320x240
  
  tft.fillScreen(TFT_BLACK);
  tft.drawRect(0, 0, tft.width(), tft.height(), TFT_GREEN);
  tft.println("Hello");

  Serial.println("Config ended");
  Serial.print("Screen X: ");
  Serial.print(tft.width());
  Serial.print("  Screen Y: ");
  Serial.println(tft.height());
}

void loop() {

  boolean istouched = touch.touched();
  if (istouched) {
    TS_Point raw = touch.getPoint();

    int x = getX(raw);
    int y = getY(raw);

    Serial.print("X: ");
    Serial.print(x);
    Serial.print("  Y: ");
    Serial.println(y);

    tft.drawPixel(x, y, TFT_GREEN);
  }
  
}

int getX(TS_Point p) {
  // map(value, fromLow, fromHigh, toLow, toHigh)
  return map(p.x, 3800, 220, 0, 320);
}

int getY(TS_Point p) {
  // map(value, fromLow, fromHigh, toLow, toHigh)
  return map(p.y, 3800, 220, 0, 240);
}
