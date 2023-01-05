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

void updateLEDS() {
  unsigned char x, y;
  for(y=0; y<matrix.height(); y++) {
    for(x=0; x<matrix.width(); x++) {
      if (game.getValueAtPos(x, y) == 1) {
        matrix.drawPixel(x, y, matrix.Color333(0, 7, 7));
      }
      if (game.getValueAtPos(x, y) == 2) {
        matrix.fillRect(x, y, 4, 2, matrix.Color333(7, 0, 0));
      }
    }
  }
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(500000);
  matrix.begin();

  // send an intro:
  Serial.println("Welcome to the serial monitor version of Crossy Road!");
  Serial.println();
  Serial.println();
  game.playerStepUp();
  Serial.println();
  game.playerStepUp();

}

#define FPS 4         // Maximum frames-per-second
uint32_t prevTime = 0; // For frame-to-frame interval timing
bool updated = false;


void loop() {

  uint32_t t;
  while(((t = millis()) - prevTime) < (1000 / FPS));
  prevTime = t;

  //display uf led
  updateLEDS();

  if(Serial.available()) // if there is data comming
  {
    String command = Serial.readStringUntil('\n'); // read string until meet newline character

    if(command == "UP")
    {
      game.playerStepUp();
      Serial.println("LED is turned ON"); // send action to Serial Monitor
    }
  }

}



//if player up button : game.playerstepup();
