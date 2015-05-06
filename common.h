

#include <iostream>
#include <allegro.h>
#include <alfont.h>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <FMOD/fmod.h>
#include <FMOD/fmod_errors.h>


using namespace std;

enum GAMESTATE {
	RUNNING,
	GAMEOVER,
	PLAYER_DEATH,
	PLAYER_RESPAWN,
	REFRESH_LEVEL
};


#define MAX_ENEMIES 4

#define COLR_MENU makecol(100,100,100)
#define COLR_MENUSEL makecol(255,200,100)
#define COLR_HIGHSCORE makecol(240,200,100)
#define COLR_HUD2 makecol(255,255,255)
#define COLR_HUD1 makecol(200,200,200)

#define SCORE_PILL_STD 3
#define SCORE_PILL_BIG 20
#define SCORE_GHOSTKILL 100

#define GHOST_HURTABLE_TIME 600

#include "highscore.h"
#include "main.h"
#include "level.h"
#include "sfx.h"
#include "player.h"
#include "enemy.h"
#include "particles.h"
#include "animation.h"
#include "gfx.h"
#include "input.h"

float getRndFloat(float min, float max);
int getRndInt(int min, int max);
float fabs(float number);
