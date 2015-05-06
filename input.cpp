#include "common.h"

cInputEngine::cInputEngine() {
	install_keyboard();
}

cInputEngine::~cInputEngine() {
	clear_keybuf();
}

void cInputEngine::handleGameInput() {
	if(this->isKey(KEY_UP)) {
		pl->changeDirection(cPlayer::UP);
	} else if(this->isKey(KEY_DOWN)) {
		pl->changeDirection(cPlayer::DOWN);
	} else if(this->isKey(KEY_LEFT)) {
		pl->changeDirection(cPlayer::LEFT);
	} else if(this->isKey(KEY_RIGHT)) {
		pl->changeDirection(cPlayer::RIGHT);
	}

	if((getGamestate() == PLAYER_DEATH) && (this->isKey(KEY_SPACE))) {
	    setGamestate(PLAYER_RESPAWN);
	}
}

bool cInputEngine::isKey(int keyCode) {
	return key[keyCode];
}

bool cInputEngine::keyPressed() {
	return keypressed();
}

int cInputEngine::readKey() {
	return readkey();
}

void cInputEngine::connectPlayerClass(cPlayer *pl) {
	this->pl = pl;
}
