#include "Game.h"


// creates the game object and sets the initial position for the player
Game::Game() {
  
  playerY = 30;
  playerX = 15;
  playerMatrixPosUpdate();

}

// i don't think this requires much doc it's just a repeated code fragment that I wanted to have in a seperate method
void Game::playerMatrixPosUpdate() {
  gameMatrix[playerY][playerX] = 1;
  gameMatrix[playerY][(playerX+1)%32] = 1;
  gameMatrix[(playerY+1)%32][(playerX+1)%32] = 1;
  gameMatrix[(playerY+1)%32][playerX] = 1;
}

// resets game matrix to all zeros and then places all entities 
void Game::updateGameMatrix() {

  for (int i = 0; i < 32; i++) {
    for(int j = 0; j < 32; j++) {
      gameMatrix[i][j] = 0;
    }
  }
  // sets the 4x4 player to 1
  playerMatrixPosUpdate();
  for (Enemy enemy: enemies) {
    gameMatrix[enemy.enemyY][enemy.enemyX] = 2;
  }

}

// makes player step up one square by moving enemies down
void Game::playerStepUp() {

  for (Enemy enemy : enemies) { enemy.enemyY++; }

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