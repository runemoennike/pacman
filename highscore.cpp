#include "common.h"

cHighscoreTable::cHighscoreTable(string filename) {
	this->filename = filename;
	this->curItem = 0;

	for(int i = 0; i < 10; i ++) {
		this->scoreItem[i].score = 0;
		this->scoreItem[i].name = "";
	}
}

void cHighscoreTable::load() {
	ifstream file;

	file.open(this->filename.c_str());

    if (file.is_open()) {
		string inpLine, name, strTemp;
    	ostringstream streamTemp;
		int pos1, score, c = 0;

    	while(!file.eof()) {
			getline(file, inpLine);

			score = 0;
			name = "";

			pos1 = inpLine.find(":");
			if((unsigned)pos1 != string::npos) {
				name = inpLine.substr(0, pos1);
				strTemp = inpLine.substr(pos1 + 1);
				score = atoi(strTemp.c_str());
			}

			this->scoreItem[c].score = score;
			this->scoreItem[c].name = name;
			c ++;

			if(c >= 10)
				break;
		}
	}
	file.close();
}

void cHighscoreTable::save() {
	ofstream file;

	file.open(this->filename.c_str());

	if (file.is_open()) {
		for(int i = 0; i < 10; i ++) {
			file << this->scoreItem[i].name << ":" << this->scoreItem[i].score << "\n";
		}
	}
	file.close();
}

bool cHighscoreTable::scoreHighEnough(int score) {
	if(score > this->scoreItem[9].score) {
		return true;
	} else {
		return false;
	}
}

void cHighscoreTable::addScore(int score, string name) {
	if(score < this->scoreItem[9].score) {
		return;
	} else {
		this->scoreItem[9].score = score;
		this->scoreItem[9].name = name;
	}

	int tempScore;
	string tempName;
	for(int i = 9; i > 0; i --) {
		if(this->scoreItem[i].score > this->scoreItem[i - 1].score) {
			tempScore = this->scoreItem[i].score;
			tempName = this->scoreItem[i].name;
			this->scoreItem[i].score = this->scoreItem[i - 1].score;
			this->scoreItem[i].name = this->scoreItem[i - 1].name;
			this->scoreItem[i - 1].score = tempScore;
			this->scoreItem[i - 1].name = tempName;
		}
	}
}

int cHighscoreTable::getScore() {
	return this->scoreItem[this->curItem].score;
}

string cHighscoreTable::getName() {
	return this->scoreItem[this->curItem].name;
}

void cHighscoreTable::next() {
	this->curItem ++;

	if(this->curItem >= 10)
		this->curItem = 0;
}

void cHighscoreTable::rewind() {
	this->curItem = 0;
}

/*********************************
*
*********************************/

void scrShowHighscore(cHighscoreTable* table) {
	cGfxEngine gfxe;
	cInputEngine inpe;
	ALFONT_FONT* font;
	BITMAP* bg;
	BITMAP* buffer;

	buffer=create_bitmap(SCREEN_W,SCREEN_H);
	bg=load_bitmap("gfx/bgmenu.bmp", NULL);
	font = alfont_load_font("fonts/VillageSquare.ttf");

	while (! inpe.isKey(KEY_ESC)) {
		blit(bg, buffer, 0,0,0,0,SCREEN_W,SCREEN_H);

		alfont_text_mode(-1);
		alfont_set_font_size(font, 30);

		for(int i = 0; i < 10; i ++) {
			char chScore[10];
			itoa(table->getScore(), chScore, 10);

			alfont_textout_aa(buffer, font, table->getName().c_str(), SCREEN_W/2 - 100, 215 + (i*30), COLR_HIGHSCORE);
			alfont_textout_right_aa(buffer, font, chScore, SCREEN_W/2 + 100, 215 + (i*30), COLR_HIGHSCORE);

			table->next();
		}

		blit(buffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
		rest(10);
	}

	alfont_destroy_font(font);
	destroy_bitmap(buffer);
	destroy_bitmap(bg);

	return;
}
END_OF_FUNCTION(scrShowHighscore);

void scrRecordHighscore(cHighscoreTable* table, int score) {
	cGfxEngine gfxe;
	cInputEngine inpe;
	ALFONT_FONT* font;
	BITMAP* bg;
	BITMAP* buffer;
	char edittext[16] = "";
   	int caret = 0;

	buffer=create_bitmap(SCREEN_W,SCREEN_H);
	bg=load_bitmap("gfx/bgmenu.bmp", NULL);
	font = alfont_load_font("fonts/VillageSquare.ttf");

	while (!inpe.isKey(KEY_ENTER)) {
		if(inpe.keyPressed())
      	{
        	int  newkey   = inpe.readKey();
        	char ASCII    = newkey & 0xff;
        	char scancode = newkey >> 8;

        	if(ASCII >= 32 && ASCII <= 126)
         	{
				if(caret < 12 - 1)
				{
					edittext[caret] = ASCII;
					caret++;
					edittext[caret] = '\0';
				}
         	}
         	else if(scancode == KEY_BACKSPACE)
         	{
           		if (caret > 0) caret--;
            	edittext[caret] = '\0';
         	}
    	}

      	blit(bg, buffer, 0,0,0,0,SCREEN_W,SCREEN_H);

		alfont_text_mode(-1);
		alfont_set_font_size(font, 30);

		char chScore[10];
		itoa(score, chScore, 10);

		alfont_textout_centre_aa(buffer, font, "You made it to the highscore table with a score of:", SCREEN_W/2, 210, COLR_HIGHSCORE);
		alfont_textout_centre_aa(buffer, font, chScore, SCREEN_W/2, 240, COLR_HIGHSCORE);

		alfont_textout_centre_aa(buffer, font, "Please enter your name:", SCREEN_W/2, 300, COLR_HIGHSCORE);
		alfont_textout_centre_aa(buffer, font, edittext, SCREEN_W/2, 330, COLR_HIGHSCORE);

		blit(buffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
		rest(10);
	}

	alfont_destroy_font(font);
	destroy_bitmap(buffer);
	destroy_bitmap(bg);

	table->addScore(score, edittext);

	return;
}
END_OF_FUNCTION(scrRecordHighscore);
