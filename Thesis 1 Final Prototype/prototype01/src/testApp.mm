#include "testApp.h"
static int pts1[] = {0,1024-150,768/2,1024-150,768,1024-150};
static int nPts1  = 3*2;
static int pts2[] = {0,150,768/2,150,768,150};
static int nPts2  = 3*2;
//--------------------------------------------------------------
void testApp::setup(){	
	
	ofxAccelerometer.setup();
	ofEnableAlphaBlending();
	ofBackground(30,30,30);
    
    //***********box2d P1****************
    worldP1.init();
    worldP1.setGravity(0, 100);
    worldP1.createBounds();
    worldP1.setIterations(1, 1);
    worldP1.setFPS(60);
    for (int i=0; i<nPts1; i+=2) {
		float x = pts1[i];
		float y = pts1[i+1];
		polyLine1.addVertex(x, y);
	}
    polyLine1.setPhysics(0, 0, 0.2);
    polyLine1.create(worldP1.getWorld());
    
    //***********box2d P2****************
    worldP2.init();
    worldP2.setGravity(0, -100);
    worldP2.createBounds();
    worldP2.setIterations(1, 1);
    worldP2.setFPS(60);
    
    for (int i=0; i<nPts2; i+=2) {
		float x = pts2[i];
		float y = pts2[i+1];
		polyLine2.addVertex(x, y);
	}
    polyLine2.setPhysics(0, 0, 0.2);
    polyLine2.create(worldP2.getWorld());
    
    //**********buttons****************
    P1L.setup(10, ofGetHeight()-120, 0, 0, 0);
    P1R.setup(20+115, ofGetHeight()-120, 1, 0, 0);
    P1J.setup(ofGetWidth()-190, ofGetHeight()-115, 0, 0, 0);
    P1F.setup(ofGetWidth()-105, ofGetHeight()-155, 1, 0, 0);
    P2L.setup(ofGetWidth()-10-101, 120-95, 0, 180, 1);
    P2R.setup(ofGetWidth()-20-101-115, 120-95, 1, 180, 1);
    P2J.setup(190-96, 115-83, 0, 180, 1);
    P2F.setup(105-77, 155-80,  1, 180, 1);
    bFixedButtonP1 = false;
    bFixedButtonP1 = false;
    //********** Guy ******************
    myGuy.setup(chracater1.getPosition());
    chracater1.setPhysics(3, 0, 0.5);
    chracater1.setup(worldP1.getWorld(), ofGetWidth()/2, ofGetHeight()/2, myGuy.width/2, myGuy.height/2);
    chracater1.body->SetFixedRotation(true);
    //********** Girl *******************
    myGirl.setup(chracater2.getPosition());
    chracater2.setPhysics(3, 0, 0.5);
    chracater2.setup(worldP2.getWorld(), ofGetWidth()/2, ofGetHeight()/2, myGirl.width/2, myGirl.height/2);
    chracater2.body->SetFixedRotation(true);
    //********** keys *******************
    key1.setup(0);
    keysubstitute1.setPhysics(30, 0.1, 0);
    keysubstitute1.setup(worldP1.getWorld(), ofGetWidth()/2+100, ofGetHeight()-155, key1.width/2, key1.height/2);
    keyState1 = 0;
    key1UsedP1 = false;
    key1UsedP2 = false;
    
    key2.setup(1);
    keysubstitute2.setPhysics(30, 0.1, 0);
    keysubstitute2.setup(worldP2.getWorld(), ofGetWidth()/2-100, 155, key2.width/2, key2.height/2);
    keyState2 = 0;
    key2UsedP1 = false;
    key2UsedP2 = false;
    //*********** passing belt *******************
    beltP1.addVertex(myGuy.getCenter);
    beltP1.addVertex(myGuy.getCenter);
    beltP2.addVertex(myGirl.getCenter);
    beltP2.addVertex(myGirl.getCenter);
    
}

//--------------------------------------------------------------
void testApp::update(){
    worldP1.update();
    worldP2.update();
    
    //*********** box2d P1*******************
    ofPoint frc1(0,0);
    ofPoint frc2(0,0);
    if (P1L.bPressed) frc1.x = -100;
    if (P1R.bPressed) frc1.x = 100;
    chracater1.addForce(frc1,10);
    chracater1.setDamping(0.98f);
    
    //*********** box2d P2*******************
    
    if (P2L.bPressed) frc2.x = 100;
    if (P2R.bPressed) frc2.x = -100;
    chracater2.addForce(frc2,10);
    chracater2.setDamping(0.98f);
    
    //*********** diffP1 *******************
    diffP1 = chracater1.getPosition()-lastPosP1;
    lastPosP1 = chracater1.getPosition();
    
    //*********** diffP2 *******************
    diffP2 = chracater2.getPosition()-lastPosP2;
    lastPosP2 = chracater2.getPosition();
    
    //*********** Guy *******************
    myGuy.update(chracater1.getPosition());
    
    //*********** Gril *******************
    myGirl.update(chracater2.getPosition());
    
    //*********** Accelerometer *******************
    ofPoint gravity = ofxAccelerometer.getForce();
    float speedP1, speedP2;
    ofPoint beltPosP1, beltPosP2;
    if (gravity.y>0.3) {
        speedP1 = 0.01f;
        bFixedButtonP1 = true;
    }else{
        speedP1 = -0.01f;
        bFixedButtonP1 = false;
    }
    
    if (gravity.y< -0.3) {
        speedP2 = 0.01f;
        bFixedButtonP2 = true;
    }else{
        speedP2 = -0.01f;
        bFixedButtonP2 = false;
    }
    
  
    
    beltPctP1 += speedP1;
    if (beltPctP1>1) {
        beltPctP1 = 1;
    }else if(beltPctP1<0){
        beltPctP1 =0;
    }
    
    beltPctP2 += speedP2;
    if (beltPctP2>1) {
        beltPctP2 = 1;
    }else if(beltPctP2<0){
        beltPctP2 =0;
    }
    
    beltPosP1.y = (1-beltPctP1)*myGuy.getCenter.y + beltPctP1*myGirl.getCenter.y;
    beltPosP2.y = (1-beltPctP2)*myGirl.getCenter.y + beltPctP2*myGuy.getCenter.y;
    
    //*********** keys *******************
        
    switch (keyState1) {
        case 0:
            key1.update(keysubstitute1.getPosition());
            break;
        case 1:{
            ofPoint temp;
            temp.x = myGuy.getCenter.x + 40;
            temp.y = beltPosP1.y;
            key1.update(temp);
            }break;
        case 2:{
            ofPoint temp;
            temp.x = myGirl.getCenter.x - 40;
            temp.y = beltPosP2.y;
            key1.update(temp);
            }break;
    }
    
    keysubstitute1.setDamping(0.98f);
    
    switch (keyState2) {
        case 0:
            key2.update(keysubstitute2.getPosition());
            break;
        case 1:{
            ofPoint temp;
            temp.x = myGuy.getCenter.x + 40;
            temp.y = beltPosP1.y;
            key2.update(temp);
        }break;
        case 2:{
            ofPoint temp;
            temp.x = myGirl.getCenter.x - 40;
            temp.y = beltPosP2.y;
            key2.update(temp);
        }break;
    }
    
    keysubstitute2.setDamping(0.98f);
    
    
    //*********** passing belt *******************
    beltP1[0].set(myGuy.getCenter.x, myGuy.getCenter.y);
    beltP1[1].set(myGuy.getCenter.x, beltPosP1.y);
    
    beltP2[0].set(myGirl.getCenter.x, myGirl.getCenter.y);
    beltP2[1].set(myGirl.getCenter.x, beltPosP2.y);
}

//--------------------------------------------------------------
void testApp::draw(){
  
    myGuy.draw();
    myGirl.draw();
    
    ofNoFill();
    ofSetColor(255, 255, 255);
    polyLine1.draw();
    polyLine2.draw();
    
    ofFill();
    ofSetColor(255, 255, 255,30);
//    chracater1.draw();
//    chracater2.draw();
    //**********key 1**************
    key1.draw();
//    keysubstitute1.draw();
    
    key2.draw();
//    keysubstitute2.draw();
    //*********buttons***********
    P1L.draw();
    P1R.draw();
    P1J.draw();
    P1F.draw();
    P2L.draw();
    P2R.draw();
    P2J.draw();
    P2F.draw();
    //*********** passing belt *******************
//    beltP1.draw();
//    beltP2.draw();
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
    
    if (bFixedButtonP1 == false) {
        P1L.touchDown(touch.x, touch.y, touch.id);
        P1R.touchDown(touch.x, touch.y, touch.id);
        P1J.touchDown(touch.x, touch.y, touch.id);
        P1F.touchDown(touch.x, touch.y, touch.id);
    }
    
    if (bFixedButtonP2 == false) {
        P2L.touchDown(touch.x, touch.y, touch.id);
        P2R.touchDown(touch.x, touch.y, touch.id);
        P2J.touchDown(touch.x, touch.y, touch.id);
        P2F.touchDown(touch.x, touch.y, touch.id);
    }
    
    
    if (P1J.bPressed && fabs(diffP1.y)< 1) chracater1.setVelocity(0, -50);
    if (P2J.bPressed && fabs(diffP2.y)< 1) chracater2.setVelocity(0, 50);
    
    //**********pick up & drop down ************************
    
    //********** key 1 ************************
    
    ofPoint length1;
    ofPoint length2;
    ofPoint length3;
    ofPoint length4;
    length1 = myGuy.getCenter - key1.getCenter;
    length2 = myGuy.getCenter - key2.getCenter;
    length3 = myGirl.getCenter - key1.getCenter;
    length4 = myGirl.getCenter - key2.getCenter;

    if (P1F.bPressed && length1.length()<100 && length2.length()<100 ) {
        
        if (keyState1 != 1 && keyState2 != 1) {
            
            if (length1.length() < length2.length()) {
                keyState1 = 1;
                keysubstitute1.destroy();
                keysubstitute1.setPhysics(30, 0.1, 0);
                keysubstitute1.setup(worldP1.getWorld(), myGuy.getCenter.x, myGuy.getCenter.y, key1.width/2, key1.height/2);
                keysubstitute1.body->SetActive(false);
                key1.angle = 0;
            }else{
                keyState2 = 1;
                keysubstitute2.destroy();
                keysubstitute2.setPhysics(30, 0.1, 0);
                keysubstitute2.setup(worldP1.getWorld(), myGuy.getCenter.x, myGuy.getCenter.y, key2.width/2, key2.height/2);
                keysubstitute2.body->SetActive(false);
                key2.angle = 180;
            }
            

        }else if(keyState1 != 1 && keyState2 == 1){
            keyState1 = 1;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP1.getWorld(), myGuy.getCenter.x, myGuy.getCenter.y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(false);
            key1.angle = 0;
            
            keyState2 = 0;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP1.getWorld(), myGuy.getCenter.x, myGuy.getCenter.y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(true);
            key2.angle = 180;
            
            

        }else if(keyState1 == 1 && keyState2 != 1){
            keyState2 = 1;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP1.getWorld(), myGuy.getCenter.x, myGuy.getCenter.y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(false);
            key1.angle = 0;
            
            keyState1 = 0;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP1.getWorld(), myGuy.getCenter.x, myGuy.getCenter.y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(true);
            key2.angle = 180;
            
            
        }
        
        beltPctP1 = 0;
    }else if(P1F.bPressed && length1.length()<100 && length2.length()>100 ){
        
        if (keyState1 != 1) {
            
            
            keyState1 = 1;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP1.getWorld(), myGuy.getCenter.x, myGuy.getCenter.y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(false);
            key1.angle = 0;
            
        }else if(keyState1 == 1){
                        
            keyState1 = 0;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP1.getWorld(), myGuy.getCenter.x, myGuy.getCenter.y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(true);
            key1.angle = 0;
        }
        beltPctP1 = 0;

    }else if(P1F.bPressed && length1.length()>100 && length2.length()<100 ){
        
        if (keyState2 != 1) {
            
            
            keyState2 = 1;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP1.getWorld(), myGuy.getCenter.x, myGuy.getCenter.y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(false);
            key2.angle = 180;
            
        }else if(keyState2 == 1){
            
            keyState2 = 0;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP1.getWorld(), myGuy.getCenter.x, myGuy.getCenter.y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(true);
            key2.angle = 180;
        }
        beltPctP1 = 0;
        
    }
    
    
    
    //--------------- key 2 --------------
    if (P2F.bPressed && length3.length()<100 && length4.length()<100 ) {
        
        if (keyState1 != 2 && keyState2 != 2) {
            
            if (length3.length() < length4.length()) {
                keyState1 = 2;
                keysubstitute1.destroy();
                keysubstitute1.setPhysics(30, 0.1, 0);
                keysubstitute1.setup(worldP2.getWorld(), myGirl.getCenter.x, myGirl.getCenter.y, key1.width/2, key1.height/2);
                keysubstitute1.body->SetActive(false);
                key1.angle = 180;
            }else{
                keyState2 = 2;
                keysubstitute2.destroy();
                keysubstitute2.setPhysics(30, 0.1, 0);
                keysubstitute2.setup(worldP2.getWorld(), myGirl.getCenter.x, myGirl.getCenter.y, key2.width/2, key2.height/2);
                keysubstitute2.body->SetActive(false);
                key2.angle = 0;
            }
            
        }else if(keyState1 != 2 && keyState2 == 2){
            keyState1 = 2;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP2.getWorld(), myGirl.getCenter.x, myGirl.getCenter.y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(false);
            key1.angle = 180;
            
            keyState2 = 0;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP2.getWorld(), myGirl.getCenter.x, myGirl.getCenter.y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(true);
            key2.angle = 180;
            
        }else if(keyState1 == 2 && keyState2 != 2){
            keyState2 = 2;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP2.getWorld(), myGirl.getCenter.x, myGirl.getCenter.y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(false);
            key2.angle = 0;
            
            keyState1 = 0;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP2.getWorld(), myGirl.getCenter.x, myGirl.getCenter.y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(true);
            key1.angle = 180;
            
        }
        
        beltPctP2 = 0;
        
    }else if(P2F.bPressed && length3.length()<100 && length4.length()>100 ){
        
        if (keyState1 != 2) {
            
            
            keyState1 = 2;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP2.getWorld(), myGirl.getCenter.x, myGirl.getCenter.y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(false);
            key1.angle = 180;
            
        }else if(keyState1 == 2){
            
            keyState1 = 0;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP2.getWorld(), myGirl.getCenter.x, myGirl.getCenter.y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(true);
            key1.angle = 180;
        }
        beltPctP2 = 0;
        
    }else if(P2F.bPressed && length3.length()>100 && length4.length()<100 ){
        
        if (keyState2 != 2) {
            
            
            keyState2 = 2;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP2.getWorld(), myGirl.getCenter.x, myGirl.getCenter.y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(false);
            key2.angle = 0;
            
            
        }else if(keyState2 == 2){
            
            keyState2 = 0;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP2.getWorld(), myGirl.getCenter.x, myGirl.getCenter.y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(true);
            key2.angle = 0;
        }
        beltPctP2 = 0;
        
    }
    
    
    
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
    
    if (bFixedButtonP1 == false) {
        P1L.touchMoved(touch.x, touch.y, touch.id);
        P1R.touchMoved(touch.x, touch.y, touch.id);
        P1J.touchMoved(touch.x, touch.y, touch.id);
        P1F.touchMoved(touch.x, touch.y, touch.id);
    }
    if (bFixedButtonP2 == false) {
        P2L.touchMoved(touch.x, touch.y, touch.id);
        P2R.touchMoved(touch.x, touch.y, touch.id);
        P2J.touchMoved(touch.x, touch.y, touch.id);
        P2F.touchMoved(touch.x, touch.y, touch.id);
    }

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
    
    if (bFixedButtonP1 == false) {
        P1L.touchUp(touch.x, touch.y, touch.id);
        P1R.touchUp(touch.x, touch.y, touch.id);
        P1J.touchUp(touch.x, touch.y, touch.id);
        P1F.touchUp(touch.x, touch.y, touch.id);
    }
    
    if (bFixedButtonP2 == false) {
        P2L.touchUp(touch.x, touch.y, touch.id);
        P2R.touchUp(touch.x, touch.y, touch.id);
        P2J.touchUp(touch.x, touch.y, touch.id);
        P2F.touchUp(touch.x, touch.y, touch.id);
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

