#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(30);
	ofBackground(255, 255, 255, 255);
	visible = true;
	
	img.loadImage("color-picker.png");

	rectHeight = 25;
	margin = 5;

	fbo.allocate(img.width, img.height + rectHeight + margin, GL_RGB32F_ARB);

	color1 = ofColor(255, 255, 255);
	color2 = ofColor(ofColor::gray);

	colorPickerIndex = 0;
}

void testApp::update(){
	if(colorPickerIndex < 0)
		colorPickerIndex = 0;
	else
		if(colorPickerIndex > 1)
			colorPickerIndex = 1;
}

void testApp::draw(){
	ofBackgroundGradient(color2, color1, OF_GRADIENT_CIRCULAR);
	
	if(visible){
		fbo.begin();
		ofEnableAlphaBlending();  
		
		//Draw color gradient image
		ofSetColor(255,255,255);
		img.draw(0, rectHeight + margin);
		
		//Draw first picker
		ofSetColor(color1);
		ofFill();
		ofRect(2, 2, img.getWidth()/3, rectHeight);
		
		//Draw second picker
		ofSetColor(color2);
		ofFill();
		ofRect(img.getWidth() - (img.getWidth()/3) - 2, 2, img.getWidth()/3, rectHeight);

		ofDisableAlphaBlending();
		fbo.end();

		glEnable(GL_BLEND);  
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  

		ofSetColor(255,255,255);

		fbo.draw(ofGetWidth() - fbo.getWidth() - 20, ofGetHeight() - fbo.getHeight() - 20);

		//Draw color picker text
		if(colorPickerIndex == 0)
			ofSetColor(0, 0, 0);
		else
			ofSetColor(0, 0, 0, 128);
		ofDrawBitmapString( "Periphery", ofGetWidth() - 20 - fbo.getWidth(), ofGetHeight() - 20 - fbo.getHeight() - 5 );
		
		if(colorPickerIndex == 1)
			ofSetColor(0, 0, 0);
		else
			ofSetColor(0, 0, 0, 128);
		ofDrawBitmapString( "Center", ofGetWidth() - 20 - fbo.getWidth()/3, ofGetHeight() - 20 - fbo.getHeight() - 5 );
	}	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == OF_KEY_RETURN){
		visible = !visible;
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

void testApp::mouseReleased(int x, int y, int button){
	if(visible){
		//Check click on color gradient
		if(mouseX < ofGetWidth() - 20 && mouseX > ofGetWidth() - 20 - img.width && mouseY < ofGetHeight() - 20 && mouseY > ofGetHeight() - 20 - img.height){
			fbo.begin();
			GLubyte RGB[3];
			float x = fbo.getWidth() - (ofGetWidth() - mouseX - 20);
			float y = fbo.getHeight() - (ofGetHeight() - mouseY - 20);

			glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &RGB[0]);
			if(colorPickerIndex == 0)
				color1 = ofColor(RGB[0], RGB[1], RGB[2], 255);
			else
				color2 = ofColor(RGB[0], RGB[1], RGB[2], 255);	
			fbo.end();
		}

		//Check click on first picker
		if(mouseX < (ofGetWidth() - 20 - img.getWidth() + 2) + img.getWidth()/3 &&
			mouseX > ofGetWidth() - 20 - img.getWidth() + 2 &&
			mouseY < ofGetHeight() - 20 - fbo.getHeight() + 2 + rectHeight &&
			mouseY > ofGetHeight() - 20 - fbo.getHeight() + 2){
				colorPickerIndex = 0;
				cout << "Clicked on first picker!" << endl;
		}

		//Check click on second picker
		if(mouseX < ofGetWidth() - 20 - 2 &&
			mouseX > ofGetWidth() - 20 - 2 - img.getWidth()/3 &&
			mouseY < ofGetHeight() - 20 - fbo.getHeight() + 2 + rectHeight &&
			mouseY > ofGetHeight() - 20 - fbo.getHeight() + 2){
				colorPickerIndex = 1;
				cout << "Clicked on second picker!" << endl;
		}

	}
}