#include "testApp.h"
static int w = 768;
static int h = 1024;


//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.95f);
	//If you want a landscape oreintation 
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
    ground_A.setup("level01_A.txt", world_A);
    ground_B.setup("level01_B.txt", world_B);
    
    // register the listener so that we get the events
	ofAddListener(world_A.contactStartEvents, this, &testApp::contactStart_worldA);
	ofAddListener(world_A.contactEndEvents, this, &testApp::contactEnd_worldA);
    ofAddListener(world_B.contactStartEvents,this, &testApp::contactStart_worldB);
    ofAddListener(world_B.contactEndEvents,this, &testApp::contactStart_worldB);
    
    control_A.setup(0);
    control_B.setup(1);

    
    char_A.setup(world_A, world_B,
                 control_A.diff,
                 control_A.bSmallLeft,
                 control_A.bSmallRight,
                 control_A.bLeft,
                 control_A.bRight,
                 rope_A.bFixedMove,
                 ofPoint(384,500),
                 0);
    
    char_B.setup(world_B, world_A,
                 control_B.diff,
                 control_B.bSmallLeft,
                 control_B.bSmallRight,
                 control_B.bLeft,
                 control_B.bRight,
                 rope_B.bFixedMove,
                 ofPoint(384,700),
                 1);
 
    
    rope_A.setup(world_B,char_A.getPos,0);
    rope_B.setup(world_A,char_B.getPos,1);
    
 
    item[0].setPhysics(1, 0, 0);
    item[0].isFixed();
    item[0].setup(world_A.getWorld(), w/3, h/3, 20, 20);
    item[1].setPhysics(1, 0, 0);
    item[1].setup(world_B.getWorld(), w/3, h/3, 20, 20);
    
  
    //camera
    camPos_A.set(0, h);
    cam_A.setNearClip(-1);
    cam_A.setFarClip(-100);
    cam_A.enableOrtho();
    cam_A.setPosition(camPos_A.x,camPos_A.y, -100);
    cam_A.setScale(1, -1, 1);
    
    camPos_B.set(0, h);
    cam_B.setNearClip(-1);
    cam_B.setFarClip(-100);
    cam_B.enableOrtho();
    cam_B.setPosition(camPos_B.x,camPos_B.y, -1);
    cam_B.setScale(1, -1, 1);

  
    dummy.setPhysics(20.0f, 0.0f, 0.2f);
    dummy.setup(world_B.getWorld(),500,500, 30,30);
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
    
    ofPoint newPos(char_B.getPos.x,char_A.getPos.y);
    rope_A.update(ofxAccelerometer.getForce(), newPos);
    
    
    newPos.set(char_A.getPos.x,char_B.getPos.y);
    rope_B.update(ofxAccelerometer.getForce(), newPos);

    cam_A.setPosition(char_A.getPos.x- w/2,camPos_A.y, -1);
    cam_B.setPosition(char_B.getPos.x- w/2,camPos_B.y, -1);
    
    ofPoint screenPos = cam_A.worldToScreen(char_A.getPos);
    ofPoint worldpos = cam_B.screenToWorld(screenPos);
}

//--------------------------------------------------------------
void testApp::draw(){

    cam_A.begin();
    drawScene(0);
    cam_A.end();
    
    cam_B.begin();
    drawScene(1);
    cam_B.end();
    
    control_A.draw();
    control_B.draw();
    
    
    
    
    ofDrawBitmapStringHighlight("Rope_A\nworld: " + ofToString(char_A.getPos,0) + "\n" +
                       "Screen: " + ofToString(cam_A.worldToScreen(char_A.getPos),0) + "\n" +
                       "camPos: " + ofToString(camPos_A,0), 50,50);
    
    ofDrawBitmapStringHighlight("Rope_B\nworld: " + ofToString(char_B.getPos,1) + "\n" +
                       "Screen: " + ofToString(cam_B.worldToScreen(char_B.getPos),1) + "\n" +
                       "camPos: " + ofToString(camPos_B,1), 600,950);
    
      
    
}
//-------------------------------------------------------------
void testApp::drawScene(int iCameraDraw){

    if (iCameraDraw == 0) {
        char_A.draw();
//        rope_B.draw();
//        ropeJoint_B.draw();
        item[0].draw();
        ofSetColor(255);
        ground_A.draw();
    }else if(iCameraDraw == 1){
        char_B.draw();
//        rope_A.draw();
//        ofRect(finalPos.x, finalPos.y,30, 30);
//        ropeJoint_A.draw();
//        dummy.draw();
        ofSetColor(ofColor::blueViolet);
        item[1].draw();
        ground_B.draw();
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
