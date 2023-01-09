#include "Game.h"


// creates the game object and sets the initial position for the player
Game::Game() {
  //1 for right -1 for left
  playerOrientation = 1;
  isFirstTurn = 1;
  isGameOver = false;
  playerY = 30;
  playerX = 15;
  playerMatrixPosUpdate();
  int enemyStartingYs[] = {0, 27, 8, 6, 19, 11, 15, 22, 25, 4};
  int enemyColors[] = {2, 2, 2, 2, 2, 3, 3, 3, 3, 3};
  for (int i = 0; i < 10; i++) {
    enemies[i].setX(i * 7 % 32);
    enemies[i].setY(enemyStartingYs[i]);
    enemies[i].setColor(enemyColors[i]);
  }
  updateGameMatrix();
}

int Game::positiveModulo(int i, int n) {
  return (n + (i % n)) % n;
}

// i don't think this requires much doc it's just a repeated code fragment that I wanted to have in a seperate method
void Game::playerMatrixPosUpdate() {
  gameMatrix[playerY][playerX] = 1;
  gameMatrix[playerY][(playerX+playerOrientation)%32] = 1;
  gameMatrix[positiveModulo(playerY-1, 32)][positiveModulo(playerX, 32)] = 1;
  gameMatrix[(playerY+1)%32][playerX] = 5;
  gameMatrix[positiveModulo(playerY-1, 32)][positiveModulo(playerX-playerOrientation, 32)] = 5;
  gameMatrix[positiveModulo(playerY, 32)][positiveModulo(playerX-playerOrientation, 32)] = 4;
}

bool Game::getGameOver() { return isGameOver; }

// resets game matrix to all zeros and then places all entities 
void Game::updateGameMatrix() {

  for (int i = 0; i < 32; i++) {
    for(int j = 0; j < 32; j++) {
      gameMatrix[i][j] = 0;
    }
  }
  // sets the 4x4 player to 1
  playerMatrixPosUpdate();
  for (int k = 0; k < 10; k++) {
    if (gameMatrix[enemies[k].getY()][enemies[k].getX()] == 1) {
      Serial.println("GAME OVER");
      isGameOver = true; 
    }
    else {
      gameMatrix[enemies[k].getY()][enemies[k].getX()] = enemies[k].getColor();
      gameMatrix[enemies[k].getY()][(enemies[k].getX()+1)%32] = enemies[k].getColor();
    }
    
  }

}

// makes player step up one square by moving enemies down
void Game::playerStepUp() {

  if (isFirstTurn < 13) {
    playerY--;
    isFirstTurn++;
  } else {
    // use iteration by index (does this copy the array?!)
    for (int i = 0; i < 10; i++) { 
      enemies[i].incY();
    }
  }
  updateGameMatrix();
}

// makes player step up one square right
void Game::playerStepRight() {
  playerX = (playerX + 1) % 32;
  playerOrientation = -1;
  updateGameMatrix();
}

// makes player step up one square right
void Game::playerStepLeft() {
  playerX--;
  if (playerX == -1) { playerX = 31; }
  playerOrientation = 1;
  updateGameMatrix();
}

void Game::shiftEnemies() {
  for (int i = 0; i < 10; i = i = i + 2) { 
    enemies[i].incX();
  }
  for (int i = 1; i < 10; i = i = i + 2) { 
    enemies[i].decX();
  }
  updateGameMatrix();
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

// returns the value of the matrix at the given cordinates
int Game::getValueAtPos(int x, int y) {
  return gameMatrix[y][x];
}

// prints out positions of all enemies in the game to serial monitor for debugging
void Game::printEnemiesPos() {
  for (int i = 0; i < 10; i++) {
    Serial.print("(");
    Serial.print(enemies[i].getX());
    Serial.print(", ");
    Serial.print(enemies[i].getY());
    Serial.print(")   ");
  }
  Serial.println();
}