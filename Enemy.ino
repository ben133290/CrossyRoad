#include "Enemy.h"

Enemy::Enemy(int x, int y) {

  enemyX = x;
  enemyY = y;

}

void Enemy::moveLeft() {
  if (enemyX != 0) {
    enemyX = enemyX - 1;
  }
}
