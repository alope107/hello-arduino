//Adapted from https://docs.waveshare.com/ESP32-S3-Touch-LCD-2 examples

#include <Arduino_GFX_Library.h>

#define EXAMPLE_PIN_NUM_LCD_SCLK 39
#define EXAMPLE_PIN_NUM_LCD_MOSI 38
#define EXAMPLE_PIN_NUM_LCD_MISO 40
#define EXAMPLE_PIN_NUM_LCD_DC 42
#define EXAMPLE_PIN_NUM_LCD_RST -1
#define EXAMPLE_PIN_NUM_LCD_CS 45
#define EXAMPLE_PIN_NUM_LCD_BL 1

#define EXAMPLE_LCD_ROTATION 1
#define EXAMPLE_LCD_H_RES 240
#define EXAMPLE_LCD_V_RES 320

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus *bus = new Arduino_ESP32SPI(
  EXAMPLE_PIN_NUM_LCD_DC /* DC */, EXAMPLE_PIN_NUM_LCD_CS /* CS */,
  EXAMPLE_PIN_NUM_LCD_SCLK /* SCK */, EXAMPLE_PIN_NUM_LCD_MOSI /* MOSI */, EXAMPLE_PIN_NUM_LCD_MISO /* MISO */);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *disp = new Arduino_ST7789(
  bus, EXAMPLE_PIN_NUM_LCD_RST /* RST */, EXAMPLE_LCD_ROTATION /* rotation */, true /* IPS */,
  EXAMPLE_LCD_H_RES /* width */, EXAMPLE_LCD_V_RES /* height */);

Arduino_Canvas *gfx = new Arduino_Canvas(EXAMPLE_LCD_V_RES /* width */, EXAMPLE_LCD_H_RES /* height */, disp, 0, 0, EXAMPLE_LCD_ROTATION);

/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

void setup(void)
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  while(!Serial);
  Serial.println("Arduino_GFX Hello World example");

#ifdef GFX_EXTRA_PRE_INIT
  GFX_EXTRA_PRE_INIT();
#endif

  // Init Display
  if (!gfx->begin())
  {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(RGB565(0, 0, 0));// Changing

#ifdef EXAMPLE_PIN_NUM_LCD_BL
  pinMode(EXAMPLE_PIN_NUM_LCD_BL, OUTPUT);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_BL, HIGH);
#endif

  // gfx->setCursor(10, 10);
  // gfx->setTextColor(RGB565(31, 63, 31));// Changing
  gfx->println("Hello World!");

  //delay(5000); // 5 seconds
}

int16_t x = 30;
int16_t y = 100;
int16_t r = 15;

int16_t dx = 5;
int16_t dy = 2;

void loop()
{
  gfx->fillScreen(0x0000);
  x += dx;
  y += dy;

  if(x > gfx->width() - r || x < r) {
    x -= dx;
    dx *= -1;
  }
  if(y > gfx->height() - r || y < r) {
    y -= dy;
    dy *= -1;
  }
  // gfx->fillScreen(RGB565(0, 0, 0));
  gfx->fillCircle(x, y, r, 0xffff);
  gfx->flush();

  delay(3);
}
