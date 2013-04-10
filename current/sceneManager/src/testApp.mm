#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    scenes[0] = new squareScene();
	scenes[1] = new circleScene();
	scenes[2] = new imageScene();
	
	currentScene = 0;
	
	for (int i = 0; i < 3; i++){
		scenes[i]->setup();
	}
	
}
//--------------------------------------------------------------
void testApp::update(){
	scenes[currentScene]->update();
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
	currentScene %= 3;
	
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
