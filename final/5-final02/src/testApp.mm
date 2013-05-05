#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){
    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);

    scenes[0] = new ttSceneMain();
    scenes[1] = new ttSceneLevel01();
    
    currentScene = 0;
    
    for (int i = 0; i < 2; i++){
		scenes[i]->setup();
        scenes[i]->goToScene = i+1;
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
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
void testApp::touchCancelled(ofTouchEventArgs & touch){}
void testApp::lostFocus(){}
void testApp::gotFocus(){}
void testApp::gotMemoryWarning(){}
void testApp::deviceOrientationChanged(int newOrientation){}