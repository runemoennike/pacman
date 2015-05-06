#include "common.h"

cGfxEngine::cGfxEngine() {
}

cGfxEngine::~cGfxEngine() {
}

void cGfxEngine::renderGame() {
	blit(this->bg, this->buffer, 0,0,0,0,SCREEN_W,SCREEN_H);

	for(int x = 0; x < LVL_W; x ++) {
		for(int y = 0; y < LVL_H; y ++) {
			switch(this->lvl->tileBase(x, y)) {
				case cLevel::BASE_FLOOR_STD:
					draw_sprite(this->buffer, this->floor_std, MAP_OFFSET_X + x * TILE_W, MAP_OFFSET_Y + y * TILE_H);
				break;
				case cLevel::BASE_FLOOR_DOODAD1:
					draw_sprite(this->buffer, this->floor_doodad1, MAP_OFFSET_X + x * TILE_W, MAP_OFFSET_Y + y * TILE_H);
				break;
				case cLevel::BASE_FLOOR_DOODAD2:
					draw_sprite(this->buffer, this->floor_doodad2, MAP_OFFSET_X + x * TILE_W, MAP_OFFSET_Y + y * TILE_H);
				break;
				case cLevel::BASE_FLOOR_DOODAD_WALLUP:
					draw_sprite(this->buffer, this->floor_doodad_wallup, MAP_OFFSET_X + x * TILE_W, MAP_OFFSET_Y + y * TILE_H);
				break;
				case cLevel::BASE_WALL_STD:
					draw_sprite(this->buffer, this->wall_std, MAP_OFFSET_X + x * TILE_W, MAP_OFFSET_Y + y * TILE_H);
				break;
				case cLevel::BASE_WALL_FRONT:
					draw_sprite(this->buffer, this->wall_front, MAP_OFFSET_X + x * TILE_W, MAP_OFFSET_Y + y * TILE_H);
				break;
				case cLevel::BASE_GHOSTDOOR:
					draw_sprite(this->buffer, this->ghostdoor.getBitmap(), MAP_OFFSET_X + x * TILE_W, MAP_OFFSET_Y + y * TILE_H);
				break;
			}

			switch(this->lvl->tileObj(x, y)) {
				case cLevel::OBJ_PILL_STD:
					draw_sprite(this->buffer, this->pill_std, MAP_OFFSET_X + x * TILE_W, MAP_OFFSET_Y + y * TILE_H);
				break;
				case cLevel::OBJ_PILL_BIG:
					draw_sprite(this->buffer, this->pill_big, MAP_OFFSET_X + x * TILE_W, MAP_OFFSET_Y + y * TILE_H);
				break;
				default: case cLevel::OBJ_NONE: break;
			}
		}
	}

	draw_sprite(this->buffer, this->player[this->pl->getDirection()].getBitmap(), MAP_OFFSET_X + pl->getX(), MAP_OFFSET_Y + pl->getY());

	for(int i = 0; i < MAX_ENEMIES; i ++) {
	    if(this->en[i]->getRespawn()) {
		    set_trans_blender(255, 255, 255, 50);
            drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
	        draw_trans_sprite(this->buffer, this->hurtableEnemy[this->en[i]->getDirection()].getBitmap(), MAP_OFFSET_X + en[i]->getX(), MAP_OFFSET_Y + en[i]->getY());
	        drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
		} else if(this->en[i]->getHurtable()) {
            draw_sprite(this->buffer, this->hurtableEnemy[this->en[i]->getDirection()].getBitmap(), MAP_OFFSET_X + en[i]->getX(), MAP_OFFSET_Y + en[i]->getY());
		} else {
		    set_trans_blender(255, 255, 255, 150);
            drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
            draw_trans_sprite(this->buffer, this->enemy[i][this->en[i]->getDirection()].getBitmap(), MAP_OFFSET_X + en[i]->getX(), MAP_OFFSET_Y + en[i]->getY());
            drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
		}
	}

	alfont_text_mode(-1);
	alfont_set_font_size(this->font, 40);
	alfont_textprintf_aa(this->buffer, this->font, 0, SCREEN_H-40, makecol(255, 255, 255), "%d", getFPS());

	alfont_set_font_size(this->font, 15);
	alfont_textout_aa(this->buffer, this->font, "Level", 0, 0, COLR_HUD1);
	alfont_textout_centre_aa(this->buffer, this->font, "Lives", SCREEN_W/2, 0, COLR_HUD1);
	alfont_textout_right_aa(this->buffer, this->font, "Score", SCREEN_W, 0, COLR_HUD1);

	alfont_set_font_size(this->font, 40);
	alfont_textprintf_aa(this->buffer, this->font, 0, 15, COLR_HUD2, "%d", 1);
	alfont_textprintf_right_aa(this->buffer, this->font, SCREEN_W, 15, COLR_HUD2, "%d", this->pl->getScore());
	alfont_textprintf_centre_aa(this->buffer, this->font, SCREEN_W/2, 15, COLR_HUD2, "%d", this->pl->getLives());


    if(getGamestate() == PLAYER_DEATH) {
        set_trans_blender(255, 255, 255, 200);
        drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
        rectfill(this->buffer, 0, 200, SCREEN_W, SCREEN_H - 200, makeacol32(0,0,0, 200));
        drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);

        alfont_set_font_size(this->font, 120);
        alfont_textout_centre_aa(this->buffer, this->font, "GHOST GOTCHA", SCREEN_W/2, SCREEN_H/2-55, COLR_HUD1);
        alfont_set_font_size(this->font, 30);
        alfont_textout_centre_aa(this->buffer, this->font, "Press [SPACE] to continue", SCREEN_W/2, SCREEN_H/2 + 50, COLR_HUD2);
    }


	blit(this->buffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H);

}

void cGfxEngine::loadGameResources() {
	this->buffer = create_bitmap(SCREEN_W, SCREEN_H);

	this->bg = load_bitmap(lvl->getBgImageFilename().c_str(), NULL);

	this->wall_std = load_bitmap("gfx/wall_std.bmp", NULL);
	this->wall_front = load_bitmap("gfx/wall_front.bmp", NULL);
	this->floor_std = load_bitmap("gfx/floor_std.bmp", NULL);
	this->floor_doodad1 = load_bitmap("gfx/floor_doodad1.bmp", NULL);
	this->floor_doodad2 = load_bitmap("gfx/floor_doodad2.bmp", NULL);
	this->floor_doodad_wallup = load_bitmap("gfx/floor_doodad_wallup.bmp", NULL);
	this->ghostdoor.load(4, "gfx/ghostdoor", 10);
	this->pill_std = load_bitmap("gfx/pill_std.bmp", NULL);
	this->pill_big = load_bitmap("gfx/pill_big.bmp", NULL);

	this->player[UP].load(4, "gfx/pacman_up", 10);
	this->player[DOWN].load(4, "gfx/pacman_down", 10);
	this->player[LEFT].load(4, "gfx/pacman_left", 10);
	this->player[RIGHT].load(4, "gfx/pacman_right", 10);

	this->enemy[0][UP].load(4, "gfx/ghost1_up", 10);
	this->enemy[0][DOWN].load(4, "gfx/ghost1_down", 10);
	this->enemy[0][LEFT].load(4, "gfx/ghost1_left", 10);
	this->enemy[0][RIGHT].load(4, "gfx/ghost1_right", 10);
	this->enemy[1][UP].load(4, "gfx/ghost2_up", 10);
	this->enemy[1][DOWN].load(4, "gfx/ghost2_down", 10);
	this->enemy[1][LEFT].load(4, "gfx/ghost2_left", 10);
	this->enemy[1][RIGHT].load(4, "gfx/ghost2_right", 10);
	this->enemy[2][UP].load(4, "gfx/ghost3_up", 10);
	this->enemy[2][DOWN].load(4, "gfx/ghost3_down", 10);
	this->enemy[2][LEFT].load(4, "gfx/ghost3_left", 10);
	this->enemy[2][RIGHT].load(4, "gfx/ghost3_right", 10);
	this->enemy[3][UP].load(4, "gfx/ghost4_up", 10);
	this->enemy[3][DOWN].load(4, "gfx/ghost4_down", 10);
	this->enemy[3][LEFT].load(4, "gfx/ghost4_left", 10);
	this->enemy[3][RIGHT].load(4, "gfx/ghost4_right", 10);

	this->hurtableEnemy[UP].load(4, "gfx/ghostx_up", 10);
	this->hurtableEnemy[DOWN].load(4, "gfx/ghostx_down", 10);
	this->hurtableEnemy[LEFT].load(4, "gfx/ghostx_left", 10);
	this->hurtableEnemy[RIGHT].load(4, "gfx/ghostx_right", 10);

	this->font = alfont_load_font("fonts/VillageSquare.ttf");
}

void cGfxEngine::unloadGameResources() {
	destroy_bitmap(this->buffer);
	destroy_bitmap(this->bg);

	destroy_bitmap(this->wall_std);
	destroy_bitmap(this->wall_front);
	destroy_bitmap(this->floor_std);
	destroy_bitmap(this->floor_doodad1);
	destroy_bitmap(this->floor_doodad2);
	destroy_bitmap(this->floor_doodad_wallup);
	this->ghostdoor.unload();
	destroy_bitmap(this->pill_std);
	destroy_bitmap(this->pill_big);

	this->player[UP].unload();
	this->player[DOWN].unload();
	this->player[LEFT].unload();
	this->player[RIGHT].unload();

	this->enemy[0][UP].unload();
	this->enemy[0][DOWN].unload();
	this->enemy[0][LEFT].unload();
	this->enemy[0][RIGHT].unload();
	this->enemy[1][UP].unload();
	this->enemy[1][DOWN].unload();
	this->enemy[1][LEFT].unload();
	this->enemy[1][RIGHT].unload();
	this->enemy[2][UP].unload();
	this->enemy[2][DOWN].unload();
	this->enemy[2][LEFT].unload();
	this->enemy[2][RIGHT].unload();
	this->enemy[3][UP].unload();
	this->enemy[3][DOWN].unload();
	this->enemy[3][LEFT].unload();
	this->enemy[3][RIGHT].unload();

	this->hurtableEnemy[UP].unload();
	this->hurtableEnemy[DOWN].unload();
	this->hurtableEnemy[LEFT].unload();
	this->hurtableEnemy[RIGHT].unload();

	alfont_destroy_font(this->font);
}

void cGfxEngine::connectLevelClass(cLevel *lvl) {
	this->lvl = lvl;
}
void cGfxEngine::connectPlayerClass(cPlayer *pl) {
	this->pl = pl;
}
void cGfxEngine::connectParticleContainerClass(cParticleContainer *ptl) {
	this->ptl = ptl;
}
void cGfxEngine::connectEnemyClass(int idx, cEnemy *en) {
	this->en[idx] = en;
}

void initGfxSubsystem() {
	int depth, res;

	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);

	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		allegro_exit();
		exit(-1);
	}

	if(alfont_init() != ALFONT_OK) {
		allegro_message("Error while initializing alfont");
	   	exit(-1);
	    allegro_exit();
	}
}



