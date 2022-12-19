#include "Game.h"
#include "Enemy.h"

String inString = "";  // string to hold input
Game game = Game();

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // send an intro:
  Serial.println("Welcome to the serial monitor version of Crossy Road!");
  Serial.println();
  Serial.println();
  game.playerStepUp();
  Serial.println();
  game.playerStepUp();

}

void loop() {

}
