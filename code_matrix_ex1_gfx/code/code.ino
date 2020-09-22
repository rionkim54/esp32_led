#include <SoftwareSerial.h>
#include "kproject_gfx.h"

SoftwareSerial soft(2,3);

kproject_gfx kproject(soft, 64, 32);

void setup()
{
  Serial.begin(9600);
  soft.begin(9600);
  kproject.begin();
}

void loop()
{
  Serial.print(F("Text                     "));
  Serial.println(testText());
  Serial.println(F("Benchmark                Time (microseconds)"));
  Serial.print(F("Screen fill              "));
  Serial.println(testFillScreen());
  delay(0);
  Serial.print(F("Lines                    "));
  Serial.println(testLines(KPROJECT_CYAN));
  delay(0);
  Serial.print(F("Horiz/Vert Lines         "));
  Serial.println(testFastLines(KPROJECT_RED, KPROJECT_BLUE));
  delay(0);
  Serial.print(F("Rectangles (outline)     "));
  Serial.println(testRects(KPROJECT_GREEN));
  delay(0);
  Serial.print(F("Rectangles (filled)      "));
  Serial.println(testFilledRects(KPROJECT_YELLOW, KPROJECT_MAGENTA));
  delay(0);
  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, KPROJECT_MAGENTA));
  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, KPROJECT_WHITE));
  delay(0);
  Serial.print(F("Triangles (outline)      "));
  Serial.println(testTriangles());
  delay(0);
  Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(0);
  Serial.print(F("Rounded rects (outline)  "));
  Serial.println(testRoundRects());
  delay(0);
  Serial.print(F("Rounded rects (filled)   "));
  Serial.println(testFilledRoundRects());
  delay(0);
  Serial.println(F("Done!"));
}

unsigned long testFillScreen()
{
  unsigned long start = micros();
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();
  kproject.fillScreen(KPROJECT_RED);
  kproject.refresh();
  kproject.fillScreen(KPROJECT_GREEN);
  kproject.refresh();
  kproject.fillScreen(KPROJECT_BLUE);
  kproject.refresh();
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();
  return micros() - start;
}

unsigned long testLines(uint16_t color)
{
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = kproject.width(),
                h = kproject.height();

  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();
  delay(0);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6)
  {
    kproject.drawLine(x1, y1, x2, y2, color);
    kproject.refresh();
  }

  x2 = w - 1;
  for (y2 = 0; y2 < h; y2 += 6)
  {
    kproject.drawLine(x1, y1, x2, y2, color);
    kproject.refresh();
  }

  t     = micros() - start; // fillScreen doesn't count against timing
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6)
  {
    kproject.drawLine(x1, y1, x2, y2, color);
    kproject.refresh();
  }
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6)
  {
    kproject.drawLine(x1, y1, x2, y2, color);
    kproject.refresh();
  }
  t    += micros() - start;

  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6)
  {
    kproject.drawLine(x1, y1, x2, y2, color);
    kproject.refresh();
  }
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6)
  {
    kproject.drawLine(x1, y1, x2, y2, color);
    kproject.refresh();
  }
  t    += micros() - start;

  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6)
  {
    kproject.drawLine(x1, y1, x2, y2, color);
    kproject.refresh();
  }
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6)
  {
    kproject.drawLine(x1, y1, x2, y2, color);
    kproject.refresh();
  }
  return micros() - start;
}

unsigned long testText()
{
  kproject.fillScreen(KPROJECT_BLACK);
  unsigned long start = micros();
  kproject.setCursor(0, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("Hello World!");
  kproject.refresh();
  delay(0);
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(0, 42);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("안녕하세요!");
  kproject.refresh();
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(0, 42);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("반갑습니다!");
  kproject.refresh();
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(0, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("안녕하세요!");
  kproject.refresh();
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(0, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("반갑습니다!");
  kproject.refresh();
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(0, 42);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("안녕하세요!");
  kproject.refresh();
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(0, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("반갑습니다!");
  kproject.refresh();



  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(0, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("안녕하세요!");
  kproject.refresh();
  delay(0);

  int pos = 0;
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("안");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string("녕");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_GREEN, KPROJECT_BLACK);
  kproject.print_string("하");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_YELLOW, KPROJECT_BLACK);
  kproject.print_string("세");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_CYAN, KPROJECT_BLACK);
  kproject.print_string("요");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_ORANGE, KPROJECT_BLACK);
  kproject.print_string("!");

  kproject.refresh();
  delay(0);


  pos = 0;
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string("안");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_GREEN, KPROJECT_BLACK);
  kproject.print_string("녕");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_YELLOW, KPROJECT_BLACK);
  kproject.print_string("하");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_CYAN, KPROJECT_BLACK);
  kproject.print_string("세");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_ORANGE, KPROJECT_BLACK);
  kproject.print_string("요");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("!");

  kproject.refresh();
  delay(0);

  pos = 0;
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_GREEN, KPROJECT_BLACK);
  kproject.print_string("안");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_YELLOW, KPROJECT_BLACK);
  kproject.print_string("녕");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_CYAN, KPROJECT_BLACK);
  kproject.print_string("하");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_ORANGE, KPROJECT_BLACK);
  kproject.print_string("세");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("요");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string("!");

  kproject.refresh();
  delay(0);

  pos = 0;
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_YELLOW, KPROJECT_BLACK);
  kproject.print_string("안");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_CYAN, KPROJECT_BLACK);
  kproject.print_string("녕");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_ORANGE, KPROJECT_BLACK);
  kproject.print_string("하");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("세");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string("요");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_GREEN, KPROJECT_BLACK);
  kproject.print_string("!");

  kproject.refresh();
  delay(0);

  pos = 0;
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_CYAN, KPROJECT_BLACK);
  kproject.print_string("안");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_ORANGE, KPROJECT_BLACK);
  kproject.print_string("녕");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("하");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string("세");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_GREEN, KPROJECT_BLACK);
  kproject.print_string("요");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_YELLOW, KPROJECT_BLACK);
  kproject.print_string("!");

  kproject.refresh();
  delay(0);


  pos = 0;
  kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_ORANGE, KPROJECT_BLACK);
  kproject.print_string("안");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("녕");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string("하");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_GREEN, KPROJECT_BLACK);
  kproject.print_string("세");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_YELLOW, KPROJECT_BLACK);
  kproject.print_string("요");

  pos += 16;
  kproject.setCursor(pos, 10);
  kproject.setTextColor(KPROJECT_CYAN, KPROJECT_BLACK);
  kproject.print_string("!");

  kproject.refresh();
  delay(0);
  return micros() - start;
}


unsigned long testFastLines(uint16_t color1, uint16_t color2)
{
  unsigned long start;
  int           x, y, w = kproject.width(), h = kproject.height();

  kproject.fillScreen(KPROJECT_BLACK);
  start = micros();
  for (y = 0; y < h; y += 5)
  {
    kproject.drawFastHLine(0, y, w, color1);
    kproject.refresh();
  }
  for (x = 0; x < w; x += 5)
  {
    kproject.drawFastVLine(x, 0, h, color2);
    kproject.refresh();
  }

  return micros() - start;
}

unsigned long testRects(uint16_t color)
{
  unsigned long start;
  int n, i, i2, cx = kproject.width()  / 2, cy = kproject.height() / 2;

  kproject.fillScreen(KPROJECT_BLACK);
  n     = min(kproject.width(), kproject.height());
  start = micros();
  for (i = 2; i < n; i += 6)
  {
    i2 = i / 2;
    kproject.drawRect(cx - i2, cy - i2, i, i, color);
    kproject.refresh();
  }
  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2)
{
  unsigned long start, t = 0;
  int           n, i, i2, cx = kproject.width()  / 2 - 1, cy = kproject.height() / 2 - 1;

  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();
  n = min(kproject.width(), kproject.height());
  for (i = n; i > 0; i -= 6)
  {
    i2    = i / 2;
    start = micros();
    kproject.fillRect(cx - i2, cy - i2, i, i, color1);
    kproject.refresh();
    t    += micros() - start;
    // Outlines are not included in timing results
    kproject.drawRect(cx - i2, cy - i2, i, i, color2);
    kproject.refresh();
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color)
{
  unsigned long start;
  int x, y, w = kproject.width(), h = kproject.height(), r2 = radius * 2;

  kproject.fillScreen(KPROJECT_BLACK);
  start = micros();
  for (x = radius; x < w; x += r2)
  {
    for (y = radius; y < h; y += r2)
    {
      kproject.fillCircle(x, y, radius, color);
      kproject.refresh();
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color)
{
  unsigned long start;
  int           x, y, r2 = radius * 2,
                      w = kproject.width()  + radius,
                      h = kproject.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  kproject.fillScreen(KPROJECT_BLACK);
  start = micros();
  for (x = 0; x < w; x += r2)
  {
    for (y = 0; y < h; y += r2)
    {
      kproject.drawCircle(x, y, radius, color);
      kproject.refresh();
    }
  }

  return micros() - start;
}

unsigned long testTriangles()
{
  unsigned long start;
  int           n, i, cx = kproject.width()  / 2 - 1,
                      cy = kproject.height() / 2 - 1;

  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();
  n     = min(cx, cy);
  start = micros();
  for (i = 0; i < n; i += 5)
  {
    kproject.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      kproject.color565(255, 255, 255));
    kproject.refresh();
  }

  return micros() - start;
}

unsigned long testFilledTriangles()
{
  unsigned long start, t = 0;
  int           i, cx = kproject.width()  / 2 - 1,
                   cy = kproject.height() / 2 - 1;

  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();
  start = micros();
  for (i = min(cx, cy); i > 10; i -= 5)
  {
    start = micros();
    kproject.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, kproject.color565(0, i * 10, i * 10));
    t += micros() - start;
    kproject.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, kproject.color565(i * 10, i * 10, 0));
    kproject.refresh();
  }

  return t;
}

unsigned long testRoundRects()
{
  unsigned long start;
  int           w, i, i2,
                cx = kproject.width()  / 2 - 1,
                cy = kproject.height() / 2 - 1;

  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();
  w     = min(kproject.width(), kproject.height());
  start = micros();
  for (i = 0; i < w; i += 6)
  {
    i2 = i / 2;
    kproject.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, kproject.color565(i, 0, 0));
    kproject.refresh();
  }

  return micros() - start;
}

unsigned long testFilledRoundRects()
{
  unsigned long start;
  int           i, i2,
                cx = kproject.width()  / 2 - 1,
                cy = kproject.height() / 2 - 1;

  kproject.fillScreen(KPROJECT_BLACK);
  kproject.refresh();
  start = micros();
  for (i = min(kproject.width(), kproject.height()); i > 20; i -= 6)
  {
    i2 = i / 2;
    kproject.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, kproject.color565(0, i, 0));
    kproject.refresh();
  }

  return micros() - start;
}
