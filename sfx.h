#ifndef SFX_H
#define SFX_H

using namespace std;

#define MAX_CHANNELS 48

#define MAX_SOUNDS 32

class cSfxEngine {
	public:
		enum eSounds {
			SND_EATPILL,
			SND_EATBIGPILL,
			SND_TURN,
			SND_DIE,
			SND_NEWLEVEL,
			SND_EATGHOST	
		};
		
		cSfxEngine();
		~cSfxEngine();
		
		void loadResources();
		void unloadResources();
		void connectLevelClass(cLevel *lvl);
		
		void play(eSounds snd);
		bool sfxOn(bool change = false, bool setTo = false);
		
	private:
		cLevel *lvl;
		
		FSOUND_SAMPLE* snds[MAX_SOUNDS];
		FSOUND_STREAM* bgMusic;
};



#endif
