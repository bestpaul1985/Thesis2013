#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    
	scenes[0] = new openingScene();
    scenes[1] = new squareScene();
	scenes[2] = new circleScene();
	scenes[3] = new imageScene();
    scenes[4] = new springScene();
	
	currentScene = 0;
	
	for (int i = 0; i < SCENE_NUMBER; i++){
		scenes[i]->setup();
        scenes[i]->goToScene = i+1;
        scenes[4]->goToScene = 0;
	}
	
}
//--------------------------------------------------------------
void testApp::update(){
	scenes[currentScene]->update();
    
    for (int i = 0; i < SCENE_NUMBER; i++){
        if (scenes[i]->end == true) {
            currentScene=scenes[i]->goToScene;
            scenes[i]->end = false;
        }
    }

}
//--------------------------------------------------------------
void testApp::draw(){
	scenes[currentScene]->draw();
}
//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    
    if (currentScene != 4) {
        currentScene++;
        currentScene %= SCENE_NUMBER;
    }
	
//	((circleScene*)scenes[1])->sayHello();
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
