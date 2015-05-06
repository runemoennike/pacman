#ifndef INPUT_H
#define INPUT_H

using namespace std;

class cInputEngine {
	public:
		cInputEngine();
		~cInputEngine();
		void handleGameInput();
		
		void connectPlayerClass(cPlayer *pl);
		
		bool isKey(int keyCode);
		bool keyPressed();
		int readKey();
		
	private:
		cPlayer *pl;
};

#endif
