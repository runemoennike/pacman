#include "common.h"

int speed_counter;
int fps=0, fpst=0, fpsc=0;
GAMESTATE gamestate=GAMEOVER;

int getFPS() {
	return fps;
}

void setGamestate(GAMESTATE newState) {
    gamestate = newState;
}
GAMESTATE getGamestate() {
    return gamestate;
}

int main() {
	cHighscoreTable table("data/highscore.dat");
	int score;

	table.load();
	init();

	bool quit = false;
	while(! quit) {
		switch(scrShowMenu()) {
			case 0:
				gamestate = RUNNING;
				score = game();
				while(key[KEY_ESC]);

				if(table.scoreHighEnough(score))
					scrRecordHighscore(&table, score);

				while(key[KEY_ENTER]);
				gamestate = GAMEOVER;
			break;
			case 1:
				scrShowHighscore(&table);
				while(key[KEY_ESC]);
			break;
			case 2:
				quit = true;
			break;
		}
	}

	table.save();
	deinit();

	return 0;
}
END_OF_MAIN();

int scrShowMenu() {
	cGfxEngine gfxe;
	cInputEngine inpe;
	ALFONT_FONT* font;
	BITMAP* bg;
	BITMAP* buffer;

	buffer=create_bitmap(SCREEN_W,SCREEN_H);
	bg=load_bitmap("gfx/bgmenu.bmp", NULL);
	font = alfont_load_font("fonts/VillageSquare.ttf");

	int curItem = 0, color;

	while (! inpe.isKey(KEY_ESC)) {
		if(inpe.isKey(KEY_DOWN)) {
			curItem += 1;
			if(curItem > 2) curItem = 0;
			while(inpe.isKey(KEY_DOWN));
		} else if(inpe.isKey(KEY_UP)) {
			curItem -= 1;
			if(curItem < 0) curItem = 2;
			while(inpe.isKey(KEY_UP));
		} else if((inpe.isKey(KEY_SPACE)) || (inpe.isKey(KEY_ENTER))) {
			while((inpe.isKey(KEY_SPACE)) || (inpe.isKey(KEY_ENTER)));
			return curItem;
		}


		blit(bg, buffer, 0,0,0,0,SCREEN_W,SCREEN_H);

		alfont_text_mode(-1);
		alfont_set_font_size(font, 40);

		if(curItem == 0) color = COLR_MENUSEL; else color = COLR_MENU;
			alfont_textout_centre_aa(buffer, font, "New Game", SCREEN_W/2, 270, color);
		if(curItem == 1) color = COLR_MENUSEL; else color = COLR_MENU;
			alfont_textout_centre_aa(buffer, font, "High Scores", SCREEN_W/2, 320, color);
		if(curItem == 2) color = COLR_MENUSEL; else color = COLR_MENU;
			alfont_textout_centre_aa(buffer, font, "Quit", SCREEN_W/2, 370, color);

		blit(buffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
		rest(10);
	}

	alfont_destroy_font(font);
	destroy_bitmap(buffer);
	destroy_bitmap(bg);

	return 2;
}
END_OF_FUNCTION(scrShowMenu);

int game() {
	cGfxEngine gfxe;
	cInputEngine inpe;
	cSfxEngine sfxe;
	cLevel lvl;
	cParticleContainer ptl;
	cPlayer pl;
	cEnemy en[4];

	// Connect all the engine parts
	gfxe.connectLevelClass(&lvl);
	gfxe.connectParticleContainerClass(&ptl);
	gfxe.connectPlayerClass(&pl);
	for(int i = 0; i < MAX_ENEMIES; i ++) gfxe.connectEnemyClass(i, &en[i]);
	sfxe.connectLevelClass(&lvl);
	inpe.connectPlayerClass(&pl);
	pl.connectLevelClass(&lvl);
	pl.connectSfxEngineClass(&sfxe);
	for(int i = 0; i < MAX_ENEMIES; i ++) {
		en[i].connectLevelClass(&lvl);
		en[i].connectSfxEngineClass(&sfxe);
		en[i].connectPlayerClass(&pl);
	}

	lvl.setLevelNum(1);

	lvl.load();
	gfxe.loadGameResources();
	sfxe.loadResources();

	pl.setPosition(lvl.getPlayerStartX(), lvl.getPlayerStartY());
	for(int i = 0; i < MAX_ENEMIES; i ++) en[i].setPosition(lvl.getEnemyStartX(i), lvl.getEnemyStartY(i));

	while(! inpe.isKey(KEY_ESC)) {
		if(gamestate == RUNNING) {
			while(speed_counter > 0) {
				/*
				* Do game logics
				*/
				pl.doMove();

				switch(pl.checkPosition()) {
                    case cPlayer::ATE_BIGPILL:
                        for(int i = 0; i < MAX_ENEMIES; i ++) en[i].setHurtable(true);
                    break;
                    default:  case cPlayer::NONE: break;
				}


				for(int i = 0; i < MAX_ENEMIES; i ++) {
					en[i].doAI();
					en[i].doMove();

					switch(en[i].checkPosition()) {
                        case cEnemy::PLAYER_CONTACT:
                            if(en[i].getRespawn()) {
                                // Ignore contact
                            } else if(en[i].getHurtable()) {
                                pl.incScore(SCORE_GHOSTKILL);
                                en[i].setRespawn(true, lvl.getEnemyStartX(i), lvl.getEnemyStartY(i));
                            } else {
                                gamestate = PLAYER_DEATH;
                            }
                        break;
                        default: case cEnemy::NONE: break;
					}
				}

                if(lvl.isCompleted()) {
                    lvl.setLevelNum(lvl.getLevelNum() + 1);
                    gamestate = REFRESH_LEVEL;
                }

				speed_counter --;
			}
		} else {
			speed_counter = 0;
		}

        /*
        * Handle input
        */
        inpe.handleGameInput();

        /*
        * State handling
        */
        if(gamestate == PLAYER_RESPAWN) {
            gamestate = REFRESH_LEVEL;
            pl.setLives(pl.getLives() - 1);

            if(pl.getLives() <= 0) {
                return pl.getScore();
            }
        }

        if(gamestate == REFRESH_LEVEL) {
            gfxe.unloadGameResources();
            sfxe.unloadResources();

            lvl.load();
            gfxe.loadGameResources();
            sfxe.loadResources();

            pl.setPosition(lvl.getPlayerStartX(), lvl.getPlayerStartY());
            for(int i = 0; i < MAX_ENEMIES; i ++) en[i].setPosition(lvl.getEnemyStartX(i), lvl.getEnemyStartY(i));

            gamestate = RUNNING;
        }

		/*
		 Render
		*/
		gfxe.renderGame();

		/*
		 Update FPS and pause
		*/
		fpst ++;
		rest(1);
	}

	gfxe.unloadGameResources();
	sfxe.unloadResources();

	return 0;
}
END_OF_FUNCTION(game);

void increment_speed_counter()
{
	if(gamestate == RUNNING) {
	    speed_counter++;
	}

	fpsc++;
	if(fpsc>=60) {
		fps=fpst;
		fpsc=0;
		fpst=0;
	}
}
END_OF_FUNCTION(increment_speed_counter);



void init() {
	allegro_init();

	install_timer();
	install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));

	srand((unsigned)time(NULL));

	initGfxSubsystem();
}

void deinit() {

}


