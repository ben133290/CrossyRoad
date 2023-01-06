#ifndef GAME_H
#define GAME_H

#include "Enemy.h"

class Game {

  public:

    // gets set to true if player collides with an enemy
    bool isGameOver = false;

    // updates all the values in the game Matrix
    void updateGameMatrix();

    // prints out positions of all enemies in the game to serial monitor
    void printEnemiesPos();

    // call this method when the button for moving up is pressed
    void playerStepUp();

    // prints the game matrix to the serial monitor
    void printMatrix();

    // returns the value of the matrix at the given cordinates
    int getValueAtPos(int x, int y);

    void shiftEnemies();

    // there should only be one instance of the game class in use
    Game();

  private:

    void playerMatrixPosUpdate();

    // this array contains all enemies on the board
    Enemy enemies[10];

    // the game matrix is the matrix containing 0 where nothing, 1 where player, and 2 where enemy
    int gameMatrix[32][32];

    // player's position in index i notation
    int playerY;

    // player's position in index j notation
    int playerX;

    


};
#endif