#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.55f);
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    ofEnableAlphaBlending();
    
    // setup world A
    world_A.init();
    world_A.setFPS(60);
    world_A.setGravity(0,-10);
    // setup world B
    world_B.init();
    world_B.setFPS(60);
    world_B.setGravity(0, 10);
    //Map
    ground_A.setup(1, 0, world_A);
    ground_B.setup(1, 1, world_B);
    
    
	ofAddListener(world_A.contactStartEvents, this, &testApp::contactStart_worldA);
	ofAddListener(world_A.contactEndEvents, this, &testApp::contactEnd_worldA);
    ofAddListener(world_B.contactStartEvents,this, &testApp::contactStart_worldB);
    ofAddListener(world_B.contactEndEvents,this, &testApp::contactEnd_worldB);
    numFootContacts_A = 0;
    numFootContacts_B = 0;
    
    //contorl
    control.setup();
    
    //char
    char_A.setup(world_A,control,ofPoint(50,0),ofxAccelerometer.getForce(),0);
    char_B.setup(world_B,control,ofPoint(50,0),ofxAccelerometer.getForce(),1);
    
    //translate
    translate_A.set(384,250);
    translate_B.set(384,768-250);
    camera_A = char_A.getPos;
    camera_B = char_B.getPos;
    screen();
    //thorn
    thorns_A.setup(world_A, 0);
    thorns_B.setup(world_B, 1);
    
    //sky
    sky.setup();
    
    //indictor
    accIndictor.setup(ofxAccelerometer.getForce());
    
    //rope
    rope_A.setup(ofxAccelerometer.getForce(),screen_A,screen_B,char_A.getPos,char_B.getPos,control,0);
    rope_B.setup(ofxAccelerometer.getForce(),screen_A,screen_B,char_A.getPos,char_B.getPos,control,1);
}
//--------------------------------------------------------------
void testApp::contactStart_worldA(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        //a == polygone, b == circle
        ttSetData * aData = (ttSetData*)e.a->GetUserData();
        ttSetData * bData = (ttSetData*)e.b->GetUserData();
        
        if (aData && aData->name == "footSenser"){
            numFootContacts_A++;
            if (bData&&bData->name == "thorn") {
                char_A.bDead = true;
            }
        }
        else if (bData && bData->name == "footSenser"){
            numFootContacts_A++;
            if (aData&&aData->name == "thorn") {
                char_A.bDead = true;
            }
        }
        
    }

}
//--------------------------------------------------------------
void testApp::contactEnd_worldA(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
            
        ttSetData * aData = (ttSetData*)e.a->GetUserData();
        ttSetData * bData = (ttSetData*)e.b->GetUserData();
        
        if (aData && aData->name == "footSenser"){
            numFootContacts_A--;
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_A--;
        }
    }
}
//--------------------------------------------------------------
void testApp::contactStart_worldB(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        //a == polygone, b == circle
        ttSetData * aData = (ttSetData*)e.a->GetUserData();
        ttSetData * bData = (ttSetData*)e.b->GetUserData();
        
        if (aData && aData->name == "footSenser"){
            numFootContacts_B++;
            if (bData&&bData->name == "thorn") {
                char_B.bDead = true;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B++;
            if (aData&&aData->name == "thorn") {
                char_B.bDead = true;
            }
        }
    }

}
//--------------------------------------------------------------
void testApp::contactEnd_worldB(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        //a == polygone, b == circle
        ttSetData * aData = (ttSetData*)e.a->GetUserData();
        ttSetData * bData = (ttSetData*)e.b->GetUserData();
        if (aData && aData->name == "footSenser"){
            numFootContacts_B--;
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B--;
        } 
    }
}
//--------------------------------------------------------------
void testApp::update(){
    
    world_A.update();
    world_B.update();
    
    //no jump in sky
    if (numFootContacts_A<=0) {
        char_A.bInSky = true;
        rope_A.bInSky = true;
    }else{
        char_A.bInSky = false;
        rope_A.bInSky = false;
    }
    
    if (numFootContacts_B<=0) {
        char_B.bInSky = true;
        rope_B.bInSky = true;
    }else{
        char_B.bInSky = false;
        rope_B.bInSky = false;
    }

    //Character
    char_A.update();
    char_B.update();
    //screen
    screen();
   
    //control
   
    if (control.bTouch[0]&&!control.bTouch[1]&&!rope_A.bRopeInUse) {
        char_A.moveLeft();
    }else if(control.bTouch[1]&&!control.bTouch[0]&&!rope_A.bRopeInUse){
        char_A.moveRight();
    }else if(control.bTouch[0]&&control.bTouch[1]&&!rope_A.bRopeInUse && rope_B.bRopeInUse){
        if (rope_B.bReady) {
            char_A.copyRope(rope_B.rects, rope_B.joints, screen_A);
            rope_B.bReady = false;
            rope_B.destroy();
            
        }
        char_A.controlRope();
        char_A.swing();
        rope_A.bSwing = true;
        rope_B.bSwing = true;
    }else if(!control.bTouch[0]&&!control.bTouch[1]){
        if (!char_A.joints.empty()) {
            char_A.character.setVelocity(char_A.rects.back().getVelocity().x * 1.5, char_A.character.getVelocity().y * 1.5 +5);
            char_A.destroyRope();
            rope_B.bSwing = false;
            char_A.bSwing = false;
            rope_A.bSwing = false;
        }
    }
    
  
    if (control.bTouch[2]&&!control.bTouch[3]&&!rope_B.bRopeInUse) {
        char_B.moveLeft();
    }else if(control.bTouch[3]&&!control.bTouch[2]&&!rope_B.bRopeInUse){
        char_B.moveRight();
    }else if(control.bTouch[2]&&control.bTouch[3]&&!rope_B.bRopeInUse && rope_A.bRopeInUse){
        if (rope_A.bReady) {
            char_B.copyRope(rope_A.rects, rope_A.joints, screen_B);
            rope_A.bReady = false;
            rope_A.destroy();
            
        }
        char_B.controlRope();
        char_B.swing();
        rope_B.bSwing = true;
        rope_A.bSwing = true;
    }else if(!control.bTouch[2]&&!control.bTouch[3]){
        if (!char_B.joints.empty()) {
            char_B.character.setVelocity(char_B.rects.back().getVelocity().x * 1.5, char_B.character.getVelocity().y * 1.5 -5);
            char_B.destroyRope();
            rope_A.bSwing = false;
            char_B.bSwing = false;
            rope_B.bSwing = false;
        }
       
    }
    
    
//    cout<< char_B.bSwing <<
//    rope_B.bSwing <<
//    rope_A.bSwing << endl;
    //rope update
  
    rope_A.update();
    rope_B.update();
    
    if (rope_A.bRopeInUse && !char_A.bInSky) {
        char_A.character.setVelocity(0, 0);
    }
    if (rope_B.bRopeInUse && !char_B.bInSky) {
        char_B.character.setVelocity(0, 0);
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofColor dark(80);
    ofBackgroundGradient(dark, ofColor::black);
   
    drawScene(0);
    accIndictor.draw();
    control.draw();
    
    ofDrawBitmapStringHighlight("world: " + ofToString(char_A.getPos,2)+"\nScreen: "+ofToString(camera_A,2), 50,50);
    ofDrawBitmapStringHighlight("world: " + ofToString(char_B.getPos,2)+"\nScreen: "+ofToString(camera_B,2), 750,700);
}
//-------------------------------------------------------------
void testApp::drawScene(int iDraw){

    if (iDraw == 0) {
        sky.drawBg();
        
        ofPushMatrix();
        ofTranslate(screen_A);
        ground_A.draw();
//        ground_A.drawPolyLine();
//        char_A.drawBox2dObject();
//        thorns_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        ground_B.draw();
//        ground_B.drawPolyLine();
//        char_B.drawBox2dObject();
//        thorns_B.draw();
        ofPopMatrix();
        
        sky.drawCloud();
        
        ofPushMatrix();
        ofTranslate(screen_A);
        char_A.draw();
        char_A.drawRope();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        char_B.draw();
        char_B.drawRope();
        ofPopMatrix();
        
        
        ofPushMatrix();
        ofTranslate(screen_A);
        char_A.drawRope();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        char_B.drawRope();
        ofPopMatrix();
        
        rope_A.draw();
        rope_B.draw();
    }
}
//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    control.touchDown(touch.x, touch.y,touch.id);
    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    control.touchMove(touch.x, touch.y,touch.id);
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    control.touchUp(touch.x, touch.y,touch.id);
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
//--------------------------------------------------------------
void testApp::screen(){

    float catchUpSpeed = 0.03f;
    if (!rope_A.bRopeInUse && !char_B.bSwing) {
        camera_A.x = catchUpSpeed * char_A.getPos.x + (1-catchUpSpeed) * camera_A.x;
        camera_A.y = catchUpSpeed * char_A.getPos.y + (1-catchUpSpeed) * camera_A.y;
    }
   
    if (!rope_B.bRopeInUse && !char_A.bSwing) {
        camera_B.x = catchUpSpeed * char_B.getPos.x + (1-catchUpSpeed) * camera_B.x;
        camera_B.y = catchUpSpeed * char_B.getPos.y + (1-catchUpSpeed) * camera_B.y;
    }
  
    screen_A.x = translate_A.x - camera_A.x,
    screen_A.y = translate_A.y;
    
    screen_B.x = translate_B.x - camera_B.x,
    screen_B.y = translate_B.y;

}
