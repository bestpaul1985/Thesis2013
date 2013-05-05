#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    scenes.push_back(new openingScene());
    currentScene = 0;
    rect[0].set(100, 100, 100, 100);
    rect[1].set(400, 100, 100, 100);
    scenes[0]->setup();
    
}
//--------------------------------------------------------------
void testApp::update(){
	
    scenes[0]->update();
}
//--------------------------------------------------------------
void testApp::draw(){

    scenes[0]->draw();
    ofSetColor(255, 255, 255);
    ofRect(rect[0]);
    ofRect(rect[1]);

}
//--------------------------------------------------------------
void testApp::exit(){
}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
   
    if(rect[0].inside(touch.x,touch.y)){
        scenes.pop_back();
        scenes.push_back(new springScene());
    }

    if(rect[1].inside(touch.x,touch.y)){
        scenes.pop_back();
        scenes.push_back(new springScene());
    }
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    scenes[0]->touchMoved(touch);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    scenes[0]->touchUp(touch);
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    scenes[0]->touchDoubleTap(touch);
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    scenes[0]->touchCancelled(touch);
}

//--------------------------------------------------------------
void testApp::lostFocus(){
    scenes[0]->lostFocus();
}

//--------------------------------------------------------------
void testApp::gotFocus(){
    scenes[0]->gotFocus();
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
    scenes[0]->gotMemoryWarning();
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    scenes[0]->deviceOrientationChanged(newOrientation);
}
