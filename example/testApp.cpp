#include "testApp.h"



//using namespace veryHandy;


//--------------------------------------------------------------
void testApp::setup(){	
	p1.load("ikStaar_palette_10x10-2.png", 4);
	p2.load("ikStaar_palette_10x10.png", 10);
	p3.load("ikStaar_palette_10x10-2.png", 4);
	p4.load("ikStaar_palette_10x10-2.png", 4);
	
	last = 0;
}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(100,100,100);
	
}

void testApp::drawPalette(ofxGraphicPalette p, int x, int y) {
	ofPushMatrix();
		for(int i = 0; i < p.getColorCount(); i++) {
			ofColor col = p.getColor(i);
			ofSetColor(col.r, col.g, col.b, 255);
			ofFill();
			ofRect(x, y, 10, 10);
			ofTranslate(10, 0, 0);
		}
	ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xffffff);

	string tstamp = getTimestampAsString();
	unsigned long epoch = parseTimestamp( tstamp );
	
	stringstream s;
	s << "tstamp " << tstamp << endl << "epoch " << epoch;
	ofDrawBitmapString( s.str(), 20, 20);	

	stringstream s2;
	s2 << "palette #1 no. colors " << p1.getColorCount() << endl << "pallete #2 no. colors: " << p2.getColorCount();
	ofDrawBitmapString( s2.str(), 20, 50);	
	
	drawPalette(p1, 10, 80);
	drawPalette(p3, 10, 100);
	drawPalette(p4, 10, 120);
	drawPalette(p2, 10, 160);
	
	if(last < epoch ) {
		last = epoch;
		p3.rotateRight(1);
		p4.rotateLeft(1);
	}
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	if (key == 's' || key == 'S'){
	}
	
	
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
