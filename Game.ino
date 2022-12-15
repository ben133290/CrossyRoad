#include "Game.h"


// creates the game object and sets the initial position for the player
Game::Game() {
  
  playerY = 31;
  playerX = 15;
  gameMatrix[playerY][playerX] = 1;
  
}

// resets game matrix to all zeros and then places all entities 
void Game::updateGameMatrix() {

  for (int i = 0; i < 32; i++) {
    for(int j = 0; j < 32; j++) {
      gameMatrix[i][j] = 0;
    }
  }
  gameMatrix[playerY][playerX] = 1;

}

// makes player step up one square
void Game::playerStepUp() {

  playerY = playerY - 1;

}

// prints out the game matrix on the serial monitor
void Game::printMatrix() {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++) {
      Serial.print(gameMatrix[i][j]);
      Serial.print(", ");
    }
    Serial.println();
  }
}

