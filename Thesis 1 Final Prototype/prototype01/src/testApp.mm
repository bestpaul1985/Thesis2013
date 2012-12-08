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
    
    float w = 100;
    float h = 100;
    ofColor color(30,30,30);
    P1L.setup(40, ofGetHeight()-h-30, w, h, color);
    P1R.setup(60+w, ofGetHeight()-h-30, w, h, color);
    P1J.setup(ofGetWidth()-140, ofGetHeight()-h-30, w, h,color);
    
    P2L.setup(ofGetWidth()-40-w, 30,  w, h, color);
    P2R.setup(ofGetWidth()-70-2*w, 30, w, h, color);
    P2J.setup(40, 30, w, h, color);
    
    
    
    guy.loadImage("image/guy1.png");
    P1.setup(worldP1, 384, 500, guy.getWidth(),guy.getHeight());
    P1.img = &guy;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
//    worldP1.update();
    P1.update(P1L.bPressed, P1R.bPressed, 100, 10, 0.98);
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    P1L.draw();
    P1R.draw();
    P1J.draw();
    P2L.draw();
    P2R.draw();
    P2J.draw();
    P1.draw();
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
    P2L.touchDown(touch.x, touch.y, touch.id);
    P2R.touchDown(touch.x, touch.y, touch.id);
    P2J.touchDown(touch.x, touch.y, touch.id);

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
    P2L.touchMoved(touch.x, touch.y, touch.id);
    P2R.touchMoved(touch.x, touch.y, touch.id);
    P2J.touchMoved(touch.x, touch.y, touch.id);
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
    P2L.touchUp(touch.x, touch.y, touch.id);
    P2R.touchUp(touch.x, touch.y, touch.id);
    P2J.touchUp(touch.x, touch.y, touch.id);
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

