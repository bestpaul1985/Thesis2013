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

    control_A.setup(0);
    control_B.setup(1);
    
    char_A.setup(world_A, world_B, control_A.diff,
                 control_A.bSmallLeft, control_A.bSmallRight,
                 control_A.bLeft, control_A.bRight,
                 0);
    
    char_B.setup(world_B, world_A, control_B.diff,
                 control_B.bSmallLeft, control_B.bSmallRight,
                 control_B.bLeft, control_B.bRight,
                 1);
 
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
    

}

//--------------------------------------------------------------
void testApp::update(){

    
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

    control_A.draw();
    control_B.draw();
    
    char_A.draw();
    char_B.draw();
    
    rope_A.draw();
    rope_B.draw();
    
    ofSetColor(ofColor::blueViolet);
    item[0].draw();
    item[1].draw();
    
    ofSetColor(255);
    ground_A.draw();
    ground_B.draw();
   
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    control_A.touchDown(touch.x, touch.y);
    control_B.touchDown(touch.x, touch.y);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    control_A.touchMove(touch.x, touch.y);
    control_B.touchMove(touch.x, touch.y);

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    control_A.touchUp(touch.x, touch.y);
    control_B.touchUp(touch.x, touch.y);

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

