#ifndef GFX_H
#define GFX_H

using namespace std;

#define TILE_W 32
#define TILE_H 32
#define MAP_OFFSET_X 80
#define MAP_OFFSET_Y 64

class cGfxEngine {
	public:
		cGfxEngine();
		~cGfxEngine();

		void loadGameResources();
		void unloadGameResources();

		void connectLevelClass(cLevel *lvl);
		void connectPlayerClass(cPlayer *pl);
		void connectEnemyClass(int idx, cEnemy *en);
		void connectParticleContainerClass(cParticleContainer *ptl);

		void renderGame();

	private:
		enum eDirection {
			UP, DOWN, LEFT, RIGHT, eDirection_COUNT
		};
		typedef cAnim tSprite[eDirection_COUNT];

		cLevel *lvl;
		cParticleContainer *ptl;
		cPlayer *pl;
		cEnemy *en[MAX_ENEMIES];

		BITMAP *bg;
		BITMAP *buffer;
		ALFONT_FONT *font;

		BITMAP *floor_std;
		BITMAP *floor_doodad1;
		BITMAP *floor_doodad2;
		BITMAP *floor_doodad_wallup;
		BITMAP *wall_std;
		BITMAP *wall_front;
		BITMAP *pill_std;
		BITMAP *pill_big;
		cAnim ghostdoor;

		tSprite player;
		tSprite enemy[MAX_ENEMIES];
		tSprite hurtableEnemy;

		bool doInitDeinit;
};

void initGfxSubsystem();

#endif
