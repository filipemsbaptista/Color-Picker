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

	color = ofColor(255, 255, 255, 255);
}

void testApp::update(){

}

void testApp::draw(){
	ofBackgroundGradient(ofColor::gray,ofColor(80, 30, 50, 255), OF_GRADIENT_CIRCULAR);
	
	if(visible){
		fbo.begin();
		ofEnableAlphaBlending();  
		
		ofSetColor(255,255,255);
		img.draw(0, rectHeight + margin);
		
		ofSetColor(color);
		ofFill();
		ofRect(0, 0, img.getWidth()/3, rectHeight);
		ofDisableAlphaBlending();
		fbo.end();

		glEnable(GL_BLEND);  
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  

		ofSetColor(255,255,255);

		fbo.draw(ofGetWidth() - fbo.getWidth() - 20, ofGetHeight() - fbo.getHeight() - 20);
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
		if(mouseX < ofGetWidth() - 20 && mouseX > ofGetWidth() - 20 - img.width && mouseY < ofGetHeight() - 20 && mouseY > ofGetHeight() - 20 - img.height){
			fbo.begin();
			GLubyte RGB[3];
			float x = fbo.getWidth() - (ofGetWidth() - mouseX - 20);
			float y = fbo.getHeight() - (ofGetHeight() - mouseY - 20);

			glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &RGB[0]);
			color = ofColor(RGB[0], RGB[1], RGB[2], 255);
			cout << "Color: (" << RGB[0] << ", " << RGB[1] << ", " << RGB[2] << ")"  << endl;
			fbo.end();
		}
	}
}