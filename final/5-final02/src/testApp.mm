#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){
    
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.9f);
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    ofEnableAlphaBlending();
    ofSetCircleResolution(8);
    ofSetLineWidth(2.5);
    ofSetFrameRate(60);
    ofEnableSmoothing();
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
    bInSky_A = false;
    bInSky_B = false;
    //dog
    dog_A.setup(world_A, 200, 100, 0);
    dog_B.setup(world_B, 200, -100, 1);
    //emoji
    emoji_A.setup(char_A.character.getPosition(),0);
    emoji_B.setup(char_B.character.getPosition(),1);
    image[0].loadImage("sprites/emoji_love.png");
    image[1].loadImage("sprites/emoji_laughing.png");
    image[2].loadImage("sprites/emoji_happy.png");
    image[3].loadImage("sprites/emoji_supprise.png");
    image[4].loadImage("sprites/emoji_angry.png");

    emoji_A.image[0] = &image[0];
    emoji_A.image[1] = &image[1];
    emoji_A.image[2] = &image[2];
    emoji_A.image[3] = &image[3];
    emoji_A.image[4] = &image[4];
    
    emoji_B.image[0] = &image[0];
    emoji_B.image[1] = &image[1];
    emoji_B.image[2] = &image[2];
    emoji_B.image[3] = &image[3];
    emoji_B.image[4] = &image[4];
    
    e_startTime_A= ofGetElapsedTimef();
    e_duration_A = 8000;
    happyness_A = 2;
    
    e_startTime_B= ofGetElapsedTimef();
    e_duration_B = 8000;
    happyness_B = 2;
    
    //score
    font.loadFont("font/NewMedia Fett.ttf", 20);
    score_A = 0;
    score_B = 0;
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
                char_A.condition = C_DEAD;
            }
        }
        else if (bData && bData->name == "footSenser"){
            numFootContacts_A++;
            if (bData&&bData->name == "thorn") {
                char_A.condition = C_DEAD;
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
                char_B.condition = C_DEAD;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B++;
            if (bData&&bData->name == "thorn") {
               char_B.condition = C_DEAD;
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
        bInSky_A = true;
    }else{
        bInSky_A = false;
    }
    
    if (numFootContacts_B<=0) {
        bInSky_B = true;
    }else{
        bInSky_B = false;
    }

    
    //screen update-------------------------------
    position();
    //control char_A-------------------------------
    if (ofxAccelerometer.getForce().x<-0.3 && rope_condition_A == R_NO_USE && rope_condition_B != R_SWING&& !bInSky_A) {
        char_A.condition = C_PUSH_ROPE;
        hook_pct_A = 0;
        rope_condition_A = R_PUSH;
    }//charA pushRope
    
    if (char_A.condition != C_DEAD) {
        if (!control.bTouch[0]&&!control.bTouch[1]) {//charA noPress
            
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
        
            
        if (control.bTouch[0]&&!control.bTouch[1]) {//charA left
            if (rope_condition_A == R_NO_USE) {
                char_A.condition = C_LEFT;
            }
            if (rope_condition_B == R_SWING) {
                rope_condition_B = R_DESTROY;
            }
        }
        
        if(control.bTouch[1]&&!control.bTouch[0]){//charA right
            if (rope_condition_A == R_NO_USE) {
                char_A.condition = C_RIGHT;
            }
            if (rope_condition_B == R_SWING) {
                rope_condition_B = R_DESTROY;
            }
        }
        
        if(control.bTouch[0]&&control.bTouch[1]){//charA doublePress
            if (rope_condition_B == R_PUSH) {
                ofPoint dis =  hook_end_B - char_pos_A;
                if ( fabs(dis.x)< 50 && dis.y<=60) {
                    char_A.condition = C_HOOK_ROPE;
                    char_B.condition = C_SWING_ROPE;
                    rope_condition_B = R_SWING;
                }
            }
        }
    }
    
    //control char_B-------------------------------
    if (ofxAccelerometer.getForce().x>0.3 && rope_condition_B == R_NO_USE && rope_condition_A != R_SWING && !bInSky_B) {
        char_B.condition = C_PUSH_ROPE;
        hook_pct_B = 0;
        rope_condition_B = R_PUSH;
        
    }//charB pushRope
    
    if (char_B.condition != C_DEAD) {
         if (!control.bTouch[2]&&!control.bTouch[3]) {//charB noPress
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
        
         if (control.bTouch[2]&&!control.bTouch[3]) {//charB left
            if (rope_condition_B == R_NO_USE) {
                char_B.condition = C_LEFT;
            }
            if (rope_condition_A == R_SWING) {
                rope_condition_A = R_DESTROY;
            }
        }
        
         if(control.bTouch[3]&&!control.bTouch[2]){//charB right
            if (rope_condition_B == R_NO_USE) {
                char_B.condition = C_RIGHT;
            }
            
            if (rope_condition_A == R_SWING) {
                rope_condition_A = R_DESTROY;
            }
        }
        
         if(control.bTouch[2]&&control.bTouch[3]){//charB double press
            if (rope_condition_A == R_PUSH) {
                ofPoint dis =  hook_end_A - char_pos_B;
                if ( fabs(dis.x)< 50 && dis.y>=-60) {
                    char_B.condition = C_HOOK_ROPE;
                    char_A.condition = C_SWING_ROPE;
                    rope_condition_A = R_SWING;
                }
            }
        }
    }
    
    //swing rope A-------------------------------
    
    if (rope_condition_A == R_SWING) {
        
        if (!rope_joint.isSetup()) {
            rope_anchor.setup(world_B.getWorld(), rope_start_B.x, rope_start_B.y, 10);
            rope_joint.setup(world_B.getWorld(), rope_anchor.body, char_B.character.body);
//            float length = fabs(rope_start_B.y - char_B.getPos.y) - 100;
            float length = 250;
            rope_joint.setLength(length);
            rope_joint.setFrequency(0.5);
        }
        
//         char_B.rope_frame = ofClamp((462-rope_anchor.getPosition().distance(char_A.character.getPosition()))/5, 0, 39) ;
    }
    
    
    if (rope_condition_A == R_DESTROY) {
        if (rope_joint.isSetup()) {
            rope_joint.destroy();
            world_B.getWorld()->DestroyBody(rope_anchor.body);
        }
    }
     //swing rope B-------------------------------
    
    if (rope_condition_B == R_SWING) {
        
        if (!rope_joint.isSetup()) {
            rope_anchor.setup(world_A.getWorld(), rope_start_A.x, rope_start_A.y, 10);
            rope_joint.setup(world_A.getWorld(), rope_anchor.body, char_A.character.body);
//            float length = fabs(rope_start_A.y - char_A.getPos.y) - 100;
            float length = 250;
            rope_joint.setLength(length);
            rope_joint.setFrequency(0.5);
        }
        
    }
    
    if (rope_condition_B == R_DESTROY) {
        if (rope_joint.isSetup()) {
            rope_joint.destroy();
            world_A.getWorld()->DestroyBody(rope_anchor.body);
        }
    }
    
    //swing acclerometer-------------------------------
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
    if (rope_condition_A == R_SWING) {
        ofPoint diff =  char_B.character.getPosition() - rope_anchor.getPosition();
        char_B.angle = atan2(diff.x, diff.y);
    }else{
        char_B.angle = 0;
    }
    
    if (rope_condition_B == R_SWING) {
        ofPoint diff =  char_A.character.getPosition() - rope_anchor.getPosition();
        char_A.angle = PI-atan2(diff.x, diff.y);
    }else{
        char_A.angle = 0;
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

    //Character-------------------------------
    char_A.update();
    char_B.update();
    
    //dog-------------------------------
    dog_A.update();
    dog_B.update();
    if (dog_B.killZone.inside(char_B.character.getPosition().x, char_B.character.getPosition().y)) {
        char_B.condition = C_DEAD;
        dog_B.condition = D_BITE;
        rope_condition_A = R_DESTROY;
    }
    //emoji-------------------------------
    int preHappyness_A= happyness_A;
    int preHappyness_B= happyness_B;
    
    emoji_A.update(char_A.character.getPosition(), char_A.moveLeft);
    emoji_B.update(char_B.character.getPosition(), char_B.moveLeft);

    if (emoji_A.step == S_END) {
        e_startTime_A = ofGetElapsedTimeMillis();
    }
    
    if (emoji_B.step == S_END) {
        e_startTime_B = ofGetElapsedTimeMillis();
    }
        // getting angry
        //wait too long
    if (char_A.condition == C_STOP) {
        if (ofGetElapsedTimeMillis() - e_startTime_A > e_duration_A && emoji_A.condition == E_NONE) {
            happyness_A --;
        }
        if (happyness_A < 0){
         happyness_A = 0;
         preHappyness_A = -1;
        } 
    }
    
    if (char_B.condition == C_STOP) {
        if (ofGetElapsedTimeMillis() - e_startTime_B > e_duration_B && emoji_B.condition == E_NONE) {
            happyness_B--;
            cout<<"1"<<endl;
        }
        if (happyness_B < 0){
            happyness_B = 0;
            cout<<"2"<<endl;
            preHappyness_B = -1;
        }
    }
    
        //DEAD
    if (char_A.condition == C_DEAD) {
        happyness_A = 0;
        preHappyness_A = -1;
        
    }
    if (char_B.condition == C_DEAD) {
        happyness_B = 0;
        preHappyness_B = -1;
    }
        //swing rope
    if (char_A.condition == C_SWING_ROPE) {
        e_startTime_A = ofGetElapsedTimeMillis();
        int chance = ofRandom(200);
        if (chance == 1) happyness_A --;
        if (happyness_A <1) {
            happyness_A = 1;
            preHappyness_A = -1;
        }
    }
    
    if (char_B.condition == C_SWING_ROPE) {
        e_startTime_B = ofGetElapsedTimeMillis();
        int chance = ofRandom(200);
        if (chance == 1) happyness_B --;
        if (happyness_B <1) {
            happyness_B = 1;
            preHappyness_B = -1;
        }
    }
        
        // getting happy
        //run
    if (char_A.character.getVelocity().length() > 5 && emoji_A.condition == E_NONE) {
        e_startTime_A = ofGetElapsedTimeMillis();
        int chance = ofRandom(100);
        if (chance == 1) happyness_A ++;
        if (happyness_A > 4) {
            happyness_A = 4;
            preHappyness_A = 5;
        }
    }

    if (char_B.character.getVelocity().length() > 5 && emoji_B.condition == E_NONE) {
        e_startTime_B = ofGetElapsedTimeMillis();
        int chance = ofRandom(100);
        if (chance == 1) happyness_B ++;
        if (happyness_B > 4) {
            happyness_B = 4;
            preHappyness_B = 5;
        }
    }
    
    
    // emoji update
    if (preHappyness_A != happyness_A) {
        if(happyness_A == 4) {
            emoji_A.condition = E_LOVE;
            score_A+=5;
        }
        if(happyness_B == 3) emoji_B.condition = E_LAUGHING;
        if(happyness_B == 2) emoji_B.condition = E_HAPPY;
        if(happyness_B == 1) emoji_B.condition = E_SURPRISE;
        
        if(happyness_A == 0) {
            emoji_A.condition = E_ANGRY;
            score_A-=5;
        }
        if (happyness_A >preHappyness_A) {
            if(happyness_A == 3) score_A+=3;
            if(happyness_A == 2) score_A+=2;
            if(happyness_A == 1) score_A+=1;
        }
        
        
    }
    
    if (preHappyness_B != happyness_B) {
        if(happyness_B == 4) {
            emoji_B.condition = E_LOVE;
            score_B+=5;
        }
        if(happyness_B == 3) emoji_B.condition = E_LAUGHING;
        if(happyness_B == 2) emoji_B.condition = E_HAPPY;
        if(happyness_B == 1) emoji_B.condition = E_SURPRISE;
        
        if(happyness_B == 0) {
            emoji_B.condition = E_ANGRY;
            score_B-=5;
        }
        
        if (happyness_B >preHappyness_B) {
            if(happyness_B == 3) score_B+=3;
            if(happyness_B == 2) score_B+=2;
            if(happyness_B == 1) score_B+=1;
        }
    }
    
    // emoji offset
    char_A.condition == C_HOOK_ROPE? emoji_A.swing = true:emoji_A.swing = false;
    char_B.condition == C_HOOK_ROPE?emoji_B.swing = true:emoji_B.swing = false;

    cout<<ofGetElapsedTimeMillis() - e_startTime_B<<"  "<<char_B.condition<<endl;
}

//--------------------------------------------------------------
void testApp::draw(){
    ofColor dark(80);
    ofBackgroundGradient(dark, ofColor::black);
   
    drawScene(0);
    accIndictor.draw();
    control.draw();
    
    ofSetColor(30, 30, 30);
    font.drawString("SCORE_A\n"+ofToString(score_A), 100, ofGetHeight()/2);
    font.drawString("SCORE_B\n"+ofToString(score_B), ofGetWidth()-200, ofGetHeight()/2);
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
        dog_A.draw();
        char_A.draw();
        emoji_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        dog_B.draw();
        char_B.draw();
        emoji_B.draw();
        ofPopMatrix();

        //draw swing rope A
        
        if (rope_condition_A == R_SWING) {
            ofPushMatrix();
            ofTranslate(screen_B);
            if (rope_joint.isSetup()) {
                ofSetColor(44,220);
//                rope_anchor.draw();
                rope_joint.draw();
            }
//            ofCircle(char_B.character.getPosition().x, char_B.character.getPosition().y, 10);
            ofPopMatrix();
        }
        
         //draw swing rope B
        if (rope_condition_B == R_SWING) {
             ofPushMatrix();
             ofTranslate(screen_A);
            if (rope_joint.isSetup()) {
                ofSetColor(44,220);
//                rope_anchor.draw();
                rope_joint.draw();
            }
           
//          ofCircle(char_A.character.getPosition().x, char_A.character.getPosition().y, 10);
            ofPopMatrix();
        }

    }
    
   
   
    //push rope
  
    if (rope_condition_A == R_PUSH) {
        float speed = 0.1f;
        hook_pct_A +=speed;
        if (hook_pct_A > 1) hook_pct_A = 1;
        hook_end_A.x = hook_start_A.x;
        hook_end_A.y = (1-hook_pct_A)*hook_start_A.y + hook_pct_A*(500+hook_start_A.y);
        
//        ofSetColor(0,100);
//        ofLine(hook_start_A.x,hook_start_A.y,hook_end_A.x, hook_end_A.y);
//        ofCircle(hook_end_A.x, hook_end_A.y, 10);
    }
    
    
    
    if (rope_condition_B == R_PUSH) {
        float speed = 0.1f;
        hook_pct_B +=speed;
        if (hook_pct_B > 1) hook_pct_B = 1;
        hook_end_B.x = hook_start_B.x;
        hook_end_B.y = (1-hook_pct_B)*hook_start_B.y + hook_pct_B*(hook_start_B.y-500);
        
//        ofSetColor(0,100);
//        ofSetLineWidth(2.5);
//        ofLine(hook_start_B.x,hook_start_B.y,hook_end_B.x, hook_end_B.y);
//        ofCircle(hook_end_B.x, hook_end_B.y, 10);
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
    
    ofPoint offset_A(10,8);
    ofPoint offset_B(5,20);
    if (char_A.moveLeft) hook_start_A.x = char_pos_A.x - offset_A.x;
    else hook_start_A.x = char_pos_A.x + offset_A.x;
    hook_start_A.y = char_pos_A.y + offset_A.y;
    
    if (char_B.moveLeft) hook_start_B.x = char_pos_B.x - offset_B.x;
    else hook_start_B.x = char_pos_B.x + offset_B.x;
    hook_start_B.y = char_pos_B.y - offset_B.y;
    //rope postion
    rope_start_A = hook_start_B - screen_A;
//    rope_end_A = hook_end_B - screen_A;
   
    rope_start_B = hook_start_A - screen_B;
//    rope_end_B = hook_end_A - screen_B;

}