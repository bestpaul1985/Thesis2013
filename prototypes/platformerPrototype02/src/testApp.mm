#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	ofBackground(30,30,30);
    
    bound1.set(0, 0, ofGetWidth(), ofGetHeight());
    p1L.set(0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight());
    p1R.set(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(), ofGetHeight());
    
    world1.init();
    world1.setFPS(60);
    world1.setGravity(0, 10);
    world1.registerGrabbing();
    world1.createBounds(bound1);
    world1.setIterations(1, 1); 
    
    player1.setPhysics(0.4, 0, 0);
    player1.setup(world1.getWorld(), ofGetWidth()/2-10, ofGetHeight()-20, 20,40);
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    world1.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    
        
        ofSetColor(255, 0, 220);
        player1.draw();
	
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    if (p1L.inside(touch.x, touch.y)) {
        touch.id = 0;
        ofPoint p;
        p.set(1, 0,ofGetElapsedTimef());
        myTouch.push_back(p);
    }else if(p1L.inside(touch.x, touch.y)){
        touch.id = 1;
        ofPoint p;
        p.set(0, 1,ofGetElapsedTimef());
        myTouch.push_back(p);
    }
    
    
    if (myTouch.size()==2) {
        ofPoint vel;
        vel = myTouch[0]-myTouch[1];
        
        if (fabs(vel.y)>0.5) {
            if (myTouch[0].y>myTouch[1].y) {
                cout<<"left 2"<<endl;
            }else{
                cout<<"right 2"<<endl;
            }
        }
        
    }else if(myTouch.size()==1){
    
        ofPoint vel;
        vel = myTouch[0]+myTouch[1];
        if (vel.x == 1) {
            cout<<"left 1"<<endl;
        }else{
        
            cout<<"right 1"<<endl;
        }
    }
    
    
    

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

