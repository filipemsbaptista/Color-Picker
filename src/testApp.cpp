#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(30);
	ofBackground(255, 255, 255, 255);
	visible = true;
	/*
    w = 200;
    h = 200;
    cx = w/2;
    cy = h/2;
	*/
    /*
    img.allocate(w,h,OF_IMAGE_COLOR);

    for (float y=0; y<h; y++) {
        for (float x=0; x<w; x++) {
                        
            float angle = atan2(y-cy,x-cy)+PI;
            float dist = ofDist(x,y,cx,cy);
            float hue = angle/TWO_PI*255;
            float sat = ofMap(dist,0,w/4,0,255,true);
            float bri = ofMap(dist,w/4,w/2,255,0,true);
            
            img.setColor(x,y,ofColor::fromHsb(hue,sat,bri));
        }
    }

    img.reloadTexture(); 
	pixels = img.getPixels();
	*/
	img.loadImage("color-picker.png");
	//img.width = w;
	//img.height = h;
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F_ARB);
	cout << "FBO: "<< fbo.getWidth() << "x" <<fbo.getHeight();

	color = ofColor(255, 255, 255, 255);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackgroundGradient(ofColor::gray,ofColor(80, 30, 50, 255), OF_GRADIENT_CIRCULAR);
	
	if(visible){
		fbo.begin();
		ofEnableAlphaBlending();  
		
		ofSetColor(255,255,255);
		img.draw(fbo.getWidth() - img.width - 20, fbo.getHeight() - img.height - 20);
		
		ofSetColor(color);
		ofFill();
		ofRect(fbo.getWidth() - img.width - 20, fbo.getHeight() - img.height - 50, img.getWidth()/3, 25);
		ofDisableAlphaBlending();
		fbo.end();
		//fbo.draw(ofGetWidth() - fbo.getWidth() - 20, ofGetHeight() - fbo.getHeight() - 20);
		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_BLEND);  
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);  

		fbo.draw(0, 0);
	}	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == OF_KEY_RETURN){
		visible = !visible;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(visible){
		if(mouseX < ofGetWidth() - 20 && mouseX > ofGetWidth() - 20 - img.width && mouseY < ofGetHeight() - 20 && mouseY > ofGetHeight() - 20 - img.height){
			fbo.begin();
			GLubyte RGB[3];
			glReadPixels(mouseX, mouseY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &RGB[0]);
			color = ofColor(RGB[0], RGB[1], RGB[2], 255);
			cout << "Color: (" << RGB[0] << ", " << RGB[1] << ", " << RGB[2] << ")"  << endl;
			fbo.end();
		}
	}
	
	/*
	unsigned char *pixels = img.getPixels();	
	int index = mouseY*img.width*3 + mouseX*3;
	int red = pixels[index];
	int green = pixels[index+1];
	int blue = pixels[index+2];
	printf(">>>>%i >>>%i >>>%i\n",red,green,blue);
	*/
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}