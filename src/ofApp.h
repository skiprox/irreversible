#pragma once

#include "ofMain.h"
#include "Flower.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void mouseReleased(int x, int y, int button);
		void keyReleased(int key);

		vector<Flower> flowers;

		float petalScaler;

		int incrementer;
		
};
