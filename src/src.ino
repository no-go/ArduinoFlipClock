#include <MsTimer2.h>
#include "myNumbers.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306.h"

// --------------------------------- Connecting

#define OLED_MOSI  11
#define OLED_CLK   13
#define PIN_CS     5
#define PIN_RESET  6
#define PIN_DC     8

#define BUTTON1    A0
#define BUTTON2    A1

// NOT connected ---------------------
#define LED_RED     10
#define LED_GREEN   9 
#define LED_BLUE    3
#define POTI        A4 
#define SPKR        A5  // A5 has no analog(PWM) Out :-(

#define OFFSEC   6

byte hours   = 18;
byte minutes = 59;
byte seconds = 50;
byte tick    = 0;
int onsec    = 0;

int redValue   = 255;
int greenValue = 255;
int blueValue = 255;

Adafruit_SSD1306 * oled = new Adafruit_SSD1306(OLED_MOSI, OLED_CLK, PIN_DC, PIN_RESET, PIN_CS);

void hideA(byte x, short y, int h) {
  oled->fillRect(x, y+h, 16, 32-h, BLACK);
}

void hideB(byte x, short y, int h) {
  oled->fillRect(x, y, 16, 16+h, BLACK);
}

void myFont(byte x, short y, byte b, bool change) {
  int i = 0;
  int j = 17;
  int h = 0;

  if (change == true && tick > 19) {
    if(tick < 33) {
      h = tick - 20;
      
      if (b == 0) {
        oled->drawBitmap(x, y, zz1, 16, 16, WHITE);
        hideA(x,y,h);
        oled->drawBitmap(x, y+j, zz0b, 16, 16, WHITE);
      } else if (b == 1) {
        oled->drawBitmap(x, y, zz2, 16, 16, WHITE);
        hideA(x,y,h);
        oled->drawBitmap(x, y+j, zz1b, 16, 16, WHITE);
      } else if (b == 2) {
        oled->drawBitmap(x, y, zz3, 16, 16, WHITE);
        hideA(x,y,h);
        oled->drawBitmap(x, y+j, zz2b, 16, 16, WHITE);
      } else if (b == 3) {
        oled->drawBitmap(x, y, zz4, 16, 16, WHITE);
        hideA(x,y,h);
        oled->drawBitmap(x, y+j, zz3b, 16, 16, WHITE);
      } else if (b == 4) {
        oled->drawBitmap(x, y, zz5, 16, 16, WHITE);
        hideA(x,y,h);
        oled->drawBitmap(x, y+j, zz4b, 16, 16, WHITE);
      } else if (b == 5) {
        oled->drawBitmap(x, y, zz6, 16, 16, WHITE);
        hideA(x,y,h);
        oled->drawBitmap(x, y+j, zz5b, 16, 16, WHITE);
      } else if (b == 6) {
        oled->drawBitmap(x, y, zz7, 16, 16, WHITE);
        hideA(x,y,h);
        oled->drawBitmap(x, y+j, zz6b, 16, 16, WHITE);
      } else if (b == 7) {
        oled->drawBitmap(x, y, zz8, 16, 16, WHITE);
        hideA(x,y,h);
        oled->drawBitmap(x, y+j, zz7b, 16, 16, WHITE);
      } else if (b == 8) {
        oled->drawBitmap(x, y, zz9, 16, 16, WHITE);
        hideA(x,y,h);
        oled->drawBitmap(x, y+j, zz8b, 16, 16, WHITE);
      } else if (b == 9) {
        oled->drawBitmap(x, y, zz0, 16, 16, WHITE);
        hideA(x,y,h);
        oled->drawBitmap(x, y+j, zz9b, 16, 16, WHITE);
      }
      
      oled->drawLine(x-1,    y+h-1, x+15, y+h-1,  WHITE);
      oled->drawLine(x-1,    y+h-1, x+2,  y+16, WHITE);
      oled->drawLine(x+15,   y+h-1, x+13, y+16, WHITE);

    } else {
      
      h = tick - 33;
      
      if (b == 0) {
        oled->drawBitmap(x, y+j, zz0b, 16, 16, WHITE);
        hideB(x,y,h);
        oled->drawBitmap(x, y+h, zz1b, 16, 16, WHITE);
        oled->fillRect(x, y, 16, 16, BLACK);
        oled->drawBitmap(x, y, zz1, 16, 16, WHITE);
      } else if (b == 1) {
        oled->drawBitmap(x, y+j, zz1b, 16, 16, WHITE);
        hideB(x,y,h);
        oled->drawBitmap(x, y+h, zz2b, 16, 16, WHITE);
        oled->fillRect(x, y, 16, 16, BLACK);
        oled->drawBitmap(x, y, zz2, 16, 16, WHITE);
      } else if (b == 2) {
        oled->drawBitmap(x, y+j, zz2b, 16, 16, WHITE);
        hideB(x,y,h);
        oled->drawBitmap(x, y+h, zz3b, 16, 16, WHITE);
        oled->fillRect(x, y, 16, 16, BLACK);
        oled->drawBitmap(x, y, zz3, 16, 16, WHITE);
      } else if (b == 3) {
        oled->drawBitmap(x, y+j, zz3b, 16, 16, WHITE);
        hideB(x,y,h);
        oled->drawBitmap(x, y+h, zz4b, 16, 16, WHITE);
        oled->fillRect(x, y, 16, 16, BLACK);
        oled->drawBitmap(x, y, zz4, 16, 16, WHITE);
      } else if (b == 4) {
        oled->drawBitmap(x, y+j, zz4b, 16, 16, WHITE);
        hideB(x,y,h);
        oled->drawBitmap(x, y+h, zz5b, 16, 16, WHITE);
        oled->fillRect(x, y, 16, 16, BLACK);
        oled->drawBitmap(x, y, zz5, 16, 16, WHITE);
      } else if (b == 5) {
        oled->drawBitmap(x, y+j, zz5b, 16, 16, WHITE);
        hideB(x,y,h);
        oled->drawBitmap(x, y+h, zz6b, 16, 16, WHITE);
        oled->fillRect(x, y, 16, 16, BLACK);
        oled->drawBitmap(x, y, zz6, 16, 16, WHITE);
      } else if (b == 6) {
        oled->drawBitmap(x, y+j, zz6b, 16, 16, WHITE);
        hideB(x,y,h);
        oled->drawBitmap(x, y+h, zz7b, 16, 16, WHITE);
        oled->fillRect(x, y, 16, 16, BLACK);
        oled->drawBitmap(x, y, zz7, 16, 16, WHITE);
      } else if (b == 7) {
        oled->drawBitmap(x, y+j, zz7b, 16, 16, WHITE);
        hideB(x,y,h);
        oled->drawBitmap(x, y+h, zz8b, 16, 16, WHITE);
        oled->fillRect(x, y, 16, 16, BLACK);
        oled->drawBitmap(x, y, zz8, 16, 16, WHITE);
      } else if (b == 8) {
        oled->drawBitmap(x, y+j, zz8b, 16, 16, WHITE);
        hideB(x,y,h);
        oled->drawBitmap(x, y+h, zz9b, 16, 16, WHITE);
        oled->fillRect(x, y, 16, 16, BLACK);
        oled->drawBitmap(x, y, zz9, 16, 16, WHITE);
      } else if (b == 9) {
        oled->drawBitmap(x, y+j, zz9b, 16, 16, WHITE);
        hideB(x,y,h);
        oled->drawBitmap(x, y+h, zz0b, 16, 16, WHITE);
        oled->fillRect(x, y, 16, 16, BLACK);
        oled->drawBitmap(x, y, zz0, 16, 16, WHITE);
      }      

      oled->drawLine(x-1,    y+16+h, x+15, y+16+h,  WHITE);
      oled->drawLine(x+2,    y+16,   x-1,  y+16+h,  WHITE);
      oled->drawLine(x+13,   y+16,   x+15, y+16+h,  WHITE);      
    }

    
  } else {
  
    if (b == 0) {
      oled->drawBitmap(x, y+i, zz0,  16, 16, WHITE);
      oled->drawBitmap(x, y+j, zz0b, 16, 16, WHITE);
    } else if (b == 1) {
      oled->drawBitmap(x, y+i, zz1,  16, 16, WHITE);
      oled->drawBitmap(x, y+j, zz1b, 16, 16, WHITE);
    } else if (b == 2) {
      oled->drawBitmap(x, y+i, zz2,  16, 16, WHITE);
      oled->drawBitmap(x, y+j, zz2b, 16, 16, WHITE);
    } else if (b == 3) {
      oled->drawBitmap(x, y+i, zz3,  16, 16, WHITE);
      oled->drawBitmap(x, y+j, zz3b, 16, 16, WHITE);
    } else if (b == 4) {
      oled->drawBitmap(x, y+i, zz4,  16, 16, WHITE);
      oled->drawBitmap(x, y+j, zz4b, 16, 16, WHITE);
    } else if (b == 5) {
      oled->drawBitmap(x, y+i, zz5,  16, 16, WHITE);
      oled->drawBitmap(x, y+j, zz5b, 16, 16, WHITE);
    } else if (b == 6) {
      oled->drawBitmap(x, y+i, zz6,  16, 16, WHITE);
      oled->drawBitmap(x, y+j, zz6b, 16, 16, WHITE);
    } else if (b == 7) {
      oled->drawBitmap(x, y+i, zz7,  16, 16, WHITE);
      oled->drawBitmap(x, y+j, zz7b, 16, 16, WHITE);
    } else if (b == 8) {
      oled->drawBitmap(x, y+i, zz8,  16, 16, WHITE);
      oled->drawBitmap(x, y+j, zz8b, 16, 16, WHITE);
    } else if (b == 9) {
      oled->drawBitmap(x, y+i, zz9,  16, 16, WHITE);
      oled->drawBitmap(x, y+j, zz9b, 16, 16, WHITE);
    }
  }

}

inline void flipClock() {
  bool flap = false;
  
  oled->setCursor(28, 40);
  oled->print((int) hours);
  
  flap = false;
  int t = minutes/10;
  if ((minutes+1)%10 == 0 && (seconds+1)%60 == 0) flap=true;
  myFont(0, 0, t, flap);
  
  flap = false;
  t = minutes - t*10;
  if ((seconds+1)%60 == 0) flap=true;
  myFont(16, 0, t, flap);

  flap = false;
  t = seconds/10;
  if ((seconds+1)%10 == 0) flap=true;
  myFont(32, 0, t, flap);
  
  t = seconds - t*10;
  myFont(48, 0, t, true);
}

inline void ticking() {
  tick = (tick+1) % 40;
  
  if (tick == 0) {
    seconds++;
    if (onsec>=0 && onsec <= OFFSEC) onsec++;
  }
  if (seconds > 59) {
    minutes += seconds / 60;
    seconds  = seconds % 60;
  }
  if (minutes > 59) {
    hours  += minutes / 60;
    minutes = minutes % 60;
  }
  if (hours > 23) {
    hours = hours % 24;
  }
}

void setup() {
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(POTI, INPUT);

  pinMode(SPKR, OUTPUT);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  analogWrite(LED_RED, 255);
  analogWrite(LED_GREEN, 255);
  analogWrite(LED_BLUE, 255);

  oled->begin();
  oled->clearDisplay();
  oled->display();
  oled->setTextColor(WHITE);
  oled->setTextSize(1);

  MsTimer2::set(25, ticking); // 50ms period -> 1sec = 40 parts/ticks
  MsTimer2::start();
}

void loop() {
  delay(7); // "refresh rate"

  if (onsec > OFFSEC) {
    oled->ssd1306_command(SSD1306_DISPLAYOFF);
    digitalWrite(OLED_CLK, LOW);
    onsec = -1;
  }

  if ( onsec != -1 ) {
    oled->clearDisplay();
    flipClock();
    oled->display();   
  }
  
  if (digitalRead(BUTTON1) == LOW) {
    onsec = 0;
    oled->ssd1306_command(SSD1306_DISPLAYON);
    
    delay(700);
    while (digitalRead(BUTTON1) == LOW) {
      hours = (hours+1)%24;
      seconds = 0;
      tick = 0;
      oled->clearDisplay();
      flipClock();
      oled->display();
      delay(250);
    }
  }

  if (digitalRead(BUTTON2) == LOW) {
    onsec = 0;
    oled->ssd1306_command(SSD1306_DISPLAYON);
    
    delay(700);
    while (digitalRead(BUTTON2) == LOW) {
      minutes = (minutes+1)%60;
      seconds = 0;
      tick = 0;
      oled->clearDisplay();
      flipClock();
      oled->display();
      delay(250);
    }
  }

}

