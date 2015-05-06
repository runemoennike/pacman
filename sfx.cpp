#include "common.h"

cSfxEngine::cSfxEngine() {
	if (FSOUND_GetVersion() < FMOD_VERSION) {
		ostringstream streamTemp;
		streamTemp << "Wrong FMOD dll version. Expected version " << FMOD_VERSION << ".";
        allegro_message(streamTemp.str().c_str());
		this->sfxOn(true, false);
    }
    
    if (!FSOUND_Init(32000, MAX_CHANNELS, 0)) {
        allegro_message(FMOD_ErrorString(FSOUND_GetError()));
		this->sfxOn(true, false);
    }
}

cSfxEngine::~cSfxEngine() {
	FSOUND_Close();	
}

void cSfxEngine::loadResources() {
	this->snds[SND_EATPILL]=FSOUND_Sample_Load(FSOUND_FREE, "sfx/eatpill2.ogg", 0,0,0);
	this->snds[SND_EATBIGPILL]=FSOUND_Sample_Load(FSOUND_FREE, "sfx/eatpill1.ogg", 0,0,0);
}

void cSfxEngine::play(eSounds snd) {
	if (sfxOn()) FSOUND_PlaySound(FSOUND_FREE, this->snds[snd]);
}

void cSfxEngine::unloadResources() {
	FSOUND_Sample_Free(this->snds[SND_EATPILL]);
	FSOUND_Sample_Free(this->snds[SND_EATBIGPILL]);
}

void cSfxEngine::connectLevelClass(cLevel *lvl) {
	this->lvl = lvl;	
}

bool cSfxEngine::sfxOn(bool change, bool setTo) {
	static bool state = true;
	
	if(change) 
		state = setTo;
	
	return state;
}
