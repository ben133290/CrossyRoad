#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
  
  public:

    void setX(int x);
    void setY(int y);

    int getX();
    int getY();

    Enemy();

    Enemy(int x, int y);

    void moveLeft();
    void moveRight();

    void incY();

  private:

    int enemyX;
    int enemyY;
  
};

#endif
