#ifndef PARTICLES_H
#define PARTICLES_H

using namespace std;

#define MAX_PARTICLESPERCONTAINER 1000

class cParticleContainer {
	public:
		cParticleContainer();
		
		void create(float x, float y, float vx, float vy, int life, int color, float mass=1.0, int spec=PTLSPEC_NORMAL, int w=1, int h=1);
		void update();
		void init();
		void check(cLevel *lvl);

		
		enum {
			PTLSPEC_NORMAL
		};
	
	private:
		struct sParticle {
			float x;
			float y;
			float vx;
			float vy;
			bool exists;
			int life;
			int color;
			float mass;
			int spec;
			int w;
			int h;
		};	
		
		sParticle ptl[MAX_PARTICLESPERCONTAINER];
		float g;
};
#endif
