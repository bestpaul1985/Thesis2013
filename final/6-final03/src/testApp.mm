#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    scenes.push_back(new openingScene());
	
    currentScene = 0;
    loader = L_LEVEL02;
    rect[0].set(100, 100, 100, 100);
    rect[1].set(400, 100, 100, 100);
}
//--------------------------------------------------------------
void testApp::update(){
	
    switch (loader) {
        case L_NONE:{
            scenes[0]->update();
        }break;
        case L_MAIN:{
            delete scenes[0];
            scenes.push_back(new level01());
            scenes->setup();
            if (scenes->SETUP == true) {
                loader = L_NONE;
                currentScene = 0;
            }
        }break;
            
        case L_LEVEL01:{
            delete scenes[0];
    
            scenes.push_back(new level02());
            scenes->setup();
            if (scenes->SETUP == true) {
                currentScene = 1;
                loader = L_NONE;
            }
            
        }break;
        case L_LEVEL02:{
            delete scenes;
            scenes= NULL;
            scenes = new level02();
            scenes->setup();
            if (scenes->SETUP == true) {
                currentScene = 2;
                loader = L_NONE;
            }
        }break;
    }
    
}
//--------------------------------------------------------------
void testApp::draw(){
    switch (loader) {
        case L_NONE:{
            scenes->draw();
            ofSetColor(255, 255, 255);
            ofRect(rect[0]);
            ofRect(rect[1]);
        }break;
        case L_MAIN:{
            
        }break;
        case L_LEVEL01:{
            
        } break;
        case L_LEVEL02:{
            
        }break;
    
    }
}
//--------------------------------------------------------------
void testApp::exit(){
}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
   
    scenes->touchDown(touch);
    
    
    if(rect[0].inside(touch.x,touch.y)){
        loader = L_LEVEL02;
    }

    if(rect[1].inside(touch.x,touch.y)){
        loader = L_LEVEL01;
    }
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    scenes->touchMoved(touch);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    scenes->touchUp(touch);
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    scenes->touchDoubleTap(touch);
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    scenes->touchCancelled(touch);
}

//--------------------------------------------------------------
void testApp::lostFocus(){
    scenes->lostFocus();
}

//--------------------------------------------------------------
void testApp::gotFocus(){
    scenes->gotFocus();
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
    scenes->gotMemoryWarning();
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    scenes->deviceOrientationChanged(newOrientation);
}
