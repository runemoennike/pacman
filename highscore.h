#ifndef HIGHSCORE_H
#define HIGHSCORE_H

using namespace std;

class cHighscoreTable {
	public:
		cHighscoreTable(string filename);
		void load();
		void save();
		bool scoreHighEnough(int score);
		void addScore(int score, string name);
		int getScore();
		string getName();
		void next();
		void rewind();
		
	private:
		struct sScoreItem {
			int score;
			string name;	
		};
		sScoreItem scoreItem[10];
		int curItem;
		string filename;
};

void scrShowHighscore(cHighscoreTable* table);
void scrRecordHighscore(cHighscoreTable* table, int score);

#endif
