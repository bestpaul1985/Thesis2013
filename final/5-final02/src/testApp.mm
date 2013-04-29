#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.55f);
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    ofEnableAlphaBlending();
    ofSetCircleResolution(8);
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
    
    //Listener
	ofAddListener(world_A.contactStartEvents, this, &testApp::contactStart_worldA);
	ofAddListener(world_A.contactEndEvents, this, &testApp::contactEnd_worldA);
    ofAddListener(world_B.contactStartEvents,this, &testApp::contactStart_worldB);
    ofAddListener(world_B.contactEndEvents,this, &testApp::contactEnd_worldB);
    numFootContacts_A = 0;
    numFootContacts_B = 0;
    
    //contorl
    control.setup();
    
    //char
    char_B.setup(world_B, ofPoint(0,0), 1);
    //translate
    translate_A.set(384,250);
    translate_B.set(384,768-250);
//    camera_A = char_A.getPos;
//    camera_B = char_B.getPos;
    screen();
    //thorn
    thorns_A.setup(world_A, 0);
    thorns_B.setup(world_B, 1);
    
    //sky
    sky.setup();
    
    //indictor
    accIndictor.setup(ofxAccelerometer.getForce());
    

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
//                char_A.bDead = true;
            }
        }
        else if (bData && bData->name == "footSenser"){
            numFootContacts_A++;
            if (aData&&aData->name == "thorn") {
//                char_A.bDead = true;
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
//                char_B.bDead = true;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B++;
            if (aData&&aData->name == "thorn") {
//                char_B.bDead = true;
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
//        char_A.bInSky = true;
//        rope_A.bInSky = true;
    }else{
//        char_A.bInSky = false;
//        rope_A.bInSky = false;
    }
    
    if (numFootContacts_B<=0) {
//        char_B.bInSky = true;
//        rope_B.bInSky = true;
    }else{
//        char_B.bInSky = false;
//        rope_B.bInSky = false;
    }

    //Character
    char_B.update();
    //screen
    screen();
    //control
    
    if (ofxAccelerometer.getForce().x>0.1) {
         char_B.condition = C_PUSH_ROPE;
    }
    
    else if (!control.bTouch[2]&&!control.bTouch[3]) {
        char_B.condition = C_STOP;
    }
    
    else if (control.bTouch[2]&&!control.bTouch[3]) {
        char_B.condition = C_LEFT;
    }
    
    else if(control.bTouch[3]&&!control.bTouch[2]){
        char_B.condition = C_RIGHT;
    }
    
    else if(control.bTouch[2]&&control.bTouch[3]){
        char_B.condition = C_HOOK_ROPE;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofColor dark(80);
    ofBackgroundGradient(dark, ofColor::black);
   
    drawScene(0);
    accIndictor.draw();
    control.draw();
}
//-------------------------------------------------------------
void testApp::drawScene(int iDraw){

    if (iDraw == 0) {
        sky.drawBg();
        
        ofPushMatrix();
        ofTranslate(screen_A);
        ground_A.draw();
        ground_A.drawPolyLine();
        thorns_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        ground_B.draw();
        ground_B.drawPolyLine();
        thorns_B.draw();
        char_B.draw();
        ofPopMatrix();
        
        sky.drawCloud();
    

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
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
void testApp::touchCancelled(ofTouchEventArgs & touch){}
void testApp::lostFocus(){}
void testApp::gotFocus(){}
void testApp::gotMemoryWarning(){}
void testApp::deviceOrientationChanged(int newOrientation){}
//--------------------------------------------------------------
void testApp::screen(){

    bool A[10],B[10];
    float catchUpSpeed = 0.03f;
    ofPoint catch_A, catch_B;
    
//    char_A.getPos.x<0? A[0] = true: A[0] =false;
//    char_B.getPos.x<0? B[0] = true: B[0] =false;
    //camera setup
    if (A[0]) {
        catch_A.x = 0;
//        catch_A.y = char_A.getPos.y;
    }else{
//        catch_A.x = char_A.getPos.x;
//        catch_A.y = char_A.getPos.y;
    }
   
    if (B[0]) {
        catch_B.x = 0;
//        catch_B.y = char_B.getPos.y;
    }else{
//        catch_B.x = char_B.getPos.x;
//        catch_B.y = char_B.getPos.y;
    }
    
    //calculate
//    if (!rope_A.bRopeInUse && !char_A.bSwing && !char_B.bSwing) {
//        camera_A.x = catchUpSpeed * catch_A.x + (1-catchUpSpeed) * camera_A.x;
//        camera_A.y = catchUpSpeed * catch_A.y + (1-catchUpSpeed) * camera_A.y;
//    }
//   
//    if (!rope_B.bRopeInUse && !char_A.bSwing && !char_B.bSwing) {
//        camera_B.x = catchUpSpeed * catch_B.x + (1-catchUpSpeed) * camera_B.x;
//        camera_B.y = catchUpSpeed * catch_B.y + (1-catchUpSpeed) * camera_B.y;
//    }
  
    screen_A.x = translate_A.x - camera_A.x,
    screen_A.y = translate_A.y;
    
    screen_B.x = translate_B.x - camera_B.x,
    screen_B.y = translate_B.y;

    
}
