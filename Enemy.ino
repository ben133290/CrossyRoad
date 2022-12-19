#include "Enemy.h"

// constructor
Enemy::Enemy(int x, int y) {

  enemyX = x;
  enemyY = y;

}

Enemy::Enemy() {
  enemyX = 0;
  enemyY = 0;
}

// moves this enemy to the left by one
void Enemy::moveLeft() {

  if (enemyX <= 0) { enemyX = enemyX - 1; }
  if (enemyX < 0) { enemyX = 30; }
  if (enemyY > 30) { enemyY = 0; }
  
}

// moves this enemy to the right by one
void Enemy::moveRight() {

  if (enemyX != 0) { enemyX = enemyX + 1; }
  if (enemyX > 30) { enemyX = 0; }
  if (enemyY > 30) { enemyY = 0; }

}
