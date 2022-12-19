#include "Game.h"
#include "Enemy.h"

String inString = "";  // string to hold input
Game game;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // send an intro:
  Serial.println("Welcome to the serial monitor version of Crossy Road!");
  Serial.println();
  game.printMatrix();
  Serial.println();
  game.playerStepUp();
  game.updateGameMatrix();
  game.printMatrix();

}

void loop() {

}
