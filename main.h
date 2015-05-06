#ifndef MAIN_H
#define MAIN_H

using namespace std;

void init();
void deinit();
void increment_speed_counter();
int getFPS();
void setGamestate(GAMESTATE newState);
GAMESTATE getGamestate();

int scrShowMenu();
int game();

#endif
