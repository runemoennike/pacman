#ifndef ANIMATION_H
#define ANIMATION_H

using namespace std;

#define MAX_ANIMFRAMES 32

class cAnim {
	public:
		void load(int numFrames, string basename, int frameTime);
		void unload();
		BITMAP* getBitmap();
		
		
		BITMAP *frame[MAX_ANIMFRAMES];
	private:
		int frames;
		int curFrame;
		int frameTime;
		int tickCounter;
};

#endif
