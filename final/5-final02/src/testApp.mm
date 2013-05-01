#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){
    
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.55f);
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    ofEnableAlphaBlending();
    ofSetCircleResolution(8);
    ofSetLineWidth(2.5);
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
    char_A.setup(world_A, ofPoint(0,0), 0);
    char_B.setup(world_B, ofPoint(0,0), 1);
    //camera
    translate_A.set(384,250);
    translate_B.set(384,768-250);
    camera_A = char_A.getPos;
    camera_B = char_B.getPos;
    //thorn
    thorns_A.setup(world_A, 0);
    thorns_B.setup(world_B, 1);
    
    //sky
    sky.setup();
    
    //indictor
    accIndictor.setup(ofxAccelerometer.getForce());
    
    //rope
    hook_pct_A = 0;
    hook_pct_B = 0;

    rope_condition_A = R_NO_USE;
    rope_condition_B = R_NO_USE;
    //booleans
    bSwing_left = false;
    bSwing_right = false;
    bDead_A = false;
    bDead_B = false;
    bInSky_A = false;
    bInSky_B = false;
    //dog
    dog.setup(world_B, 100,-100);
   
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
                bDead_A = true;
            }
        }
        else if (bData && bData->name == "footSenser"){
            numFootContacts_A++;
            if (aData&&aData->name == "thorn") {
                 bDead_A = true;
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
            if (bData&&bData->name == "thorn") {
                bDead_A = false;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_A--;
            if (bData&&bData->name == "thorn") {
                bDead_A = false;
            }
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
                bDead_B = true;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B++;
            if (aData&&aData->name == "thorn") {
                bDead_B = true;
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
            if (bData&&bData->name == "thorn") {
                bDead_B = false;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B--;
            if (bData&&bData->name == "thorn") {
                bDead_B = false;
            }
        } 
    }
}
//--------------------------------------------------------------
void testApp::update(){
    
    world_A.update();
    world_B.update();
    
    //no jump in sky
    if (numFootContacts_A<=0) {
        bInSky_A = true;
    }else{
        bInSky_A = false;
    }
    
    if (numFootContacts_B<=0) {
        bInSky_B = true;
    }else{
        bInSky_B = false;
    }

    
    //screen update
    position();
    //control char_A
    if (ofxAccelerometer.getForce().x<-0.3 && rope_condition_A == R_NO_USE) {
        char_A.condition = C_PUSH_ROPE;
        hook_pct_A = 0;
        rope_condition_A = R_PUSH;
    }
    
    if (bDead_A) {
        char_A.condition = C_DEAD;
    }else{
        if (!control.bTouch[0]&&!control.bTouch[1]) {
            
            if (rope_condition_A==R_NO_USE&& !bInSky_A) {
                char_A.condition = C_STOP;
            }
            
            if (rope_condition_B == R_SWING) {
                rope_condition_B = R_DESTROY;
            }
            
            if (rope_condition_B == R_DESTROY) {
                char_B.condition = C_STOP;
            }
        }
        
        
        if (control.bTouch[0]&&!control.bTouch[1]) {
            if (rope_condition_A == R_NO_USE) {
                char_A.condition = C_LEFT;
            }
        }
        
        if(control.bTouch[1]&&!control.bTouch[0]){
            if (rope_condition_A == R_NO_USE) {
                char_A.condition = C_RIGHT;
            }
        }
        
        if(control.bTouch[0]&&control.bTouch[1]){
            if (rope_condition_B == R_PUSH) {
                ofPoint dis =  hook_end_B - char_pos_A;
                if ( fabs(dis.x)< 50 && dis.y<=60) {
                    char_A.condition = C_HOOK_ROPE;
                    rope_condition_B = R_SWING;
                }
            }
        }
    }
    
    //control char_B
    if (ofxAccelerometer.getForce().x>0.3 && rope_condition_B == R_NO_USE) {
        char_B.condition = C_PUSH_ROPE;
        hook_pct_B = 0;
        rope_condition_B = R_PUSH;
    }
    
    if (bDead_B) {
        char_B.condition = C_DEAD;
    }else{
        
         if (!control.bTouch[2]&&!control.bTouch[3]) {
            if (rope_condition_B==R_NO_USE && !bInSky_B) {
                char_B.condition = C_STOP;
            }
                
            
            if (rope_condition_A == R_SWING) {
                rope_condition_A = R_DESTROY;
            }
            
            if (rope_condition_A == R_DESTROY) {
                char_A.condition = C_STOP;
            }
        }
        
        else if (control.bTouch[2]&&!control.bTouch[3]) {
            if (rope_condition_B == R_NO_USE) {
                char_B.condition = C_LEFT;
            }
            if (rope_condition_A == R_SWING) {
                rope_condition_A = R_DESTROY;
            }
        }
        
        else if(control.bTouch[3]&&!control.bTouch[2]){
            if (rope_condition_B == R_NO_USE) {
                char_B.condition = C_RIGHT;
            }
            
            if (rope_condition_A == R_SWING) {
                rope_condition_A = R_DESTROY;
            }
        }
        
        else if(control.bTouch[2]&&control.bTouch[3]){
            if (rope_condition_A == R_PUSH) {
                ofPoint dis =  hook_end_A - char_pos_B;
                if ( fabs(dis.x)< 50 && dis.y>=-60) {
                    char_B.condition = C_HOOK_ROPE;
                    rope_condition_A = R_SWING;
                }
            }
        }
    }
    
    //swing A
    
    if (rope_condition_A == R_SWING) {
        
        if (!rope_joint.isSetup()) {
            rope_anchor.setup(world_B.getWorld(), rope_start_B.x, rope_start_B.y, 10);
            rope_joint.setup(world_B.getWorld(), rope_anchor.body, char_B.character.body);
            float length = fabs(rope_start_B.y - char_B.getPos.y) - 100;
            rope_joint.setLength(length);
        }
        
    }
    
    if (rope_condition_A == R_DESTROY) {
        if (rope_joint.isSetup()) {
            rope_joint.destroy();
            world_B.getWorld()->DestroyBody(rope_anchor.body);
        }
    }
     //swing B
    
    if (rope_condition_B == R_SWING) {
        
        if (!rope_joint.isSetup()) {
            rope_anchor.setup(world_A.getWorld(), rope_start_A.x, rope_start_A.y, 10);
            rope_joint.setup(world_A.getWorld(), rope_anchor.body, char_A.character.body);
            float length = fabs(rope_start_A.y - char_A.getPos.y) - 100;
            rope_joint.setLength(length);
        }
        
    }
    
    if (rope_condition_B == R_DESTROY) {
        if (rope_joint.isSetup()) {
            rope_joint.destroy();
            world_A.getWorld()->DestroyBody(rope_anchor.body);
        }
    }
    
    //swing acclerometer
    if (ofxAccelerometer.getForce().y > 0.4 && !bSwing_left) {
        if (rope_condition_A == R_SWING) {
            char_B.character.addForce(ofPoint(-30,0), 100);
        }
        
        if (rope_condition_B == R_SWING) {
            char_A.character.addForce(ofPoint(-30,0), 100);
        }
        bSwing_left = true;
    }
    
    if (ofxAccelerometer.getForce().y < -0.4 && !bSwing_right) {
        if (rope_condition_A == R_SWING) {
            char_B.character.addForce(ofPoint(30,0), 100);
        }
        if (rope_condition_B == R_SWING) {
            char_A.character.addForce(ofPoint(30,0), 100);
        }
        bSwing_right = true;
    }
    
    //reset
    if (ofxAccelerometer.getForce().x<0.3 && ofxAccelerometer.getForce().x>-0.3) {
        if (rope_condition_A !=R_SWING) {
            rope_condition_A = R_NO_USE;
        }
        if (rope_condition_B !=R_SWING) {
            rope_condition_B = R_NO_USE;
        }
    }
    
    if (ofxAccelerometer.getForce().y<0.4 && ofxAccelerometer.getForce().y>-0.4) {
        bSwing_left = false;
        bSwing_right = false;
    }
    
    cout<<rope_condition_A<<"  "<<rope_condition_B<<endl;
    
    //Character
    char_A.update();
    char_B.update();
    
    //dog
    dog.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofColor dark(80);
    ofBackgroundGradient(dark, ofColor::black);
   
    drawScene(0);
    accIndictor.draw();
    control.draw();
    
    
//    ofDrawBitmapStringHighlight("world: " + ofToString(char_A.getPos,2)+"\nScreen: "+ofToString(char_A.getPos+screen_A,2), 50,50);
//    ofDrawBitmapStringHighlight("world: " + ofToString(char_B.getPos,2)+"\nScreen: "+ofToString(char_B.getPos+screen_B,2), 750,700);

}
//-------------------------------------------------------------
void testApp::drawScene(int iDraw){

    if (iDraw == 0) {
        sky.drawBg();
        
        ofPushMatrix();
        ofTranslate(screen_A);
        ground_A.draw();
//        ground_A.drawPolyLine();
//        thorns_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        ground_B.draw();
//        ground_B.drawPolyLine();
//        thorns_B.draw();
        ofPopMatrix();
        
        sky.drawCloud();
        
        ofPushMatrix();
        ofTranslate(screen_A);
        char_A.draw();
        
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        dog.draw();
        char_B.draw();
        

        ofPopMatrix();
        
        
        ofPushMatrix();
        if (rope_condition_A == R_SWING) {
            ofTranslate(screen_B);
        }
        
        if (rope_condition_B == R_SWING) {
            ofTranslate(screen_A);
        }
        
        if (rope_joint.isSetup()) {
            ofSetColor(0,100);
            rope_anchor.draw();
            rope_joint.draw();
        }
        
        if (rope_condition_A == R_SWING) {
           ofCircle(char_B.character.getPosition().x, char_B.character.getPosition().y, 10);
        }
        
        if (rope_condition_B == R_SWING) {
           ofCircle(char_A.character.getPosition().x, char_A.character.getPosition().y, 10);
        }
        
        ofPopMatrix();

    }
    
   
   
    //rope
  
    if (rope_condition_A == R_PUSH) {
        float speed = 0.1f;
        hook_pct_A +=speed;
        if (hook_pct_A > 1) hook_pct_A = 1;
        hook_end_A.x = hook_start_A.x;
        hook_end_A.y = (1-hook_pct_A)*hook_start_A.y + hook_pct_A*(500+hook_start_A.y);
        
        ofSetColor(0,100);
        ofLine(hook_start_A.x,hook_start_A.y,hook_end_A.x, hook_end_A.y);
        ofCircle(hook_end_A.x, hook_end_A.y, 10);
    }
    
    
    
    if (rope_condition_B == R_PUSH) {
        float speed = 0.1f;
        hook_pct_B +=speed;
        if (hook_pct_B > 1) hook_pct_B = 1;
        hook_end_B.x = hook_start_B.x;
        hook_end_B.y = (1-hook_pct_B)*hook_start_B.y + hook_pct_B*(hook_start_B.y-500);
        
        ofSetColor(0,100);
        ofSetLineWidth(2.5);
        ofLine(hook_start_B.x,hook_start_B.y,hook_end_B.x, hook_end_B.y);
        ofCircle(hook_end_B.x, hook_end_B.y, 10);
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
void testApp::position(){

    bool A[10],B[10];
    float catchUpSpeed = 0.05f;
    ofPoint catch_A, catch_B;
    
    char_A.getPos.x<0? A[0] = true: A[0] =false;
    char_B.getPos.x<0? B[0] = true: B[0] =false;
    //camera setup
    if (A[0]) {
        catch_A.x = 0;
        catch_A.y = char_A.getPos.y;
    }else{
        catch_A.x = char_A.getPos.x;
        catch_A.y = char_A.getPos.y;
    }
   
    if (B[0]) {
        catch_B.x = 0;
        catch_B.y = char_B.getPos.y;
    }else{
        catch_B.x = char_B.getPos.x;
        catch_B.y = char_B.getPos.y;
    }
    
    
    if (rope_condition_B != R_SWING) {
        camera_A.x = catchUpSpeed * catch_A.x + (1-catchUpSpeed) * camera_A.x;
        camera_A.y = catchUpSpeed * catch_A.y + (1-catchUpSpeed) * camera_A.y;
    }
       
    if (rope_condition_A != R_SWING) {
        camera_B.x = catchUpSpeed * catch_B.x + (1-catchUpSpeed) * camera_B.x;
        camera_B.y = catchUpSpeed * catch_B.y + (1-catchUpSpeed) * camera_B.y;
    }
  
    screen_A.x = translate_A.x - camera_A.x,
    screen_A.y = translate_A.y;
    
    screen_B.x = translate_B.x - camera_B.x,
    screen_B.y = translate_B.y;
    //char postion
    char_pos_A = char_A.getPos + screen_A;
    char_pos_B = char_B.getPos + screen_B;
    //hook postion
    
    ofPoint offset(15,0);
    if (char_A.moveLeft) hook_start_A.x = char_pos_A.x - offset.x;
    else hook_start_A.x = char_pos_A.x + offset.x;
    hook_start_A.y = char_pos_A.y + offset.y;
    
    if (char_B.moveLeft) hook_start_B.x = char_pos_B.x - offset.x;
    else hook_start_B.x = char_pos_B.x + offset.x;
    hook_start_B.y = char_pos_B.y - offset.y;
    //rope postion
    rope_start_A = hook_start_B - screen_A;
//    rope_end_A = hook_end_B - screen_A;
   
    rope_start_B = hook_start_A - screen_B;
//    rope_end_B = hook_end_A - screen_B;

}
