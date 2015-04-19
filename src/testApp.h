#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		ofFbo fbo;					//Buffer to draw color picker
		float rectHeight;			//Height of the color shower
		float margin;				//Margin between color shower and color picker

		ofImage img;				//Image object for color picker
		
		bool visible;				//Is color picker visible
		
		ofColor color1, color2;	

		float colorPickerIndex;		//0 - Left picker, 1 - Right picker
};