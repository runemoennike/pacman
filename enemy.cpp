#include "common.h"

cEnemy::cEnemy() {
	this->tickCounter = 0;
	this->ticksToMove = 1;
	this->movePerTick = 1;
	this->x = 10 * TILE_W;
	this->y = 7 * TILE_H;
	this->direction = LEFT;
	this->desiredDirection = this->direction;
	this->stuck = false;
	this->isHurtable = false;
	this->respawnState = false;
	this->respDestX = 0;
	this->respDestY = 0;
}

void cEnemy::connectLevelClass(cLevel *lvl) {
	this->lvl = lvl;
}
void cEnemy::connectSfxEngineClass(cSfxEngine *sfxe) {
	this->sfxe = sfxe;
}
void cEnemy::connectPlayerClass(cPlayer *pl) {
	this->pl = pl;
}

void cEnemy::doAI() {
	if((this->stuck)) {
		int newDirection = getRndInt(1, 3);
		switch(this->getDirection()) {
			case UP:
			case DOWN:
				switch(newDirection) {
					case 1: this->changeDirection(RIGHT); break;
					default: case 2: this->changeDirection(LEFT); break;
				}
			break;
			case LEFT:
			case RIGHT:
				switch(newDirection) {
					case 1: this->changeDirection(UP); break;
					default: case 2: this->changeDirection(DOWN); break;
				}
			break;
		}
		this->stuck = false;
	}
}

void cEnemy::doMove() {
	this->tickCounter ++;

    if(this->respawnState) {
	    if(this->tickCounter == this->ticksToMove * 3) {
            this->tickCounter = 0;

            this->direction = DOWN;

            if(this->x < this->respDestX) {
                this->x ++;
            } else if (this->x > this->respDestX) {
                this->x --;
            }
            if(this->y < this->respDestY) {
                this->y ++;
            } else if (this->y > this->respDestY) {
                this->y --;
            }

            if((this->x == this->respDestX) && (this->y == this->respDestY)) {
                this->respawnState = false;
                this->isHurtable = false;
            }
	    }
    } else if(this->isHurtable) {
        this->hurtableTickCount ++;
        if(this->hurtableTickCount > GHOST_HURTABLE_TIME) {
            this->isHurtable = false;
        }
	}

	if(! this->respawnState) {
        if(this->tickCounter == this->ticksToMove) {
            this->tickCounter = 0;

            if(! this->stuck) {
                switch(this->direction) {
                    case UP:
                        this->y -= this->movePerTick;
                        if(! this->lvl->tileEnemyWalkable(this->getXTile(), this->getYTile())) {
                            this->y = (this->getYTile() + 1) * TILE_H;
                            this->stuck = true;
                        }
                    break;
                    case DOWN:
                        this->y += this->movePerTick;
                        if(! this->lvl->tileEnemyWalkable(this->getXTile(), this->getYTile() + 1)) {
                            this->y = this->getYTile() * TILE_H;
                            this->stuck = true;
                        }
                    break;
                    case LEFT:
                        this->x -= this->movePerTick;
                        if(! this->lvl->tileEnemyWalkable(this->getXTile(), this->getYTile())) {
                            this->x = (this->getXTile() + 1) * TILE_W;
                            this->stuck = true;
                        }
                    break;
                    case RIGHT:
                        this->x += this->movePerTick;
                        if(! this->lvl->tileEnemyWalkable(this->getXTile() + 1, this->getYTile())) {
                            this->x = this->getXTile() * TILE_W;
                            this->stuck = true;
                        }
                    break;
                }
            }

            if(this->desiredDirection != this->direction) {
                if(this->isExactTile()) {
                    this->direction = this->desiredDirection;
                }
            }
        }
	}
}

cEnemy::eStatus cEnemy::checkPosition() {
    eStatus result = NONE;

    if((this->pl->getXTile() == this->getXTile()) && (this->pl->getYTile() == this->getYTile())) {
        result = PLAYER_CONTACT;
    }

    return result;
}

void cEnemy::setDirection(eDirection newDirection) {
	this->direction = newDirection;
}
cEnemy::eDirection cEnemy::getDirection() {
	return this->direction;
}
void cEnemy::changeDirection(eDirection desiredDirection) {
	this->desiredDirection = desiredDirection;
}


void cEnemy::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}
int cEnemy::getX() {
	return this->x;
}
int cEnemy::getY() {
	return this->y;
}

int cEnemy::getXTile() {
	return this->x / TILE_W;
}
int cEnemy::getYTile() {
	return this->y / TILE_H;
}
bool cEnemy::isExactTile() {
	if((this->x % TILE_W == 0) && (this->y % TILE_H == 0)) {
		return true;
	} else {
		return false;
	}
}

bool cEnemy::getHurtable() {
    return this->isHurtable;
}
void cEnemy::setHurtable(bool hurtable) {
    this->isHurtable = hurtable;
    this->hurtableTickCount = 0;
}

void cEnemy::setRespawn(bool respawnState, int destX, int destY) {
    this->respawnState = respawnState;
    this->respDestX = destX;
    this->respDestY = destY;
}
bool cEnemy::getRespawn() {
    return this->respawnState;
}
