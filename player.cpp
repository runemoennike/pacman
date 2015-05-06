#include "common.h"

cPlayer::cPlayer() {
	this->tickCounter = 0;
	this->ticksToMove = 2;
	this->movePerTick = 4;
	this->direction = RIGHT;
	this->desiredDirection = this->direction;
	this->lives = 3;
	this->score = 0;
}

void cPlayer::connectLevelClass(cLevel *lvl) {
	this->lvl = lvl;
}
void cPlayer::connectSfxEngineClass(cSfxEngine *sfxe) {
	this->sfxe = sfxe;
}

void cPlayer::doMove() {
	this->tickCounter ++;

	if(this->tickCounter == this->ticksToMove) {
		this->tickCounter = 0;

		switch(this->direction) {
			case UP:
				this->y -= this->movePerTick;
				if(! this->lvl->tileWalkable(this->getXTile(), this->getYTile())) {
					this->y = (this->getYTile() + 1) * TILE_H;
				}
			break;
			case DOWN:
				this->y += this->movePerTick;
				if(! this->lvl->tileWalkable(this->getXTile(), this->getYTile() + 1)) {
					this->y = this->getYTile() * TILE_H;
				}
			break;
			case LEFT:
				this->x -= this->movePerTick;
				if(! this->lvl->tileWalkable(this->getXTile(), this->getYTile())) {
					this->x = (this->getXTile() + 1) * TILE_W;
				}
			break;
			case RIGHT:
				this->x += this->movePerTick;
				if(! this->lvl->tileWalkable(this->getXTile() + 1, this->getYTile())) {
					this->x = this->getXTile() * TILE_W;
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

cPlayer::eStatus cPlayer::checkPosition() {
    eStatus result = NONE;

	if(this->isExactTile()) {
		int xt = this->getXTile();
		int yt = this->getYTile();

		switch(this->lvl->tileObj(xt, yt)) {
			case cLevel::OBJ_PILL_STD:
				this->lvl->setTileObj(xt, yt, cLevel::OBJ_NONE);
				this->sfxe->play(cSfxEngine::SND_EATPILL);
				this->incScore(SCORE_PILL_STD);
			break;
			case cLevel::OBJ_PILL_BIG:
				this->lvl->setTileObj(xt, yt, cLevel::OBJ_NONE);
				this->sfxe->play(cSfxEngine::SND_EATBIGPILL);
				this->incScore(SCORE_PILL_BIG);
				result = ATE_BIGPILL;
			break;
			default: case cLevel::OBJ_NONE: break;
		}
	}

	return result;
}

void cPlayer::setDirection(eDirection newDirection) {
	this->direction = newDirection;
}
cPlayer::eDirection cPlayer::getDirection() {
	return this->direction;
}
void cPlayer::changeDirection(eDirection desiredDirection) {
	this->desiredDirection = desiredDirection;
}


void cPlayer::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}
int cPlayer::getX() {
	return this->x;
}
int cPlayer::getY() {
	return this->y;
}

int cPlayer::getXTile() {
	return this->x / TILE_W;
}
int cPlayer::getYTile() {
	return this->y / TILE_H;
}
bool cPlayer::isExactTile() {
	if((this->x % TILE_W == 0) && (this->y % TILE_H == 0)) {
		return true;
	} else {
		return false;
	}
}

void cPlayer::setLives(int lives) {
    this->lives = lives;
}
int cPlayer::getLives() {
    return this->lives;
}

void cPlayer::setScore(int score) {
    this->score = score;
}
void cPlayer::incScore(int amount) {
    this->score += amount;
}
int cPlayer::getScore() {
    return this->score;
}
