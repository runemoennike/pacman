#include "common.h"

BITMAP* cAnim::getBitmap() {
	this->tickCounter ++;
	if(this->tickCounter == this->frameTime) {
		this->tickCounter = 0;
		this->curFrame ++;
		if(this->curFrame == this->frames) {
			this->curFrame = 0;
		}
	}
			
	return this->frame[this->curFrame];
}

void cAnim::load(int numFrames, string basename, int frameTime) {
	this->curFrame = 0;
	this->tickCounter = 0;
	this->frames = numFrames;
	this->frameTime = frameTime;
	
	ostringstream streamTemp;
	for(int i = 1; i <= numFrames; i++) {
		streamTemp.str("");
		streamTemp << basename << i << ".bmp";
		this->frame[i - 1] = load_bitmap(streamTemp.str().c_str(), NULL);
	}
}

void cAnim::unload() {
	for(int i = 0; i < this->frames; i++) {
		destroy_bitmap(this->frame[i]);	
	}	
}
