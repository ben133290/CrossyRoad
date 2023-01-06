#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
  
  public:

    void setX(int x);
    void setY(int y);
    void setColor(int color);

    int getX();
    int getY();
    int getColor();

    Enemy();

    Enemy(int x, int y);

    void moveLeft();
    void moveRight();

    void incY();
    void incX();
    void decX();

  private:

    int carColor;
    int enemyX;
    int enemyY;
  
};

#endif
