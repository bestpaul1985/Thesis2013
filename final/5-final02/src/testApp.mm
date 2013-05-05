#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    scenes[0] = new ttScence01();
}
//--------------------------------------------------------------
void testApp::update(){
    scenes[0]->update();
}

//--------------------------------------------------------------
void testApp::draw(){
//   scenes[0]->draw();
}
//--------------------------------------------------------------
void testApp::exit(){
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
//    scenes[0]->touchDown(touch);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
//    scenes[0]->touchMoved(touch);

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
//    scenes[0]->touchUp(touch);

}
//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
void testApp::touchCancelled(ofTouchEventArgs & touch){}
void testApp::lostFocus(){}
void testApp::gotFocus(){}
void testApp::gotMemoryWarning(){}
void testApp::deviceOrientationChanged(int newOrientation){}
