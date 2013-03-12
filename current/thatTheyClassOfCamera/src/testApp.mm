#include "testApp.h"
static int w = 768;
static int h = 1024;
static int offset = 10;
static int pts_A[] = {0+offset,100,    offset,offset,    w-offset, offset,    w-offset,100};
static int nPts_A  = 4*2;

static int pts_B[] = {0+offset,h-100,  offset,h-offset,    w-offset,h-offset,    w-offset,h-100};
static int nPts_B  = 4*2;


//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.9f);
	//If you want a landscape oreintation 
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);
	
	ofBackground(30);
    ofEnableAlphaBlending();
    
    // setup world A
    world_A.init();
    world_A.setFPS(60);
    world_A.setGravity(0,-10);
    world_A.enableGrabbing();
    world_A.setIterations(1, 1);
    
    // setup world B
    world_B.init();
    world_B.setFPS(60);
    world_B.setGravity(0, 10);
    world_B.enableGrabbing();
    world_B.setIterations(1, 1);

    char_A.setup(world_A, world_B);
    char_B.setup(world_B, world_A);
 
    rope_A.setup(char_B.getPos, 0);
    rope_B.setup(char_A.getPos, 1);
    
    item[0].setPhysics(1, 0.5, 1);
    item[0].setup(world_A.getWorld(), w/3, h/3, 20, 20);
    item[1].setPhysics(1, 0.5, 1);
    item[1].setup(world_B.getWorld(), w/3, h/3, 20, 20);
    
    for (int i=0; i<nPts_A; i+=2) {
		float xA = pts_A[i];
		float yA = pts_A[i+1];
		ground_A.addVertex(xA, yA);
	}
    
    ground_A.setPhysics(0.0 ,0.0, 0.0);
    ground_A.create(world_A.getWorld());
    
    for (int i=0; i<nPts_B; i+=2) {
        float xB = pts_B[i];
        float yB = pts_B[i+1];
        ground_B.addVertex(xB, yB);
    }
    ground_B.setPhysics(0.0 ,0.0, 0.0);
    ground_B.create(world_B.getWorld());
    
    //camera staff
    camPos_A.set(0, h);
    cam_A.setNearClip(-1);
    cam_A.setFarClip(-100);
    cam_A.enableOrtho();
    cam_A.setPosition(camPos_A.x,camPos_A.y, -1);
    cam_A.setScale(1, -1, 1);
    
    camPos_B.set(0, h);
    cam_B.setNearClip(-1);
    cam_B.setFarClip(-100);
    cam_B.enableOrtho();
    cam_B.setPosition(camPos_B.x,camPos_B.y, -1);
    cam_B.setScale(1, -1, 1);
    
    setupViewports();
    
}
//--------------------------------------------------------------
void testApp::setupViewports(){
 
    view_A.x = 0;
    view_A.y= 0;
    view_A.width =  w;
    view_A.height = h/2;
}

//--------------------------------------------------------------
void testApp::update(){
    
    cam_A.setPosition(camPos_A.x,camPos_A.y, -1);
    cam_B.setPosition(camPos_B.x,camPos_B.y, -1);
    
    world_A.update();
    world_B.update();
    
    //Character
    char_A.update();
    char_B.update();
    
    rope_A.update(ofxAccelerometer.getForce(), char_A.getPos);
    rope_B.update(ofxAccelerometer.getForce(), char_B.getPos);
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    ofVec2f circle(0,0);
    
    cam_A.begin();
    ofCircle(circle, 30);
    drawScene(0);
    cam_A.end();
    
    
    cam_B.begin();
    drawScene(1);
    cam_B.end();
    
    
    ofDrawBitmapString("Rope_A\nworld: " + ofToString(rope_A.endPos,0) + "\n" +
                       "Screen: " + ofToString(cam_A.worldToScreen(rope_A.endPos),0) + "\n" +
                       "camPos: " + ofToString(camPos_A,0), 100,100);
  
    ofDrawBitmapString("Rope_B\nworld: " + ofToString(rope_B.endPos,1) + "\n" +
                       "Screen: " + ofToString(cam_A.worldToScreen(rope_B.endPos),1) + "\n" +
                       "camPos: " + ofToString(camPos_B,1), 400,512);

}
//--------------------------------------------------------------
void testApp::drawScene(int iCameraDraw){
    if (iCameraDraw == 0) {
        char_A.draw();
        
        rope_A.draw();
        
        ofSetColor(ofColor::blueViolet);
        item[0].draw();
        
        ofSetColor(255);
        ground_A.draw();

        
    }else if (iCameraDraw == 1){
    
        char_B.draw();
        rope_B.draw();
        
        ofSetColor(ofColor::blueViolet);
        item[1].draw();
        
        ofSetColor(255);
        ground_B.draw();
    }
}
//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){

    if (touch.numTouches == 1) {
        preTouch_A.x= touch.x;
        preTouch_A.y = touch.y;
    }else if(touch.numTouches == 2){
        preTouch_B.x= touch.x;
        preTouch_B.y = touch.y;
    }
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){

    if (touch.numTouches == 1) {
        ofPoint diff;
        diff.x = touch.x - preTouch_A.x;
        diff.y = touch.y - preTouch_A.y;
        
        camPos_A.x -= diff.x;
        camPos_A.y -= diff.y;
        
        preTouch_A.x = touch.x;
        preTouch_A.y = touch.y;
    }else if(touch.numTouches == 2){
        if (touch.id == 0) {
         
        ofPoint diff;
        diff.x = touch.x - preTouch_B.x;
        diff.y = touch.y - preTouch_B.y;
        
        camPos_B.x -= diff.x;
        camPos_B.y -= diff.y;
        
        preTouch_B.x = touch.x;
        preTouch_B.y = touch.y;
    }
    }
   
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    camPos_A.set(0, h);
    camPos_B.set(0, h);
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

