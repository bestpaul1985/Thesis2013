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
    
    ofPoint p;
    p.set(0, 0,ofGetElapsedTimef());
    myTouch.push_back(p);
    p.set(0, 0,ofGetElapsedTimef());
    myTouch.push_back(p);
    
    bTouchedTwo = false;
    
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
        myTouch[0].set(1, 1,ofGetElapsedTimef());
    }else if(p1R.inside(touch.x, touch.y)){
        touch.id = 1;
        myTouch[1].set(2, 1,ofGetElapsedTimef());
    }
    
    
    ofPoint vel;
    vel = myTouch[0]+myTouch[1];
    float diff;
    diff = fabs(myTouch[0].z-myTouch[1].z);
    
 
    
    
    if (bTouchedTwo == true) {
        
        if (vel.x == 1 && diff>0.5) {
            cout<<vel.x<<"L"<<endl;
        }else if(vel.x == 2 && diff>0.5){
            cout<<vel.x<<"R"<<endl;
        }else if (vel.x == 3&& diff>0.5 && myTouch[0].z<myTouch[1].z) {
            cout<<vel.x<<"L"<<"  "<<"Jump"<<endl;
        }else if (vel.x == 3&& diff>0.5 && myTouch[1].z<myTouch[0].z) {
            cout<<vel.x<<"R"<<"  "<<"Jump"<<endl;
        }else if (vel.x ==3 && diff<0.5){
            cout<<"Jump"<<endl;
        }
        
    }else{
    
        if (vel.x == 1) {
            cout<<vel.x<<"L"<<endl;
        }else if(vel.x == 2){
            cout<<vel.x<<"R"<<endl;
        }else if (vel.x == 3&& diff>0.5 && myTouch[0].z>myTouch[1].z) {
            cout<<vel.x<<"L"<<"  "<<"Jump"<<endl;
        }else if (vel.x == 3&& diff>0.5 && myTouch[1].z>myTouch[0].z) {
            cout<<vel.x<<"R"<<"  "<<"Jump"<<endl;
        }else if (vel.x ==3 && diff<0.5){
            cout<<"Jump"<<endl;
        }
    
    }
        
    

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
    if (p1L.inside(touch.x, touch.y)) {
        touch.id = 0;
        myTouch[0].set(0, 1, ofGetElapsedTimef());
    }else if(p1R.inside(touch.x, touch.y)){
        touch.id = 1;
        myTouch[1].set(0, 1, ofGetElapsedTimef());
    }
    
    ofPoint vel;
    vel = myTouch[0]+myTouch[1];
    
    if(vel.y == 2){
    
        bTouchedTwo = true;
    }

    
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

