#include "testApp.h"

// comparison routine for sort...


//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(30); //lets run at 30 fps!
    c.initialization();
}

//--------------------------------------------------------------
void testApp::update(){
	
    c.update();

}

//--------------------------------------------------------------
void testApp::draw(){
	
	c.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
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

