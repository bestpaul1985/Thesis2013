#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    
	scenes[0] = new openingScene();
    scenes[1] = new springScene();
    

	currentScene = 1;
	
    scenes[0]->setup();
	scenes[1]->setup();
    
	
}
//--------------------------------------------------------------
void testApp::update(){
    
    
    if (currentScene == 3) {
        scenes[1] = new springScene();
        scenes[1]->setup();
        if (scenes[1]->end == true) {
            currentScene = 1;
        }
    }
    
    if (currentScene == 1) {
        scenes[currentScene]->update();
    }

}
//--------------------------------------------------------------
void testApp::draw(){
    if (currentScene == 1) {
        scenes[currentScene]->draw();

    }
}
//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    
    if (currentScene == 1) {
        delete scenes[1];
        currentScene = 3;
    }
    
    
    
        
//	((circleScene*)scenes[1])->sayHello();
//    scenes[currentScene]->touchDown(touch);
    
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
