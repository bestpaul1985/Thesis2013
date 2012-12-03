#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	
	ofxAccelerometer.setup();
	ofBackground(30,30,30);
    ofSetLogLevel(OF_LOG_NOTICE);
    box2d.init();
    box2d.setGravity(0, 100);
    box2d.createBounds(0,0,ofGetWidth(),ofGetHeight());
	box2d.createGround(0,ofGetHeight()-100,ofGetWidth(),ofGetHeight()-100);
	box2d.setFPS(60);
	box2d.registerGrabbing();
    
    bgRectA.set(0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight());
    bgRectB.set(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(), ofGetHeight());
    rectColorA.set(30, 30, 30);
    rectColorB.set(30, 30, 30);
    
    for (int i = 0; i<10; i++) {
        finger f;
        f.setup(false, i);
        f.moveto(0, 0);
        fingers.push_back(f);
    }
    
    frc1.set(0, 0);
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    player1.setPhysics(10, 0, 0.1);
//  player1.setFixedRotation(true);
    ofRectangle r;
    r.set(ofGetWidth()/2, ofGetHeight()/2, 20,20);
    player1.setup(box2d.getWorld(), r);
    speed.set(0, 0);
    
    for (int i=0; i<2; i++) {
        ofPoint p;
        p.set(0,0,0);
        jump1.push_back(p);
    }
    
    bNoTouch = false;
}

//--------------------------------------------------------------
void testApp::update(){
    
    box2d.update();
    
    if (bNoTouch) {
        
        if (frc1.x == 0)return;
        
        if (frc1.x<0) {
            frc1.x += 1;
        }else{
            frc1.x -= 1;
        }
    }else{
        frc1 += speed;
        if (frc1.x>150) {
            frc1.x = 150;
        }else if(frc1.x < -150){
            frc1.x = -150;
        }
    }
    
    player1.addForce(frc1, 25);
    player1.setDamping(0.3f, 0.7f);
    player1.update();


}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0, 255, 220);
    ofLine(0,ofGetHeight()-100,ofGetWidth(),ofGetHeight()-100);
    ofSetColor(rectColorA);
    ofRect(bgRectA);
    ofSetColor(rectColorB);
    ofRect(bgRectB);
    ofSetColor(255, 0, 220);
    for (int i=0; i<fingers.size(); i++) {
        fingers[i].draw();
    }
    
    
    player1.draw();
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    
    if ( bgRectA.inside(touch.x, touch.y)){
        touch.id = 0;
        jump1[0].set(1,0,0);
        time1 = ofGetElapsedTimef();
        bNoTouch = false;
        fingers[0].moveto(touch.x, touch.y);
        fingers[0].bDraw = true;
        
    }else if(bgRectB.inside(touch.x, touch.y)){
        touch.id = 1;
        jump1[1].set(0,1,0);
        time2 = ofGetElapsedTimef();
        bNoTouch = false;
        fingers[1].moveto(touch.x, touch.y);
        fingers[1].bDraw = true;
    }
    
    

        ofPoint vel;
        vel = jump1[0]+jump1[1];
        
        if (vel.x == 1 && vel.y ==0) {
            cout<<"left"<<endl;
            speed.set(-10,0);
        }else if (vel.x == 0 && vel.y == 1) {
            cout<<"right"<<endl;
            speed.set(10,0);
        }
    
    
    if (vel.x == 1 && vel.y == 1 &&fabs(time1 - time2) < 0.5) {
            cout<<"jump"<<endl;
            player1.setVelocity(0, -50);
            
        }
       
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){


}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
    if ( bgRectA.inside(touch.x, touch.y)){
        touch.id = 0;
        jump1[0].set(0,0,0);
        time1 = ofGetElapsedTimef();
        fingers[0].bDraw = false;
        
    }else if(bgRectB.inside(touch.x, touch.y)){
        touch.id = 1;
        jump1[1].set(0,0,0);
        time2 = ofGetElapsedTimef();
        fingers[1].bDraw = false;
    }
    
    ofPoint vel;
    vel = jump1[0]+jump1[1];
    
    if (vel.x == 1 && vel.y ==0) {
        cout<<"left"<<endl;
        speed.set(-10, 0);
        bNoTouch = false;
        
    }else if (vel.x == 0 && vel.y == 1) {
        cout<<"right"<<endl;
        speed.set(10, 0);
        bNoTouch = false;
       
    }
    
    
    if (vel.x == 0 && vel.y == 0) {
        cout<<"noTouch"<<endl;
        speed.set(0, 0);
        bNoTouch = true;
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

