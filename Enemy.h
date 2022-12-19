#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
  
  public:
  
    int enemyX;
    int enemyY;

    Enemy();

    Enemy(int x, int y);

    void moveLeft();
    void moveRight();
  
};

#endif
