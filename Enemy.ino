#include "Enemy.h"

Enemy::Enemy() {
  carColor = 0;
  enemyX = 0;
  enemyY = 0;
}

void Enemy::setX(int x) {
  enemyX = x;
}

void Enemy::setColor(int color) {
  carColor = color;
}

int Enemy::getColor() {
  return carColor;
}

void Enemy::setY(int y) {
  enemyY = y;
}

int Enemy::getX() {
  return enemyX;
}

int Enemy::getY() {
  return enemyY;
}

void Enemy::incY() {
  enemyY = (enemyY + 1) % 32;
}

void Enemy::incX() {
  enemyX = (enemyX + 1) % 32;
}

void Enemy::decX() {
  enemyX = enemyX - 1;
  if (enemyX == -1) { enemyX = 31; }
}
