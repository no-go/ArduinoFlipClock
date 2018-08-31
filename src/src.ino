#include <MsTimer2.h>
#include "myNumbers.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306.h"

// --------------------------------- Connecting

#define OLED_MOSI  11
#define OLED_CLK   13
#define PIN_CS     5
#define PIN_RESET  6
#define PIN_DC     8

#define BUTTON1    A1
#define BUTTON2    A0

#define LED_RED     10
#define LED_GREEN   9 
#define LED_BLUE    3

#include "DS3231M.h"
// RTC Chip DS3231M: ---------------------
// A4 = SDA
// A5 = SCL

#define OFFSEC   6

/*
 *  0 = set hours
 *  1 = set minutes
 *  2 = media previous
 *  3 = volume+ -
 *  4 = cursor up down
 *  5 = bluetooth off
 */
int modus = 5;
uint8_t looper = 0; // color looper

RTCdata data = {20,34,1, 5, 31,8,18}; // (5 = Freitag, 01:34:20 Uhr 31.08.2018

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
    if(tick < 30) {
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
      
      h = tick - 30;
      
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
  
  oled->setTextSize(2);  
  oled->setCursor(3, 0);
  if (data.hour < 9) oled->print('0');
  oled->print((int) data.hour);
  if (seconds%2) oled->print(' '); else oled->print(':');
  if (data.minute < 9) oled->print('0');
  oled->print((int) data.minute);
  
  flap = false;
  int t = seconds/10;
  if ((seconds+1)%10 == 0) flap=true;
  myFont(14, 16, t, flap);
  
  t = seconds - t*10;
  myFont(34, 16, t, true);
}

inline void ticking() {
  tick = (tick+1) % 40;
  
  if (tick == 0) {
    seconds++;
    if (onsec>=0 && onsec <= OFFSEC) onsec++;
  }
  if (seconds > 59) {
    seconds  = seconds % 60;
  }
}

void setup() {
  Serial.begin(9600);
      
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  // off
  //analogWrite(LED_RED, 255);
  //analogWrite(LED_GREEN, 255);
  //analogWrite(LED_BLUE, 255);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);

  Wire.begin();
  //DS3231M_set(data);
  DS3231M_get(data);

  oled->begin();
  oled->clearDisplay();
  oled->display();
  oled->setTextColor(WHITE);

  Serial.println("+++");
  delay(800);
  Serial.println("AT+GAPDEVNAME=FlipWatch");
  delay(800);
  Serial.println("AT+BLEPOWERLEVEL=-8");
  delay(800);
  Serial.println("AT+BLEHIDEN=1");
  delay(1500);
  Serial.println("ATZ");
  delay(800);
  Serial.println("+++");
  delay(800);


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
    DS3231M_get(data);
    seconds = data.second;

    // display is on for more than 1sec
    if (onsec > 0) {
      switch(modus) {
        case 0:
          while (digitalRead(BUTTON1) == LOW) {
            data.hour = (data.hour+1)%24;
            data.second = 0;
            seconds = 0;
            DS3231M_set(data);
            delay(100);
            tick = 0;
            oled->clearDisplay();
            flipClock();
            oled->display();
            delay(150);
          }
          break;
        case 1:
          while (digitalRead(BUTTON1) == LOW) {
            data.minute = (data.minute+1)%60;
            data.second = 0;
            seconds = 0;
            DS3231M_set(data);
            delay(100);
            tick = 0;
            oled->clearDisplay();
            flipClock();
            oled->display();
            delay(150);
          }
          break;
        case 2:
          Serial.println("AT+BleHidControlKey=MEDIAPREVIOUS");
          break;
        case 3:
          Serial.println("AT+BleHidControlKey=VOLUME+");
          break;
        case 4:
          Serial.println("AT+BleKeyboardCode=00-00-52-00-00");
          Serial.println("AT+BleKeyboardCode=00-00");
          break;
        default:
        ;
      }
    }

    // switch display on
    onsec = 0;
    oled->ssd1306_command(SSD1306_DISPLAYON);
  }

  if (digitalRead(BUTTON2) == LOW) {
    
    // display is on
    if (onsec != -1) {

      switch(modus) {
        case 0:
          while (digitalRead(BUTTON2) == LOW) {
            data.hour = (data.hour==0) ? 23 :(data.hour-1)%24;
            data.second = 0;
            seconds = 0;
            DS3231M_set(data);
            delay(100);
            tick = 0;
            oled->clearDisplay();
            flipClock();
            oled->display();
            delay(150);
          }
          break;
        case 1:
          while (digitalRead(BUTTON2) == LOW) {
            data.minute = (data.minute==0) ? 59 :(data.minute-1)%60;
            data.second = 0;
            seconds = 0;
            DS3231M_set(data);
            delay(100);
            tick = 0;
            oled->clearDisplay();
            flipClock();
            oled->display();
            delay(150);
          }
          break;
        case 2:
          Serial.println("AT+BleHidControlKey=MEDIANEXT");
          break;
        case 3:
          Serial.println("AT+BleHidControlKey=VOLUME-");
          break;
        case 4:
          Serial.println("AT+BleKeyboardCode=00-00-51-00-00");
          Serial.println("AT+BleKeyboardCode=00-00");
          break;
        default:
        ;
      }

      onsec = 0;
  
    // display is off  
    } else {
      // run through colors 
      while (digitalRead(BUTTON2) == LOW) {
        digitalWrite(LED_RED, (looper & 0b00000001) == 0b00000001);
        digitalWrite(LED_GREEN, (looper & 0b00000010) == 0b00000010);
        digitalWrite(LED_BLUE, (looper & 0b00000100) == 0b00000100);
        delay(500);
        looper++;
        if (looper>7) {
          looper=0;
          oled->ssd1306_command(SSD1306_DISPLAYON);
          oled->clearDisplay();
          oled->setTextSize(1);  
          oled->setCursor(0, 0);

          modus = (modus+1)%6;
          switch(modus) {
            case 0:
              oled->print("\nset hours ");
              oled->print("\n   +/-");
              break;
            case 1:
              oled->print("\nset minute");
              oled->print("\n   +/-");
              break;
            case 2:
              Serial.println("AT+BLEPOWERLEVEL=-8");
              oled->print("\n   media ");
              oled->print("\n prev/next");
              break;
            case 3:
              Serial.println("AT+BLEPOWERLEVEL=-8");
              oled->print("\nvolume -/+");
              break;
            case 4:
              Serial.println("AT+BLEPOWERLEVEL=-8");
              oled->print("\n cursor");
              oled->print("\n up/down");
              break;
            case 5:
              Serial.println("AT+BLEPOWERLEVEL=-40");
              oled->print("\nBluetooth\n");
              oled->print("\n   off");
              break;
            default:
            ;
          }
          oled->display();
          delay(1000);
          oled->ssd1306_command(SSD1306_DISPLAYOFF);
          digitalWrite(OLED_CLK, LOW);
        }
      }
    }
    
  }

}

