#include "common.h"

cParticleContainer::cParticleContainer() {
	init();
}

void cParticleContainer::create(float x, float y, float vx, float vy, int life, int color, float mass, int spec, int w, int h) {
	for(int p = 0; p < MAX_PARTICLESPERCONTAINER; p ++) {
		if(! this->ptl[p].exists) {
			this->ptl[p].exists = true;
			this->ptl[p].x = x;
			this->ptl[p].y = y;
			this->ptl[p].vx = vx;
			this->ptl[p].vy = vy;
			this->ptl[p].life = life;
			this->ptl[p].color = color;
			this->ptl[p].mass = mass;
			this->ptl[p].spec = spec;
			this->ptl[p].w = w;
			this->ptl[p].h = h;
			return;
		}
	}
}

void cParticleContainer::update() {
    for(int p = 0; p < MAX_PARTICLESPERCONTAINER; p ++) {
		if(this->ptl[p].exists) {
			this->ptl[p].life --;

			this->ptl[p].x += this->ptl[p].vx;
			this->ptl[p].y += this->ptl[p].vy;

			this->ptl[p].vy += this->g * this->ptl[p].mass;
		}
	}
}

void cParticleContainer::check(cLevel *lvl) {
	for(int p = 0; p < MAX_PARTICLESPERCONTAINER; p ++) {
		if(this->ptl[p].exists) {
			switch(this->ptl[p].spec) {
				default:
				case PTLSPEC_NORMAL:
					if(this->ptl[p].y > SCREEN_H)
						this->ptl[p].exists = false;
				break;
			}

			if(this->ptl[p].spec != PTLSPEC_NORMAL) {
				if(this->ptl[p].x + this->ptl[p].w > SCREEN_W)
					this->ptl[p].vx =- fabs(this->ptl[p].vx);
				if(this->ptl[p].x < 0)
					this->ptl[p].vx = fabs(this->ptl[p].vx);
			}

			if(this->ptl[p].life < 0)
				this->ptl[p].exists = false;
		}
	}
}

void cParticleContainer::init() {
	for(int p = 0; p<MAX_PARTICLESPERCONTAINER; p ++) {
		this->ptl[p].exists = false;
		this->ptl[p].x = 0;
		this->ptl[p].y = 0;
		this->ptl[p].vx = 0;
		this->ptl[p].vy = 0;
		this->ptl[p].life = 0;
		this->ptl[p].color = 0;
		this->ptl[p].spec = PTLSPEC_NORMAL;
	}
}
