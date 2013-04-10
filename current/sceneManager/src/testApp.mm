#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	scenes[0] = new openingScene();
    scenes[1] = new circleScene();
    scenes[2] = new squareScene();
	scenes[3] = new circleScene();
	scenes[4] = new imageScene();
	
	currentScene = 0;
	
	for (int i = 0; i < SCENE_NUMBER; i++){
		scenes[i]->setup();
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
    
	currentScene++;
	currentScene %= SCENE_NUMBER;
	
	((circleScene*)scenes[1])->sayHello();
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}
//--------------------------------------------------------------
void testApp::screen(){

}
