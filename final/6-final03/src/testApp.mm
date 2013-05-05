#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    scenes[0] = new openingScene();
    scenes[1] = new level01();
    scenes[2] = new level02();
    
    currentScene = 1;
    scenes[1]->update();
    
}
//--------------------------------------------------------------
void testApp::update(){
    scenes[currentScene]->update();
}
//--------------------------------------------------------------
void testApp::draw(){
   
}
//--------------------------------------------------------------
void testApp::exit(){
}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    scenes[currentScene]->touchDown(touch);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    scenes[currentScene]->touchMoved(touch);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    scenes[currentScene]->touchUp(touch);
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    scenes[currentScene]->touchDoubleTap(touch);
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    scenes[currentScene]->touchCancelled(touch);
}

//--------------------------------------------------------------
void testApp::lostFocus(){
    scenes[currentScene]->lostFocus();
}

//--------------------------------------------------------------
void testApp::gotFocus(){
    scenes[currentScene]->gotFocus();
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
    scenes[currentScene]->gotMemoryWarning();
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    scenes[currentScene]->deviceOrientationChanged(newOrientation);
}
