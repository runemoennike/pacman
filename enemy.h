#ifndef ENEMY_H
#define ENEMY_H

using namespace std;

class cEnemy {
	public:
		enum eDirection {
			UP, DOWN, LEFT, RIGHT
		};
		enum eStatus {
            NONE, PLAYER_CONTACT
		};

		cEnemy();
		void connectLevelClass(cLevel *lvl);
		void connectSfxEngineClass(cSfxEngine *sfxe);
		void connectPlayerClass(cPlayer *pl);

		void doAI();
		void doMove();
		eStatus checkPosition();

		void setDirection(eDirection newDirection);
		eDirection getDirection();
		void changeDirection(eDirection desiredDirection);

		void setPosition(int x, int y);
		int getX();
		int getY();

		bool getHurtable();
		void setHurtable(bool hurtable);

        void setRespawn(bool respawnState, int destX, int destY);
        bool getRespawn();

		int getXTile();
		int getYTile();
		bool isExactTile();

	private:
		int x;
		int y;
		eDirection direction;
		eDirection desiredDirection;

		int tickCounter;
		int ticksToMove;
		int movePerTick;
		bool stuck;

		bool isHurtable;
		int hurtableTickCount;

		bool respawnState;
		int respDestX;
		int respDestY;

		cLevel *lvl;
		cSfxEngine *sfxe;
		cPlayer *pl;
};

#endif
