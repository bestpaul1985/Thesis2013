#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){
    
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.9f);
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    ofEnableAlphaBlending();
    ofSetCircleResolution(6);
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
    //ground
//    ground_A.setup(0, 0, world_A);
//    ground_B.setup(0, 1, world_B);
    
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
    char_Render[0] = new ofxSpriteSheetRenderer(1, 10000, 0, 85);
    char_Render[1] = new ofxSpriteSheetRenderer(1, 10000, 0, 84);
    char_Render[2] = new ofxSpriteSheetRenderer(1, 10000, 0, 39);
    char_Render[3] = new ofxSpriteSheetRenderer(1, 10000, 0, 84);
    char_Render[4] = new  ofxSpriteSheetRenderer(1, 10000, 0, 84);
    char_Render[0]->loadTexture("sprites/all_girl.png", 2040, GL_NEAREST);
    char_Render[1]->loadTexture("sprites/push_girl.png", 1000, GL_NEAREST);
    char_Render[2] ->loadTexture("sprites/run_boy.png", 1000, GL_NEAREST);
    char_Render[3] ->loadTexture("sprites/push_boy.png", 1000, GL_NEAREST);
    char_Render[4] ->loadTexture("sprites/pull_boy.png", 1000, GL_NEAREST);
    
    char_A.setup(world_A, ofPoint(0,0), 0,char_Render[0],char_Render[1],char_Render[1]);
    char_B.setup(world_B, ofPoint(0,0), 1,char_Render[2],char_Render[3],char_Render[4]);
    //camera
    translate_A.set(384,768/2);
    translate_B.set(384,768/2);
    camera_A = char_A.getPos;
    camera_B = char_B.getPos;
    //thorn
    thorns_A.setup(world_A, 0,0);
    thorns_B.setup(world_B, 0,1);
    
    //sky
    skyBg.loadImage("sprites/bg/sky/background.png");
    sky.setup(skyBg);
    //indictor
    accIndictor.setup(ofxAccelerometer.getForce());
    
    //rope
    rope_A.setup(world_B, char_A, char_B, rope_start_B, hook_start_A, hook_end_A, ofxAccelerometer.getForce(), 0);
    rope_B.setup(world_A, char_B, char_A, rope_start_A, hook_start_B, hook_end_B, ofxAccelerometer.getForce(), 1);

    //booleans
    bInSky_A = false;
    bInSky_B = false;
    levelOver_A = false;
    levelOver_B = false;
    levelRester = true;
    bStatistics = false;
    //renderers
//    dog_Render = new ofxSpriteSheetRenderer(1, 1000, 0, 120);
//    dog_Render ->loadTexture("sprites/all_dog.png", 2040, GL_NEAREST);
//    rabit_Render = new ofxSpriteSheetRenderer(1, 1000, 0, 30);
//    rabit_Render ->loadTexture("sprites/rabit.png", 2040, GL_NEAREST);
    
    //dog
    dog_A.setup(world_A,dog_Render, -1000, 2000, 0);
    dog_B.setup(world_B,dog_Render, -1000, 2000, 1);
    //rabit
    rabit_A.setup(world_A,rabit_Render, -200, 2000, 0);
    rabit_B.setup(world_B,rabit_Render, -200, 2000, 1);
    //emoji
    emoji_A.setup(char_A.character.getPosition(),char_A,0);
    emoji_B.setup(char_B.character.getPosition(),char_B,1);
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
    
    
    //score
    font.loadFont("font/NewMedia Fett.ttf", 20);
    
    
    //meun
    logo.loadImage("menu/firstmenuLogo72.png");
    mainMenuText.loadImage("menu/firstmenuText72.png");
    main_menu.setup(skyBg, logo,mainMenuText);
    
    condition = MAIN_MEUN;
    game_menu.setup();
    
    //gameEnd;
    gameEnd_bg.loadImage("menu/emojigraph72.png");
    gameEnd_font.loadFont("font/NewMedia Fett.ttf", 12);
    
    //minigame
    catchGame.setup(ofxAccelerometer.getForce(), control);
    timer = 0;
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
            
            if (bData&&bData->name == "door" && condition != MAIN_MEUN) {
                levelOver_A = true;
            }
        }
        else if (bData && bData->name == "footSenser"){
            numFootContacts_A++;
            if (bData&&bData->name == "thorn") {
                char_A.condition = C_DEAD;
            }
            
            if (bData&&bData->name == "door" && condition != MAIN_MEUN) {
                levelOver_A = true;
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
            if (bData&&bData->name == "door" && condition != MAIN_MEUN) {
                levelOver_A = false;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_A--;
            if (bData&&bData->name == "door" && condition != MAIN_MEUN) {
                levelOver_A = false;
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
                char_B.condition = C_DEAD;
            }
            if (bData&&bData->name == "door" && condition != MAIN_MEUN) {
                levelOver_B = true;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B++;
            if (bData&&bData->name == "thorn") {
               char_B.condition = C_DEAD;
            }
            if (bData&&bData->name == "door" && condition != MAIN_MEUN) {
                levelOver_B = true;
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
            if (bData&&bData->name == "door" && condition != MAIN_MEUN) {
                levelOver_B = false;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B--;
            if (bData&&bData->name == "door" && condition != MAIN_MEUN) {
                levelOver_B = false;
            }
        } 
    }
}
//--------------------------------------------------------------
void testApp::update(){
    

    switch (condition) {
        case MAIN_MEUN:{
            if (levelRester) {
                groundNew_A.setup("levelTxt/level1var1A.txt", world_A);
                groundNew_B.setup("levelTxt/level1var1B.txt", world_B);
                levelRester = false;
            }
            
            if (control.bAllTouch) {
                timer ++;
                if (timer>100) {
                    timer = 0;
                    condition = LEVEL_1;
                    gameReset();
                }
            }
            
            
            
        }break;
        case LEVEL_1:{
            
            if (levelRester) {
                groundNew_A.setup("levelTxt/level1var1A.txt", world_A);
                groundNew_B.setup("levelTxt/level1var1B.txt", world_B);
                levelRester = false;
            }
            
            if (!game_menu.show) {
                world_A.update();
                world_B.update();
                gamePlay(0);
            }
            if (game_menu.goMain) {
                game_menu.goMain = false;
                condition = MAIN_MEUN;
            }
        
            if (levelOver_A && levelOver_B) {
                char_A.condition = C_MINIGAME;
                char_B.condition = C_MINIGAME;
                rope_A.condition = R_MINIGAME;
                rope_B.condition = R_MINIGAME;
                catchGame.update();
            }
            
            if (catchGame.bFinish) {
                bStatistics = true;
                catchGame.bFinish = false;
            }
            
            if (bStatistics && control.bAllTouch) {
                timer ++;
                if (timer > 100) {
                    timer = 0;
                    condition = LEVEL_2;
                    gameReset();
                    groundNew_A.destroy();
                    groundNew_B.destroy();
                }
            }
            
        }break;
        case LEVEL_2:{
            if (levelRester) {
                groundNew_A.setup("levelTxt/level1var1A.txt", world_A);
                groundNew_B.setup("levelTxt/level1var1B.txt", world_B);
                levelRester = false;
            }
            
            if (!game_menu.show) {
                world_A.update();
                world_B.update();
                gamePlay(0);
            }
            if (game_menu.goMain) {
                game_menu.goMain = false;
                condition = MAIN_MEUN;
            }
            
            if (levelOver_A && levelOver_B) {
                char_A.condition = C_MINIGAME;
                char_B.condition = C_MINIGAME;
                rope_A.condition = R_MINIGAME;
                rope_B.condition = R_MINIGAME;
                catchGame.update();
            }
            
            if (catchGame.bFinish) {
                bStatistics = true;
                catchGame.bFinish = false;
            }
            
            if (bStatistics && control.bAllTouch) {
                timer ++;
                if (timer > 100) {
                    timer = 0;
                    condition = MAIN_MEUN;
                    gameReset();
                    groundNew_A.destroy();
                    groundNew_B.destroy();
                }
            }
            
        }break;
        case LEVEL_3:{
        }break;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    switch (condition) {
            
        case MAIN_MEUN:{
            main_menu.draw();
            control.draw();
        } break;
            
        case LEVEL_1:{
            drawScene(0);
            game_menu.draw();
            if (levelOver_A && levelOver_B) {
                catchGame.draw();
                rope_A.draw_minigame(ofPoint(500,500));
                rope_B.draw_minigame(ofPoint(500,500));
            }
            if (bStatistics) {
                gameEnd(0);
            }
            control.draw();
            
        }break;
        case LEVEL_2:{
            if (levelOver_A && levelOver_B) {
                gameEnd(1);
            }
            else{
                drawScene(1);
                game_menu.draw();
            }
            control.draw();
            
        }break;
        case LEVEL_3:{
            if (levelOver_A && levelOver_B) {
                gameEnd(2);
            }
            else{
                drawScene(2);
                game_menu.draw();
            }
            control.draw();
            
        }break;
    }
    

       
    ofDrawBitmapStringHighlight("world: " + ofToString(char_A.getPos,2)+"\nScreen: "+ofToString(char_A.getPos+screen_A,2), 50,50);
    ofDrawBitmapStringHighlight("world: " + ofToString(char_B.getPos,2)+"\nScreen: "+ofToString(char_B.getPos+screen_B,2), 750,700);

}
//-------------------------------------------------------------
void testApp::drawScene(int level){
    sky.drawBg();

   
                
        ofPushMatrix();
        ofTranslate(screen_A);
        groundNew_A.draw();
        thorns_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        groundNew_B.draw();
        thorns_B.draw();
        ofPopMatrix();
        
        sky.drawCloud();
    if (level == 0) {
      
    }
    if (level == 1) {
        
    }
    if (level == 2) {
        
    }
    
        ofPushMatrix();
        ofTranslate(screen_A);
        char_A.draw();
        emoji_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        char_B.draw();
        emoji_B.draw();
        ofPopMatrix();
    
        //draw swing rope A
        rope_A.draw_swing(screen_B);
        rope_A.draw_push();
        rope_B.draw_swing(screen_A);
        rope_B.draw_push();
    
    
            
}
//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    switch (condition) {
        case MAIN_MEUN:
            
            break;
            
        case LEVEL_1:
            game_menu.touchDown(touch.x, touch.y,touch.id);
            break;
    }
    
    control.touchDown(touch.x, touch.y,touch.id);
    ofPoint pos(touch.x, touch.y);
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
void testApp::position(int level){

    bool A[10],B[10];
    float catchUpSpeed = 0.05f;
    ofPoint catch_A, catch_B;
   
    if (level == 0) {
        char_A.getPos.x<0? A[0] = true: A[0] =false;
        char_B.getPos.x<0? B[0] = true: B[0] =false;
   
        char_A.getPos.x>1690? A[1] = true: A[1] =false;
        char_B.getPos.x>1690? B[1] = true: B[1] =false;
        
        //camera setup
        if (A[0]) {
            catch_A.x = 0;
            catch_A.y = char_A.getPos.y;
        }else if(A[1]){
            catch_A.x = 1690;
            catch_A.y = -180;
        }else{
            catch_A.x = char_A.getPos.x;
            catch_A.y = char_A.getPos.y;
        }
        
        if (B[0]) {
            catch_B.x = 0;
            catch_B.y = char_B.getPos.y;
        }else if(B[1]){
            catch_B.x = 1690;
            catch_B.y = 180;
        }else{
            catch_B.x = char_B.getPos.x;
            catch_B.y = char_B.getPos.y;
        }

    }
        
    
    if (rope_B.condition != R_SWING) {
        camera_A.x = catchUpSpeed * catch_A.x + (1-catchUpSpeed) * camera_A.x;
        camera_A.y = catchUpSpeed * catch_A.y + (1-catchUpSpeed) * camera_A.y;
    }
       
    if (rope_A.condition != R_SWING) {
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
    ofPoint offset_A(15,8);
    ofPoint offset_B(-4,22);
    if (char_A.moveLeft) hook_start_A.x = char_pos_A.x - offset_A.x;
    else hook_start_A.x = char_pos_A.x + offset_A.x;
    hook_start_A.y = char_pos_A.y + offset_A.y;
    
    if (char_B.moveLeft) hook_start_B.x = char_pos_B.x - offset_B.x;
    else hook_start_B.x = char_pos_B.x + offset_B.x;
    hook_start_B.y = char_pos_B.y - offset_B.y;
   
    //rope postion
    rope_start_A = hook_start_B - screen_A;
//  rope_end_A = hook_end_B - screen_A;
   
    rope_start_B = hook_start_A - screen_B;
//  rope_end_B = hook_end_A - screen_B;

}

//--------------------------------------------------------------
void testApp::gamePlay(int level){

//    if (level == 0 && levelRester) {
//        dog_A.dog.setPosition(-1000, 2000);
//        dog_B.dog.setPosition(-1000, 2000);
//        
//        thorns_A.setup(world_A, 0,0);
//        thorns_B.setup(world_B, 0,1);
//        levelRester = false;
//    }
//    
//    if (level == 1 && levelRester) {
//        rabit_A.rabit.setPosition(0, 0);
//        rabit_A.rabit.setPosition(0, 0);
//        
//        thorns_A.setup(world_A, 0,0);
//        thorns_B.setup(world_B, 0,1);
//        levelRester = false;
//    }
    
//    if (level == 2 && levelRester) {
//        dog_A.dog.setPosition(0, 0);
//        dog_B.dog.setPosition(0, 0);
//        
//        thorns_A.setup(world_A, 0,0);
//        thorns_B.setup(world_B, 0,1);
//        levelRester = false;
//    }
    
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
    position(level);
    //control char_A-------------------------------
    if (ofxAccelerometer.getForce().x<-0.3 && rope_A.condition == R_NO_USE && rope_B.condition != R_SWING&& !bInSky_A&&char_A.condition != C_MINIGAME) {
        char_A.condition = C_PUSH_ROPE;
        rope_A.hook_pct  = 0;
        rope_A.condition = R_PUSH;
    }//charA pushRope
    
    if (char_A.condition != C_DEAD&&char_A.condition != C_MINIGAME) {
        if (!control.bTouch[0]&&!control.bTouch[1]) {//charA noPress
            
            if (rope_A.condition==R_NO_USE&& !bInSky_A) {
                char_A.condition = C_STOP;
            }
            
            if (rope_B.condition == R_SWING) {
                rope_B.condition = R_DESTROY;
            }
            
            if (rope_B.condition == R_DESTROY) {
                char_B.condition = C_STOP;
            }
        }
        
        
        if (control.bTouch[0]&&!control.bTouch[1]) {//charA left
            if (rope_A.condition == R_NO_USE) {
                char_A.condition = C_LEFT;
            }
            if (rope_B.condition == R_SWING) {
                rope_B.condition  = R_DESTROY;
            }
        }
        
        if(control.bTouch[1]&&!control.bTouch[0]){//charA right
            if (rope_A.condition  == R_NO_USE) {
                char_A.condition = C_RIGHT;
            }
            if (rope_B.condition  == R_SWING) {
                rope_B.condition  = R_DESTROY;
            }
        }
        
        if(control.bTouch[0]&&control.bTouch[1]){//charA doublePress
            if (rope_B.condition  == R_PUSH) {
                ofPoint dis =  hook_end_B - char_pos_A;
                if ( fabs(dis.x)< 50 && dis.y<=60) {
                    char_A.condition = C_HOOK_ROPE;
                    char_B.condition = C_SWING_ROPE;
                    rope_B.condition  = R_SWING;
                }
            }
        }
    }
    
    //control char_B-------------------------------
    if (ofxAccelerometer.getForce().x>0.3 && rope_B.condition  == R_NO_USE && rope_A.condition != R_SWING && !bInSky_B&&char_B.condition != C_MINIGAME) {
        char_B.condition = C_PUSH_ROPE;
        rope_B.hook_pct = 0;
        rope_B.condition  = R_PUSH;
        
    }//charB pushRope
    
    if (char_B.condition != C_DEAD&&char_B.condition != C_MINIGAME) {
        if (!control.bTouch[2]&&!control.bTouch[3]) {//charB noPress
            if (rope_B.condition==R_NO_USE && !bInSky_B) {
                char_B.condition = C_STOP;
            }
            
            
            if (rope_A.condition == R_SWING) {
                rope_A.condition = R_DESTROY;
            }
            
            if (rope_A.condition == R_DESTROY) {
                char_A.condition = C_STOP;
            }
        }
        
        if (control.bTouch[2]&&!control.bTouch[3]) {//charB left
            if (rope_B.condition == R_NO_USE) {
                char_B.condition = C_LEFT;
            }
            if (rope_A.condition == R_SWING) {
                rope_A.condition = R_DESTROY;
            }
        }
        
        if(control.bTouch[3]&&!control.bTouch[2]){//charB right
            if (rope_B.condition == R_NO_USE) {
                char_B.condition = C_RIGHT;
            }
            
            if (rope_A.condition == R_SWING) {
                rope_A.condition = R_DESTROY;
            }
        }
        
        if(control.bTouch[2]&&control.bTouch[3]){//charB double press
            if (rope_A.condition == R_PUSH) {
                ofPoint dis =  hook_end_A - char_pos_B;
                if ( fabs(dis.x)< 50 && dis.y>=-60) {
                    char_B.condition = C_HOOK_ROPE;
                    char_A.condition = C_SWING_ROPE;
                    rope_A.condition = R_SWING;
                }
            }
        }
    }
    //rope--------------------------------------
    rope_A.update();
    rope_B.update();
    
    //Character-------------------------------
    char_A.update();
    char_B.update();
    
    //emoji-------------------------------
    emoji_A.update(char_A.character.getPosition(), char_A.moveLeft);
    emoji_B.update(char_B.character.getPosition(), char_B.moveLeft);
    emoji_A.control();
    emoji_B.control();
    //dog-------------------------------
    if (level == 0) {
        
    }
    
    if (level == 1) {
        //dog-------------------------------
        dog_A.update();
        dog_B.update();
        if (dog_B.killZone.inside(char_B.character.getPosition().x, char_B.character.getPosition().y)) {
            char_B.condition = C_DEAD;
            dog_B.condition = D_BITE;
            rope_A.condition = R_DESTROY;
        }
        //rabit-------------------------------
        rabit_A.update();
        rabit_B.update();
    }
   
    
}

//--------------------------------------------------------------
void testApp::gameEnd(int level){
    float orgRadius = 180;
    int max;
    int number[5];
    float angle[5];
    float radius[5];
    ofPoint pts[5];
    ofPoint orgPos(ofGetWidth()/2, ofGetHeight()/2);
    ofPoint icon_pts[5];
    ofPolyline path;
    float offSet = 30;
    number[0] = emoji_A.num_love+emoji_B.num_love;
    number[1] = emoji_A.num_happy+ emoji_B.num_happy;
    number[2] = emoji_A.num_laughing+ emoji_B.num_laughing;
    number[3] = emoji_A.num_angry + emoji_B.num_angry;
    number[4] = emoji_A.num_surprise+ emoji_B.num_surprise;
    
//    number[0] = 10;
//    number[1] = 20;
//    number[2] = 30;
//    number[3] = 40;
//    number[4] = 50;
//    
    angle[0] = 90;
    angle[1] = 150;
    angle[2] = 210;
    angle[3] = 330;
    angle[4] = 30;
    
    for (int i=1; i<5; i++) {
        max = MAX(number[i], number[i-1]);
    }
    
    radius[0] = ofMap(number[0], 0, max, 50, orgRadius, true);
    radius[1] = ofMap(number[1], 0, max, 50, orgRadius, true);
    radius[2] = ofMap(number[2], 0, max, 50, orgRadius, true);
    radius[3] = ofMap(number[3], 0, max, 50, orgRadius, true);
    radius[4] = ofMap(number[4], 0, max, 50, orgRadius, true);
    
    ofSetColor(255);
    skyBg.draw(0, 0);
    
    for (int i=0; i<5; i++) {
        pts[i].x =  radius[i]*cos(angle[i]*DEG_TO_RAD);
        pts[i].y = radius[i]*-sin(angle[i]*DEG_TO_RAD);
        icon_pts[i].x = (orgRadius+offSet)*cos(angle[i]*DEG_TO_RAD);
        icon_pts[i].y = (orgRadius+offSet)*-sin(angle[i]*DEG_TO_RAD);
        path.addVertex(pts[i]);
    }
    path.close();
    

    // draw the mesh
    ofMesh mesh;
    ofMesh meshBG;
    meshBG.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    vector < ofPoint > meshPts = path.getVertices();
    for (int i = 0; i < meshPts.size(); i++){
        meshBG.addVertex(meshPts[i]);
    }
    
    
    ofPushMatrix();
    ofTranslate(orgPos);
    ofSetColor(144,143,142,125);
    ofFill();
    meshBG.draw();
//    for (int i=0; i<5; i++) {
//        ofSetColor(255, 30, 100);
//        ofLine(0,0, pts[i].x, pts[i].y);
//    }
//    ofSetColor(0,125);
//    ofSetLineWidth(1);
//    path.draw();
    ofPopMatrix();
    
   ;
    for (int i=0; i<5; i++) {
        ofPushMatrix();
        ofRectangle rect;
        rect = gameEnd_font.getStringBoundingBox(ofToString(number[i]), 0, 0);
        ofTranslate(orgPos.x+icon_pts[i].x,orgPos.y+icon_pts[i].y);
        
        if (i==0) {
            ofRotateZ(0);
        }
        if (i==1) {
            ofRotateZ(-60);
        }
        if (i==2) {
            ofRotateZ(-120);
        }
        if (i==3) {
            ofRotateZ(-240);
        }
        if (i == 4) {
            ofRotateZ(-300);
        }
        
        ofSetColor(30);
        gameEnd_font.drawString(ofToString(number[i]),-rect.getWidth()/2,-rect.getHeight()/2);
        ofPopMatrix();
    }
    
    
    ofSetColor(255);
    gameEnd_bg.draw(0,0);
    
   
}

//--------------------------------------------------------
void testApp::gameReset(){
    bInSky_A = false;
    bInSky_B = false;
    levelOver_A = false;
    levelOver_B = false;
    bStatistics = false;
    levelRester = true;
    numFootContacts_A = 0;
    numFootContacts_B = 0;
    rope_A.condition = R_NO_USE;
    rope_B.condition = R_NO_USE;
    char_A.condition = C_STOP;
    char_B.condition = C_STOP;
    char_A.character.setPosition(0, 0);
    char_B.character.setPosition(0, 0);
    camera_A.set(0, 0);
    camera_B.set(0, 0);
    
}


