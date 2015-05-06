#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class cPlayer {
	public:
		enum eDirection {
			UP, DOWN, LEFT, RIGHT
		};
		enum eStatus {
            NONE, ATE_BIGPILL
		};

		cPlayer();
		void connectLevelClass(cLevel *lvl);
		void connectSfxEngineClass(cSfxEngine *sfxe);

		void doMove();
		eStatus checkPosition();

		void setDirection(eDirection newDirection);
		eDirection getDirection();
		void changeDirection(eDirection desiredDirection);

		void setPosition(int x, int y);
		int getX();
		int getY();

		int getXTile();
		int getYTile();
		bool isExactTile();

		void setLives(int lives);
		int getLives();

		void setScore(int score);
		void incScore(int amount);
		int getScore();

	private:
		int x;
		int y;
		eDirection direction;
		eDirection desiredDirection;

		int tickCounter;
		int ticksToMove;
		int movePerTick;

		int lives;
		int score;

		cLevel *lvl;
		cSfxEngine *sfxe;
};

#endif
