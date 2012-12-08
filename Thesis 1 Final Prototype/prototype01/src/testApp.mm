#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	
	ofxAccelerometer.setup();
	ofEnableAlphaBlending();
	ofBackground(30,30,30);
    
    worldP1.init();
    worldP1.setGravity(0, 100);
    worldP1.createBounds();
    worldP1.setIterations(1, 1);
    worldP1.setFPS(60);
    
    

    P1L.setup(10, ofGetHeight()-120, 0, 0);
    P1R.setup(20+115, ofGetHeight()-120, 1, 0);
    P1J.setup(ofGetWidth()-190, ofGetHeight()-115, 0, 0);
    P1F.setup(ofGetWidth()-105, ofGetHeight()-155, 1, 0);
    
    P2L.setup(ofGetWidth()-10-101, 120-95, 0, 180);
    P2R.setup(ofGetWidth()-20-101-115, 120-95, 1, 180);
    P2J.setup(190-96, 115-83, 0, 180);
    P2F.setup(105-77, 155-80,  1, 180);
    
    ofPoint tempPos(ofGetWidth()/2,ofGetHeight()/2);
    myGuy.setup(tempPos);
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    worldP1.update();
    ofPoint tempPos(0,0);
    myGuy.update(tempPos);
}

//--------------------------------------------------------------
void testApp::draw(){
    P1L.draw();
    P1R.draw();
    P1J.draw();
    P1F.draw();
    P2L.draw();
    P2R.draw();
    P2J.draw();
    P2F.draw();
    
    myGuy.draw();
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y))touch.id = 0;
    if(rect2.inside(touch.x, touch.y))touch.id = 1;
    if(rect3.inside(touch.x, touch.y))touch.id = 2;
    if(rect4.inside(touch.x, touch.y))touch.id = 3;
    
    P1L.touchDown(touch.x, touch.y, touch.id);
    P1R.touchDown(touch.x, touch.y, touch.id);    
    P1J.touchDown(touch.x, touch.y, touch.id);
    P1F.touchDown(touch.x, touch.y, touch.id);
    P2L.touchDown(touch.x, touch.y, touch.id);
    P2R.touchDown(touch.x, touch.y, touch.id);
    P2J.touchDown(touch.x, touch.y, touch.id);
    P2F.touchDown(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y))touch.id = 0;
    if(rect2.inside(touch.x, touch.y))touch.id = 1;
    if(rect3.inside(touch.x, touch.y))touch.id = 2;
    if(rect4.inside(touch.x, touch.y))touch.id = 3;
    
    P1L.touchMoved(touch.x, touch.y, touch.id);
    P1R.touchMoved(touch.x, touch.y, touch.id);
    P1J.touchMoved(touch.x, touch.y, touch.id);
    P1F.touchMoved(touch.x, touch.y, touch.id);
    P2L.touchMoved(touch.x, touch.y, touch.id);
    P2R.touchMoved(touch.x, touch.y, touch.id);
    P2J.touchMoved(touch.x, touch.y, touch.id);
    P2F.touchMoved(touch.x, touch.y, touch.id);

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y))touch.id = 0;
    if(rect2.inside(touch.x, touch.y))touch.id = 1;
    if(rect3.inside(touch.x, touch.y))touch.id = 2;
    if(rect4.inside(touch.x, touch.y))touch.id = 3;
    
    P1L.touchUp(touch.x, touch.y, touch.id);
    P1R.touchUp(touch.x, touch.y, touch.id);
    P1J.touchUp(touch.x, touch.y, touch.id);
    P1F.touchUp(touch.x, touch.y, touch.id);
    P2L.touchUp(touch.x, touch.y, touch.id);
    P2R.touchUp(touch.x, touch.y, touch.id);
    P2J.touchUp(touch.x, touch.y, touch.id);
    P2F.touchUp(touch.x, touch.y, touch.id);

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

