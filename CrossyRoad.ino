#include "Game.h"
#include "Enemy.h"
#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK  8
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

String inString = "";  // string to hold input
Game game = Game();
int score = 0;
int colorSpeed = 0;

void updateLEDS() {
  unsigned char x, y;
  for(y=0; y<matrix.height(); y++) {
    for(x=0; x<matrix.width(); x++) {
      int value = game.getValueAtPos(x, y);
      if (value == 0) {
        matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));
      }
      if (value == 1) {
        matrix.drawPixel(x, y, matrix.Color333(15, 15, 5));
      }
      if (value == 2) {
        matrix.drawPixel(x, y, matrix.Color333(15, 0, colorSpeed));
      }
      if (value == 3) {
        matrix.drawPixel(x, y, matrix.Color333(0, colorSpeed, 15));
      }
      if (value == 4) {
        matrix.drawPixel(x, y, matrix.Color333(1, 0, 0));
      }
      if (value == 5) {
        matrix.drawPixel(x, y, matrix.Color333(15, 15, 0));
      }
    }
  }
}

// is called when player collides with an enemy
void displayGameOver() {
  matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  // draw an 'X' in red
  matrix.drawLine(0, 0, 31, 31, matrix.Color333(7, 0, 0));
  matrix.drawLine(31, 0, 0, 31, matrix.Color333(7, 0, 0));
  delay(1000);
  matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  // draw game over
  matrix.setCursor(3, 2);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print("GAME");
  matrix.setCursor(6, 11);   // next line
  matrix.print("OVER");
  delay(4000);
  matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  matrix.setTextColor(matrix.Color333(0,1,5));
  matrix.setCursor(1, 1);   // next line
  matrix.print("Score");
  matrix.setTextColor(matrix.Color333(0,7,2));
  matrix.setCursor(1, 12);
  matrix.print(score);
  matrix.setCursor(1, 22);
  if (score <= 25) { 
    matrix.setTextColor(matrix.Color333(7,0,0));
    matrix.print("Bad!");
    }
  if (score > 25 && score <= 50 ) { 
    matrix.setTextColor(matrix.Color333(0,0,7));
    matrix.print("OK!");
    }
  if (score > 50 && score <= 75) {
    matrix.setTextColor(matrix.Color333(0,7,0));
    matrix.print("Nice!");
  }
  if (score > 75) {
    matrix.setTextColor(matrix.Color333(0,7,0));
    matrix.print('G');
    matrix.setTextColor(matrix.Color333(7,7,0));
    matrix.print('R');
    matrix.setTextColor(matrix.Color333(7,0,0));
    matrix.print('E');
    matrix.setTextColor(matrix.Color333(7,0,7));
    matrix.print('A');
    matrix.setTextColor(matrix.Color333(0,0,7));
    matrix.print('T');
  }
  delay(10000);
  matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
}

// 'chicken', 32x32px
const unsigned char chicken [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x03, 0xa8, 0x02, 0x00, 
	0x00, 0x88, 0x06, 0x00, 0x00, 0x84, 0x0e, 0x00, 0x00, 0x42, 0x16, 0x00, 0x00, 0x41, 0xe6, 0x00, 
	0x00, 0x24, 0x04, 0x00, 0x00, 0x24, 0x08, 0x00, 0x00, 0x12, 0x08, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x02, 0x40, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x06, 0xc0, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 144)
//const int epd_bitmap_allArray_LEN = 1;
//const unsigned char* epd_bitmap_allArray[1] = {
	//epd_bitmap_chicken
//};

void displayIntro() {
  matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  // draw game over
  matrix.setCursor(1, 3);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(7,7,0));
  matrix.print("Cross the ");
  matrix.setCursor(1, 20);
  matrix.print("Road!");
  delay(1000);

  //display Chicken
  matrix.fillRect(0, 0, 32, 32, matrix.Color333(0, 0, 0));
  matrix.drawBitmap(0, 0, chicken, 32, 32, matrix.Color333(7, 7, 7));
  matrix.drawLine(14, 31, 14, 28, matrix.Color333(15, 15, 0));
  matrix.drawLine(17, 31, 17, 28, matrix.Color333(15, 15, 0));
  matrix.drawPixel(13, 31, matrix.Color333(15, 15, 0));
  matrix.drawPixel(16, 31, matrix.Color333(15, 15, 0));
  matrix.drawLine(6, 19, 7, 19, matrix.Color333(15, 15, 0));
  matrix.drawPixel(7, 20, matrix.Color333(15, 0, 0));
  delay(1000);  
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(2000000);
  matrix.begin();
  // send an intro:
  Serial.println("Welcome to the serial monitor version of Crossy Road!");
  Serial.println();
  Serial.println();

  displayIntro();
  //game.playerStepUp();

}

int enemySpeed = 1; // framerate
uint32_t prevTime = 0; // For frame-to-frame interval timing
bool updated = false;
uint32_t t = 0;


void loop() {

  updateLEDS();

  t = millis();
  if (t - prevTime > (1000 / enemySpeed)) { 
  game.shiftEnemies();
  prevTime = t;
  }
  

  if(Serial.available()) // if there is data comming
  {
    String command = Serial.readStringUntil('\n'); // read string until meet newline character

    if (command == "u") {
      game.playerStepUp();
      score++;
    }
    if (command == "r") { 
      game.playerStepRight(); 
    }
    if (command == "l") {
      game.playerStepLeft();
    }
  }

  if(game.getGameOver()) {
    displayGameOver();
    Serial.println("GameOver!");
    // ends programm
    exit(0);
  }

  enemySpeed = 16 + (score / 10);
  if (score / 10 < 15) {
    colorSpeed = score / 10;
  } else {
    colorSpeed = 15;
  }

}





//if player up button : game.playerstepup();
