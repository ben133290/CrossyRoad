#ifndef GAME_H
#define GAME_H

class Game {

  public:

    // updates all the values in the game Matrix
    void updateGameMatrix();

    void playerStepUp();

    // prints the game matrix to the serial monitor
    void printMatrix();

    // there should only be one instance of the game class in use
    Game();

  private:

    // the game matrix is the matrix containing 0 where nothing, 1 where player, and 2 where enemy
    int gameMatrix[32][32];

    // player's position in index i notation
    int playerY;

    // player's position in index j notation
    int playerX;


};
#endif