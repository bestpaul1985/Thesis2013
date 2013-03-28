#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.95f);
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);
	
	ofBackground(30);
    ofEnableAlphaBlending();
    
    // setup world A
    world_A.init();
    world_A.setFPS(60);
    world_A.setGravity(0,-9.8);
    world_A.setIterations(1, 1);
    world_A.registerGrabbing();
    // setup world B
    world_B.init();
    world_B.setFPS(60);
    world_B.setGravity(0, 9.8);
    world_B.setIterations(1, 1);
    world_B.registerGrabbing();
    //Map
    ground_A.setup(1, 0, world_A);
    ground_B.setup(1, 1, world_B);
    
    // register the listener so that we get the events
	ofAddListener(world_A.contactStartEvents, this, &testApp::contactStart_worldA);
	ofAddListener(world_A.contactEndEvents, this, &testApp::contactEnd_worldA);
    ofAddListener(world_B.contactStartEvents,this, &testApp::contactStart_worldB);
    ofAddListener(world_B.contactEndEvents,this, &testApp::contactStart_worldB);
    
    
    control_A.setup(0);
    control_B.setup(1);

    char_A.setup(world_A, world_B,
                 control_A,
                 ofPoint(384,380),
                 0);
    
    char_B.setup(world_B, world_A,
                 control_B,
                 ofPoint(384,700),
                 1);
    
    //rope
    rope_A.setup(char_A, char_B,control_A,control_B, 0);
    rope_B.setup(char_A, char_B,control_A,control_B, 1);
    rope_A.setupContactListener();
    rope_B.setupContactListener();
}
//--------------------------------------------------------------
void testApp::contactStart_worldA(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        //a == polygone, b == circle
       
    }

}
//--------------------------------------------------------------
void testApp::contactEnd_worldA(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
            

    }
}
//--------------------------------------------------------------
void testApp::contactStart_worldB(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        
    }

}
//--------------------------------------------------------------
void testApp::contactEnd_worldB(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
    
    }
}
//--------------------------------------------------------------
void testApp::update(){

    world_A.update();
    world_B.update();

    //Character
    char_A.update();
    char_B.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofColor dark(80);
    ofBackgroundGradient(dark, ofColor::black);

    drawScene(0);
    drawScene(1);
    
    rope_A.update();
    rope_A.accelerometerUpdate(ofxAccelerometer.getForce());
    rope_B.update();
    rope_B.accelerometerUpdate(ofxAccelerometer.getForce());

    rope_A.draw();
    rope_B.draw();
    
    ofDrawBitmapStringHighlight("Rope_A\nworld: " + ofToString(char_A.getPos,0) + "\n" +
                       "Screen: " + ofToString(cam_A.worldToScreen(char_A.getPos),0) + "\n" +
                       "camPos: " + ofToString(camPos_A,0), 50,50);
    
    ofDrawBitmapStringHighlight("Rope_B\nworld: " + ofToString(char_B.getPos,0) + "\n" +
                       "Screen: " + ofToString(cam_B.worldToScreen(char_B.getPos),0) + "\n" +
                       "camPos: " + ofToString(camPos_B,0), 570,950);
    
    //    control_A.draw();
    //    control_B.draw();
    
    
}
//-------------------------------------------------------------
void testApp::drawScene(int iCameraDraw){

    if (iCameraDraw == 0) {
//        char_A.drawBox2dObject();
        ground_A.draw();
        ground_A.drawPolyLine();
        char_A.draw();
    }else if(iCameraDraw == 1){
//        char_B.drawBox2dObject();
        ground_B.draw();
        ground_B.drawPolyLine();
        char_B.draw();
    }


}
//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    control_A.touchDown(touch.x, touch.y,touch.id);
    control_B.touchDown(touch.x, touch.y,touch.id);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    control_A.touchMove(touch.x, touch.y,touch.id);
    control_B.touchMove(touch.x, touch.y,touch.id);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    control_A.touchUp(touch.x, touch.y,touch.id);
    control_B.touchUp(touch.x, touch.y,touch.id);
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

