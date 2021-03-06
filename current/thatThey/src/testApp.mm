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
    
	//If you want a landscape oreintation 
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);
	
	ofBackground(30);
    ofEnableAlphaBlending();
    
    // setup world A
    world_A.init();
    world_A.setFPS(60);
    world_A.setGravity(0,-10);
    world_A.setIterations(1, 1);
    
    // setup world B
    world_B.init();
    world_B.setFPS(60);
    world_B.setGravity(0, 10);
    world_B.setIterations(1, 1);

    char_A.setPhysics(1, 0.5, 1);
    char_A.setup(world_A.getWorld(), w/3, h/2, 50, 50);
    char_B.setPhysics(1, 0.5, 1);
    char_B.setup(world_B.getWorld(), w*2/3, h/2, 50, 50);
    
    charDummy_A.setPhysics(0, 0, 0);
    charDummy_A.setup(world_B.getWorld(), w/3, h/2, 60, 60);
    charDummy_B.setPhysics(0, 0, 0);
    charDummy_B.setup(world_A.getWorld(), w*2/3, h/2, 60, 60);
    
    ropeEnd_A.setPhysics(1, 0.1, 0.1);
    ropeEnd_A.setup(world_B.getWorld(), w/2, h/2, 5);
    ropeEnd_B.setPhysics(1, 0.1, 0.1);
    ropeEnd_B.setup(world_A.getWorld(), w/2, h/2, 5);
    
    rope_A.setup(world_B.getWorld(), charDummy_A.body, ropeEnd_A.body);
    rope_B.setup(world_A.getWorld(), charDummy_B.body, ropeEnd_B.body);
    
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
    
    // update dummy location
    charDummy_A.setPosition(char_A.getPosition().x, char_A.getPosition().y);
    charDummy_B.setPosition(char_B.getPosition().x, char_B.getPosition().y);
   
    // points for ropeEnd
    ofPoint accelFrc = ofxAccelerometer.getForce();
    ofPoint pos_A, pos_B;
    float dist;
    float catchUpSpeed = 0.09f;
    float strength = 8.0f;
    float damping  = 0.7f;
    
    dist = ofDist(accelXeno_B.x,accelXeno_B.y, char_B.getPosition().x, char_B.getPosition().y);
    
    // ropeEnd B calculation
    pos_B = char_B.getPosition();
    if(accelFrc.y>0.15){
        //set X
        if      (accelFrc.x >= 0)   pos_B.x = ofMap(accelFrc.x, 0, 0.6, char_B.getPosition().x, 768,true);
        else if (accelFrc.x < 0)    pos_B.x = ofMap(accelFrc.x, 0, -0.6, char_B.getPosition().x, 0,true);
        //set Y
        accelFrc.y = ofClamp(accelFrc.y, 0.15, 0.6);
        pos_B.y -= ofMap(accelFrc.y, 0.15, 0.6, 0, char_B.getPosition().y);
        
        // Xeno to pos
        accelXeno_B = catchUpSpeed * pos_B + (1-catchUpSpeed) * accelXeno_B;
//        ropeEnd_B.setPosition(accelXeno_B);
        ropeEnd_B.addAttractionPoint(accelXeno_B,strength);
        ropeEnd_B.setDamping(damping);
        rope_B.setLength(dist);
        
    }
    else {
        if (dist > 50) {
            accelXeno_B = catchUpSpeed * pos_B + (1-catchUpSpeed) * accelXeno_B;
            ropeEnd_B.setPosition(accelXeno_B);
        }
        else ropeEnd_B.setPosition(pos_B.x,pos_B.y);
    }
    
    
    // ropeEnd A calculation
    pos_A = char_A.getPosition();
    if(accelFrc.y<-0.15){
        //set X
        if      (accelFrc.x >= 0)   pos_A.x = ofMap(accelFrc.x, 0, 0.6, char_A.getPosition().x, 768,true);
        else if (accelFrc.x < 0)    pos_A.x = ofMap(accelFrc.x, 0, -0.6, char_A.getPosition().x, 0,true);
        //set Y
        accelFrc.y = ofClamp(accelFrc.y,-0.6,-0.15);
        pos_A.y += ofMap(accelFrc.y, -0.15, -0.6,  0, 1024-char_A.getPosition().y);
        // Xeno to pos
        accelXeno_A = catchUpSpeed * pos_A + (1-catchUpSpeed) * accelXeno_A;
        ropeEnd_A.setPosition(accelXeno_A);
    }
    else{
        dist = ofDist(accelXeno_A.x,accelXeno_A.y, char_A.getPosition().x, char_A.getPosition().y);
        if (dist > 50) {
            accelXeno_A = catchUpSpeed * pos_A + (1-catchUpSpeed) * accelXeno_A;
            ropeEnd_A.setPosition(accelXeno_A);
        }
        else ropeEnd_A.setPosition(pos_A.x,pos_A.y);
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
	
    ofSetColor(ofColor::wheat,200);
    char_A.draw();
    ofSetColor(ofColor::gold,200);
    char_B.draw();
    
    
    ofSetColor(100,100);
    charDummy_A.draw();
    charDummy_B.draw();
    
    
    ofSetColor(255,200);
    rope_A.draw();
    rope_B.draw();
    
    ofSetColor(ofColor::darkTurquoise,200);
    ropeEnd_A.draw();
    ropeEnd_B.draw();
    
    ofSetColor(ofColor::blueViolet);
    item[0].draw();
    ofSetColor(ofColor::cadetBlue);
    item[1].draw();
    
//    ofSetLineWidth(3);
    ofSetColor(255);
    ground_A.draw();
    ground_B.draw();
    
    
    ofSetColor(255, 100);
    ofCircle(accelXeno_A,20);
    ofCircle(accelXeno_B, 20);
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){

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

