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
    ofxAccelerometer.setForceSmoothing(0.95f);
	//If you want a landscape oreintation 
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);
	
	ofBackground(30);
    ofEnableAlphaBlending();
    
    // setup world A
    world_A.init();
    world_A.setFPS(60);
    world_A.setGravity(0,-100);
    world_A.setIterations(1, 1);
    
    // setup world B
    world_B.init();
    world_B.setFPS(60);
    world_B.setGravity(0, 100);
    world_B.setIterations(1, 1);

    control_A.setup(0);
    control_B.setup(1);

    
    char_A.setup(world_A, world_B,
                 control_A.diff,
                 control_A.bSmallLeft,
                 control_A.bSmallRight,
                 control_A.bLeft,
                 control_A.bRight,
                 rope_A.bFixedMove,
                 ofPoint(384,512),
                 0);
    
    char_B.setup(world_B, world_A,
                 control_B.diff,
                 control_B.bSmallLeft,
                 control_B.bSmallRight,
                 control_B.bLeft,
                 control_B.bRight,
                 rope_B.bFixedMove,
                 ofPoint(384,512),
                 1);
 
    
    rope_A.setup(char_A.getPos,0);
    rope_B.setup(char_B.getPos,1);
    
    ropeJoint_A.setup(world_B,0);
    ropeJoint_B.setup(world_A,1);
    
    item[0].setPhysics(1, 0, 0);
    item[0].isFixed();
    item[0].setup(world_A.getWorld(), w/3, h/3, 20, 20);
    item[1].setPhysics(1, 0, 0);
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
    
//    ofRectangle temp(100,400,200,50);
//    obstacle1.setup(world_B.getWorld(), temp);

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
    
    ropeJoint_A.update(rope_A.bFixedMove,
                       control_A.bSwingLeft,
                       control_A.bSwingRight,
                       control_A.diff,
                       rope_A.length,
                       char_A.getPos);
    
    ropeJoint_B.update(rope_B.bFixedMove,
                       control_B.bSwingLeft,
                       control_B.bSwingRight,
                       control_B.diff,
                       rope_B.length,
                       char_B.getPos);
    
}

//--------------------------------------------------------------
void testApp::draw(){

    control_A.draw();
    control_B.draw();
    
    char_A.draw();
    char_B.draw();
    
    ropeJoint_A.draw();
    ropeJoint_B.draw();
    
    ofSetColor(ofColor::blueViolet);
    item[0].draw();
    item[1].draw();
    
    ofSetColor(255);
    ground_A.draw();
    ground_B.draw();
   
//    obstacle1.draw();
    
   
    
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

