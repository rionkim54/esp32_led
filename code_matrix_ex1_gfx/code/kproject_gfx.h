#define COMMAND_DELAY 1 // HUB75 MATRIX
//#define COMMAND_DELAY 40      // TFT LCD
#define COMMAND_REFRESH_DELAY 100 // HUB75 MATRIX
//#define COMMAND_REFRESH_DELAY 10


#include <Adafruit_GFX.h>
#include <stdlib.h>

// Color definitions
#define KPROJECT_BLACK 0x0000       ///<   0,   0,   0
#define KPROJECT_NAVY 0x000F        ///<   0,   0, 123
#define KPROJECT_DARKGREEN 0x03E0   ///<   0, 125,   0
#define KPROJECT_DARKCYAN 0x03EF    ///<   0, 125, 123
#define KPROJECT_MAROON 0x7800      ///< 123,   0,   0
#define KPROJECT_PURPLE 0x780F      ///< 123,   0, 123
#define KPROJECT_OLIVE 0x7BE0       ///< 123, 125,   0
#define KPROJECT_LIGHTGREY 0xC618   ///< 198, 195, 198
#define KPROJECT_DARKGREY 0x7BEF    ///< 123, 125, 123
#define KPROJECT_BLUE 0x001F        ///<   0,   0, 255
#define KPROJECT_GREEN 0x07E0       ///<   0, 255,   0
#define KPROJECT_CYAN 0x07FF        ///<   0, 255, 255
#define KPROJECT_RED 0xF800         ///< 255,   0,   0
#define KPROJECT_MAGENTA 0xF81F     ///< 255,   0, 255
#define KPROJECT_YELLOW 0xFFE0      ///< 255, 255,   0
#define KPROJECT_WHITE 0xFFFF       ///< 255, 255, 255
#define KPROJECT_ORANGE 0xFD20      ///< 255, 165,   0
#define KPROJECT_GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define KPROJECT_PINK 0xFC18        ///< 255, 130, 198

class kproject_gfx : public Adafruit_GFX
{
  public:
    kproject_gfx(Stream &stream, int width, int height);
    Stream *_stream;
    void refresh();
    void begin();
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
    virtual void     drawPixel(int16_t x, int16_t y, uint16_t color);  // and these three
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    virtual void setTextColor(uint16_t c, uint16_t bg);
    virtual void setCursor(int16_t x, int16_t y);
    virtual void print_string(char *str);
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    virtual void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    virtual void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    virtual void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    virtual void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    virtual void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
    virtual void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
    virtual void draw_bmp_file(int16_t bmp_x, int16_t bmp_y, int16_t w, int16_t h, int16_t x, int16_t y, char *filename);

    void write16t(uint16_t data);
};



kproject_gfx::kproject_gfx(Stream &stream, int width, int height): Adafruit_GFX(width, height)
{
  WIDTH = width;
  HEIGHT = height;
  _width = width;
  _height = height;
  _stream = &stream;
}

void kproject_gfx::write16t(uint16_t data)
{
  _stream->write(data >> 8);
  _stream->write(data);
}

void kproject_gfx::begin()
{
  WIDTH = _width;
  HEIGHT = _height;
}

void kproject_gfx::refresh()
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)0); // command id
  _stream->write('r');
  delay(COMMAND_REFRESH_DELAY);
}

void kproject_gfx::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)1); // command id
  write16t(x);
  write16t(y);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

uint16_t kproject_gfx::color565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


void kproject_gfx::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)2); // command id
  write16t(x);
  write16t(y);
  write16t(h);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)3); // command id
  write16t(x);
  write16t(y);
  write16t(w);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);

}

void kproject_gfx::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)4); // command id
  write16t(x0);
  write16t(y0);
  write16t(x1);
  write16t(y1);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);

}

void kproject_gfx::print_string(char *str)
{
  int len = strlen(str);
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)10); // command id
  _stream->write(len);
  for ( int i = 0; i < len; i++)
  {
    _stream->write(str[i]);
  }
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::setCursor(int16_t x, int16_t y)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)8); // command id
  write16t(x);
  write16t(y);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::setTextColor(uint16_t c, uint16_t bg)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)9); // command id
  _stream->write(c >> 8);
  _stream->write(c);
  _stream->write(bg >> 8);
  _stream->write(bg);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)5); // command id
  write16t(x);
  write16t(y);
  write16t(w);
  write16t(h);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);

}

void kproject_gfx::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)6); // command id
  write16t(x);
  write16t(y);
  write16t(w);
  write16t(h);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)11); // command id
  write16t(x0);
  write16t(y0);
  write16t(r);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)12); // command id
  write16t(x0);
  write16t(y0);
  write16t(r);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)13); // command id
  write16t(x0);
  write16t(y0);
  write16t(x1);
  write16t(y1);
  write16t(x2);
  write16t(y2);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)14); // command id
  write16t(x0);
  write16t(y0);
  write16t(x1);
  write16t(y1);
  write16t(x2);
  write16t(y2);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)15); // command id
  write16t(x0);
  write16t(y0);
  write16t(w);
  write16t(h);
  write16t(radius);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color)
{
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)16); // command id
  write16t(x0);
  write16t(y0);
  write16t(w);
  write16t(h);
  write16t(radius);
  _stream->write(color >> 8);
  _stream->write(color);
  _stream->write('r');
  delay(COMMAND_DELAY);
}

void kproject_gfx::draw_bmp_file(int16_t bmp_x, int16_t bmp_y, int16_t w, int16_t h, int16_t x, int16_t y, char *filename)
{
    char filename_string[20];
    memset(filename_string,0,20);
    filename_string[0] = '/';
    strcpy(&filename_string[1], filename);
    Serial.println(filename_string);
    
  _stream->write('k');
  _stream->write('p');
  _stream->write((int8_t)17); // command id
  write16t(bmp_x);
  write16t(bmp_y);
  write16t(w);
  write16t(h);
  write16t(x);
  write16t(y);
  for ( int i = 0; i < 20; i++)
  {
    _stream->write(filename_string[i]);
  }
  _stream->write('r');
  delay(COMMAND_DELAY);
}
