#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // OLED display Reset pin, -1 if nonexistent

#define YELLOW_AREA 8 // Anything sub 8 will be in the yellow area

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();
  display.display();

  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0, 30);
  // // Display static text
  // display.println("Hello, world!");
  // display.display();
}

const String inputText = "Welcome to the dvd!";
const int textSizePerChar = 8;

void loop()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Title
  display.setCursor(0, textSizePerChar);
  for (unsigned int i = 0; i < inputText.length(); i++)
  {
    display.print(inputText[i]);
    delay(250);
    display.display();
  }

  // Dvd bouncer
  int x = 0;
  int y = textSizePerChar + YELLOW_AREA;
  int dx = 1;
  int dy = 1;

  while (true)
  {
    display.setCursor(x, y);
    display.print(".");

    x += dx;
    y += dy;

    if (x >= SCREEN_WIDTH)
    {
      x = SCREEN_WIDTH;
      dx = -dx;
    }
    else if (x <= 0)
    {
      x = 0;
      dx = -dx;
    }

    if (y >= (SCREEN_HEIGHT - YELLOW_AREA))
    {
      y = (SCREEN_HEIGHT - YELLOW_AREA);
      dy = -dy;
    }
    else if (y <= (YELLOW_AREA + 3))
    {
      y = (YELLOW_AREA + 3);
      dy = -dy;
    }

    delay(50);
    display.display();
  }

  delay(5000);
  display.clearDisplay();
  display.display();
}