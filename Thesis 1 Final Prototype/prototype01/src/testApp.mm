#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	
	ofxAccelerometer.setup();
	ofEnableAlphaBlending();
	ofBackground(30,30,30);
    bgImg.loadImage("image/back.jpg");
    bgP1.loadImage("image/terraingrey.png");
    bgP2.loadImage("image/terrainbrown.png");
    //*********** Sound ****************
    bgm.loadSound("sound/takkreverse.wav");
    bgm.setMultiPlay(false);
    bgm.setLoop(true);
    bgm.play();
    bgm.setVolume(0.1f);
    jumpSound.loadSound("sound/Jump.wav");
    jumpSound.setMultiPlay(true);
    pickUpKeySound.loadSound("sound/Pickup_Key.wav");
    pickUpKeySound.setMultiPlay(true);
    pickUpRopeSound.loadSound("sound/Pickup_Rope.wav");
    pickUpRopeSound.setMultiPlay(true);
    useRopeSound.loadSound("Use_rope.wav");
    useRopeSound.setMultiPlay(true);
    //***********box2d P1****************
    worldP1.init();
    worldP1.setGravity(0, 100);
    //  worldP1.createBounds();
    ofPoint one(0,ofGetHeight());
    ofPoint two(3000,ofGetHeight());
    worldP1.createGround(one, two);
    worldP1.setIterations(1, 1);
    worldP1.setFPS(60);
    //***********box2d P2****************
    worldP2.init();
    worldP2.setGravity(0, -100);
    //  worldP2.createBounds();
    one.set(-3000,0);
    two.set(1000,0);

    worldP2.createGround(one, two);
    worldP2.setIterations(1, 1);
    worldP2.setFPS(60);
    
    
    //************ MAP ***************
	
    
    if (XML.loadFile("tutorialLevelP1.xml")) {
        int strokeNum = XML.getNumTags("STROKE");
        for (int i=0; i<strokeNum; i++) {
            XML.pushTag("STROKE",i);
            int ptNum = XML.getNumTags("PT");
            if (ptNum>0) {
                ofxBox2dPolygon tempPolyline;
                for (int j=0; j<ptNum; j++) {
                    int x = XML.getValue("PT:X", 0, j);
                    int y = XML.getValue("PT:Y", 0, j);
                    ofPoint tempP;
                    tempP.set(x-2220, y-1514);
                    tempPolyline.addVertex(tempP);
                }
                tempPolyline.setPhysics(0, 0, 0.2f);
                tempPolyline.create(worldP1.getWorld());
                polyLines1.push_back(tempPolyline);
            }
            XML.popTag();
        }
    }
	
    if (XML2.loadFile("tutorialLevelP2.xml")) {
        int strokeNum = XML2.getNumTags("STROKE");
        for (int i=0; i<strokeNum; i++) {
            XML2.pushTag("STROKE",i);
            int ptNum = XML2.getNumTags("PT");
            if (ptNum>0) {
                ofxBox2dPolygon tempPolyline;
                for (int j=0; j<ptNum; j++) {
                    int x = XML2.getValue("PT:X", 0, j);
                    int y = XML2.getValue("PT:Y", 0, j);
                    ofPoint tempP;
                    tempP.set(x-2220, y-1514);
                    tempPolyline.addVertex(tempP);
                }
                tempPolyline.setPhysics(0, 0, 0.2f);
                tempPolyline.create(worldP2.getWorld());
                polyLines2.push_back(tempPolyline);
            }
            XML2.popTag();
        }
    }
    
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
    myGuy.setup(chracater1.getPosition().x,chracater1.getPosition().y);
    chracater1.setPhysics(3, 0, 0.5f);
    chracater1.setup(worldP1.getWorld(), 200, 800, myGuy.width/2, myGuy.height/2);
    chracater1.body->SetFixedRotation(true);
    myGuy.getCenter = chracater1.getPosition();
    lastPosP1 = chracater1.getPosition();
    //********** Girl *******************
    myGirl.setup(chracater2.getPosition().x, chracater2.getPosition().y);
    chracater2.setPhysics(3, 0, 0.5f);
    chracater2.setup(worldP2.getWorld(), 568, 224, myGirl.width/2, myGirl.height/2);
    chracater2.body->SetFixedRotation(true);
    myGirl.getCenter = chracater2.getPosition();
    lastPosP2 = chracater2.getPosition();
    //********** keys *******************
    key1.setup(0);
    keysubstitute1.setPhysics(1, 0, 0.999f);
    keysubstitute1.setup(worldP1.getWorld(), ofGetWidth()/2, 800, key1.width/2, key1.height/2);
    keyState1 = 0;
    key1UsedP1 = false;
    key1UsedP2 = false;
    
    key2.setup(1);
    keysubstitute2.setPhysics(1, 0, 0.999f);
    keysubstitute2.setup(worldP2.getWorld(), ofGetWidth()/2, 224, key2.width/2, key2.height/2);
    keyState2 = 0;
    key2UsedP1 = false;
    key2UsedP2 = false;
    //*********** passing belt *******************
    beltP1.addVertex(myGuy.getCenter);
    beltP1.addVertex(myGuy.getCenter);
    beltP2.addVertex(myGirl.getCenter);
    beltP2.addVertex(myGirl.getCenter);
    beltLastPosP1 = myGuy.getCenter;
    beltLastPosP2 = myGirl.getCenter;
    beltPosP1.set(myGuy.getCenter.x+30, myGuy.getCenter.y);
    beltPosP2.set(myGirl.getCenter.x-30, myGirl.getCenter.y);
    beltPosRopeP1.set(myGuy.getCenter.x+30, myGuy.getCenter.y);
    beltPosRopeP2.set(myGirl.getCenter.x-30, myGirl.getCenter.y);
    beltPctP1 = 0;
    beltPctP2 = 0;
    //*********** chests *******************
    myChest1.setup(0);
    myChest2.setup(1);
    chestSub1.setPhysics(0, 0, 0);
    chestSub1.isFixed();
    chestSub1.setup(worldP1.getWorld(), ofGetWidth()/2+200 ,ofGetHeight()-175, myChest1.width1/2, myChest1.height1/2);
    chestSub2.setPhysics(0, 0, 0);
    chestSub2.isFixed();
    chestSub2.setup(worldP2.getWorld(), ofGetWidth()/2-200 ,155, myChest2.width1/2, myChest2.height1/2);
    
    //********* elevter *******************
    myEleP1.setup(100, 800 , 0);
    myEleP2.setup(668, 165 , 1);
    
    //********* inventory *******************
    invP1.setup(394, 960, 0);
    invP2.setup(374, 64, 1);
    
    //********* rope *******************
    
    rope1.setup(chestSub1.getPosition().x, chestSub1.getPosition().y, 0);
    rope2.setup(chestSub2.getPosition().x, chestSub2.getPosition().y, 1);
   
    posRope1.setInitialCondition(chestSub1.getPosition().x, chestSub1.getPosition().y, 0, 0);
    posRope2.setInitialCondition(chestSub2.getPosition().x, chestSub2.getPosition().y, 0, 0);
   
    posRope1.damping = 0.05f;
    posRope2.damping = 0.05f;
    
    posClimb.set(0, 0);
    posClimb2.set(0, 0);
    
    climbUp = 150;
    climbUp2 = -150;
    
    bRopeIconAnimationDone1 = false;
    bRopeIconAnimationDone2 = false;
    
    bRopeInUse1 = false;
    bRopeInUse2 = false;
    
    bClimb = false;
    bClimb2 = false;
    
    bRope1 = true;
    bRope2 = true;
   
    ropeMesh1.setup();
    ropeMesh2.setup();
    ropeMesh2.num = 1;
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    worldP1.update();
    worldP2.update();
    ofSoundUpdate();
    
    if (bRopeSound) {
        pickUpRopeSound.play();
        bRopeSound = false;
    }
    //*********** box2d P1*******************
    ofPoint frc1(0,0);
    ofPoint frc2(0,0);
    
    
    if (P1L.bPressed){
        frc1.x = -100;
        myGuy.bReverse=true;
    }
    if (P1R.bPressed){
        frc1.x = 100;
        myGuy.bReverse=false;
    }

    chracater1.addForce(frc1,10);
   
    
    if(bClimb2){
        cout<<"2"<<endl;
        if (P2F.bPressed) {
            climbUp2 -=5;
        }
        if (climbUp2<-180) {
            climbUp2 = -180;
        }
        chracater1.addAttractionPoint(posClimb2.x , posClimb2.y+climbUp2, 100);
        if ((ropeStroke2.getClosestPoint(myGuy.getCenter)- myGuy.getCenter).length() > myGuy.height/2+20) {
            cout<<"3"<<endl;
            bClimb2 = false;
            climbUp2 = -150;
            bRopeInUse2 = false;
            invP2.num = 3;
            ropeStroke2.clear();
            ropeMesh2.mesh.clear();
        }
        chracater1.setDamping(0.8f);
    }else{
        chracater1.setDamping(0.98f);
    }

    
    //*********** box2d P2*******************
    
    if (P2L.bPressed) {
        frc2.x = 100;
        myGirl.bReverse=true;
    }
    if (P2R.bPressed){
        frc2.x = -100;
        myGirl.bReverse=false;
    }
    chracater2.addForce(frc2,10);
   
    if(bClimb){
        cout<<"2"<<endl;
        if (P2F.bPressed) {
            climbUp +=5;
        }
        if (climbUp>180) {
            climbUp = 180;
        }
        chracater2.addAttractionPoint(posClimb.x,posClimb.y+climbUp, 100);
        if ((ropeStroke1.getClosestPoint(myGirl.getCenter)- myGirl.getCenter).length() > myGirl.height/2+20) {
            cout<<"3"<<endl;
            bClimb = false;
            climbUp = 150;
            bRopeInUse1 = false;
            invP1.num = 2;
            ropeStroke1.clear();
            ropeMesh1.mesh.clear();
        }
        chracater2.setDamping(0.8f);
    }else{
        chracater2.setDamping(0.98f);
    }
    
    
   
    
    
    //*********** diffP1 *******************
    diffP1 = chracater1.getPosition()-lastPosP1;
    //*********** diffP2 *******************
    diffP2 = chracater2.getPosition()-lastPosP2;
    //*********** Guy *******************
    float min = 384-50;
    float max = 384+50;
    if (bFixedButtonP2 == true) {
            
        if (chracater1.getPosition().x > 0&& chracater1.getPosition().x <min ) {
            
             myGuy.update(myGuy.getCenter.x + diffP1.x ,chracater1.getPosition().y);
            
        }else if( chracater1.getPosition().x > (3000-max)&& chracater1.getPosition().x <3000 ){
            
             myGuy.update(myGuy.getCenter.x + diffP1.x,chracater1.getPosition().y);
            
        }else{
            
            if(myGuy.getCenter.x <= max && myGuy.getCenter.x >=min){
                myGuy.update(myGuy.getCenter.x + diffP1.x, chracater1.getPosition().y);
                
            }
            
            if(myGuy.getCenter.x > max){
                myGuy.update(max, chracater1.getPosition().y);
                offSet = chracater1.getPosition() - myGuy.getCenter;
            }
            
            if(myGuy.getCenter.x < min){
                myGuy.update(min, chracater1.getPosition().y);
                offSet = chracater1.getPosition() - myGuy.getCenter;
            }
        }
    }else{
        myGuy.update(384,chracater1.getPosition().y);
        offSet = chracater1.getPosition() - myGuy.getCenter;
    }
    

    //*********** Gril *******************

    if (bFixedButtonP1 == true) {
        if (chracater2.getPosition().x < 768 && chracater2.getPosition().x > max ) {
            
            myGirl.update(myGirl.getCenter.x + diffP2.x, chracater2.getPosition().y);
            
        }else if( chracater2.getPosition().x > 768-2400 && chracater2.getPosition().x < max-2400){
            
            myGirl.update(myGirl.getCenter.x + diffP2.x, chracater2.getPosition().y);
            
        }else{
            
            if(myGirl.getCenter.x <= max && myGirl.getCenter.x >=min){
                myGirl.update(myGirl.getCenter.x + diffP2.x, chracater2.getPosition().y);
            }
            
            if(myGirl.getCenter.x > max){
                myGirl.update(max, chracater2.getPosition().y);
                offSet2 = chracater2.getPosition() - myGirl.getCenter;
            }
            
            if(myGirl.getCenter.x < min){
                myGirl.update(min, chracater2.getPosition().y);
                offSet2 = chracater2.getPosition() - myGirl.getCenter;
                
                
            }
        }
    }else{
        myGirl.update(384,chracater2.getPosition().y);
        offSet2 = chracater2.getPosition() - myGirl.getCenter;
    }
    //*********** Accelerometer *******************
    ofPoint gravity = ofxAccelerometer.getForce();
    float speedP1, speedP2;
    
    ofxBox2dRect rect1;
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
    
    ofPoint ropeMeshPos;
    ofPoint ropeMeshPos2;
    beltPosP1.y = (1-beltPctP1)*myGuy.getCenter.y + beltPctP1*myGirl.getCenter.y;
    beltPosP2.y = (1-beltPctP2)*myGirl.getCenter.y + beltPctP2*myGuy.getCenter.y;
    beltPosRopeP1.y = (1-beltPctP1)*myGuy.getCenter.y;
    beltPosRopeP2.y = (1-beltPctP2)*myGirl.getCenter.y + beltPctP2*1024;
    ropeMeshPos.y = (1-beltPctP1)*myGuy.getCenter.y + beltPctP1*(myGirl.getCenter.y+myGirl.height/2-15);
    ropeMeshPos2.y = (1-beltPctP2)*myGirl.getCenter.y + beltPctP2*(myGuy.getCenter.y - myGuy.height/2 + 15);
    //*********** keys *******************
   
    

    switch (keyState1) {
        case 0:
            key1.update(keysubstitute1.getPosition());
            break;
        case 1:{
            float keyoffset1;
            
            if (myGuy.bReverse == false) {
                keyoffset1 = 25;
            }else{
                keyoffset1 = -25;
            }
            ofPoint temp;
            temp.x = chracater1.getPosition().x + keyoffset1;
            temp.y = beltPosP1.y+20;
            key1.update(temp);
            keysubstitute1.setPosition(chracater1.getPosition().x +40, beltPosP1.y);
            if (myGuy.bReverse == false) {
                key1.angle =0;
            }else{
                key1.angle =180;
            }
            
            }break;
        case 2:{
            float keyoffset1;
            if (myGirl.bReverse == false) {
                keyoffset1 = 25;
            }else{
                keyoffset1 = -25;
            }
            ofPoint temp;
            temp.x = chracater2.getPosition().x - keyoffset1;
            temp.y = beltPosP2.y-20;
            key1.update(temp);
            keysubstitute1.setPosition(chracater2.getPosition().x -40, beltPosP2.y);
            if (myGirl.bReverse == false) {
                key1.angle =180;
            }else{
                key1.angle =0;
            }
            }break;
        case 3:{
            keysubstitute1.setPosition(-100, -100);
        }break;
    }
    
    keysubstitute1.setDamping(0.98f);
    
    switch (keyState2) {
        case 0:
          
            key2.update(keysubstitute2.getPosition());
            
            break;
        case 1:{
            float keyoffset2;
            if (myGuy.bReverse == false) {
                keyoffset2 = 25;
            }else{
                keyoffset2 = -25;
            }
            
            ofPoint temp;
            temp.x = chracater1.getPosition().x + keyoffset2;
            temp.y = beltPosP1.y+20;
            key2.update(temp);
            keysubstitute2.setPosition(chracater1.getPosition().x + 40, beltPosP1.y);
            if (myGuy.bReverse == false) {
                key2.angle =180;
            }else{
                key2.angle =0;
            }
        }break;
        case 2:{
            
            float keyoffset2;
            if (myGirl.bReverse == false) {
                keyoffset2 = 25;
            }else{
                keyoffset2 = -25;
            }
            ofPoint temp;
            temp.x = chracater2.getPosition().x - keyoffset2;
            temp.y = beltPosP2.y-20;
            key2.update(temp);
            keysubstitute2.setPosition(chracater2.getPosition().x - 40, beltPosP2.y);
            if (myGirl.bReverse == false) {
                key2.angle =0;
            }else{
                key2.angle =180;
            }
        }break;
        case 3:{
            keysubstitute2.setPosition(-100, -100);
        }break;
    }
    
    keysubstitute2.setDamping(0.98f);
    
    
    //*********** passing belt *******************
    beltP1[0].set(myGuy.getCenter.x, myGuy.getCenter.y);
    beltP1[1].set(myGuy.getCenter.x, beltPosP1.y);
    
    beltP2[0].set(myGirl.getCenter.x, myGirl.getCenter.y);
    beltP2[1].set(myGirl.getCenter.x, beltPosP2.y);
    
    //*********** chests *******************
    myChest1.update(chestSub1.getPosition());
    myChest2.update(chestSub2.getPosition());
    
    //*********** rope ********************
    
    if (myChest1.open && bRope1) {
         posRope1.setInitialCondition(chestSub1.getPosition().x, chestSub1.getPosition().y, 15, -20);
         bRope1 = false;
         rope1.bFixed = false;
         rope1.bScale = true;
         pickUpRopeSound.play();
    }
    
    if (myChest2.open && bRope2) {
        posRope2.setInitialCondition(chestSub2.getPosition().x, chestSub2.getPosition().y, -15, 20);
        bRope2 = false;
        rope2.bFixed = false;
        rope2.bScale = true;
        pickUpRopeSound.play();
    }
   
    if (bRope1 == false&&bRopeIconAnimationDone1==false) {
        
        posRope1.resetForce();
        posRope1.addAttractionForce(chracater1.getPosition().x,chracater1.getPosition().y , 3000, 0.9);
        posRope1.addForce(0, 0);
        posRope1.addDampingForce();
        posRope1.update();
        rope1.pos = posRope1.pos;
        if ((rope1.pos-chracater1.getPosition()).length()<10) {
            rope1.bFixed = true;
            rope1.bScale = false;
            bRopeInUse1 = true;
            invP1.num = 4;
            myChest1.bFixed = true;
            chestSub1.body->SetActive(false);
            bRopeIconAnimationDone1 = true;
        }
    }
    
    if (bRope2 == false&&bRopeIconAnimationDone2==false) {
        
        posRope2.resetForce();
        posRope2.addAttractionForce(chracater2.getPosition().x,chracater2.getPosition().y , 3000, 0.9);
        posRope2.addForce(0, 0);
        posRope2.addDampingForce();
        posRope2.update();
        rope2.pos = posRope2.pos;
        if ((rope2.pos-chracater2.getPosition()).length()<10) {
            rope2.bFixed = true;
            rope2.bScale = false;
            bRopeInUse2 = true;
            invP2.num = 5;
            myChest2.bFixed = true;
            chestSub2.body->SetActive(false);
            bRopeIconAnimationDone2 = true;
        }
    }
    
    //*********** rope mesh ********************
    
    if (bRopeInUse1) {

        float beltDiff1 = ropeMeshPos.y - myGuy.getCenter.y;
        
        if (fabs(beltDiff1) > 10){
            int num = fabs(beltDiff1/10);
            ropeStroke1.clear();
            for (int i=0; i<num; i++) {
                ropeStroke1.addVertex(myGuy.getCenter.x, myGuy.getCenter.y - 10*i);
                useRopeSound.play();
            }
            
            
        }else{
            ropeStroke1.clear();
            for(int i=4; i>0; i--){
                ropeStroke1.addVertex(myGuy.getCenter.x, myGuy.getCenter.y+10*i);
            }
        }
    
    }
    
    if (bRopeInUse2) {
        float beltDiff2 = ropeMeshPos2.y - myGirl.getCenter.y;
        
        if (fabs(beltDiff2) > 10){
            int num = fabs(beltDiff2/10);
            ropeStroke2.clear();
            for (int i=0; i<num; i++) {
                ropeStroke2.addVertex(myGirl.getCenter.x, myGirl.getCenter.y + 10*i);
                useRopeSound.play();

            }
            
            
        }else{
            ropeStroke2.clear();
            for(int i=4; i>0; i--){
                ropeStroke2.addVertex(myGirl.getCenter.x, myGirl.getCenter.y-10*i);
            }
        }
        
    }

    //*********** get lastPos ***************
    lastPosP1 = chracater1.getPosition();
    lastPosP2 = chracater2.getPosition();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    
    ofSetColor(255, 255, 255);
    ofFill();
    bgImg.draw(0, 0);
    ofPushMatrix();
        ofTranslate(-offSet.x,0);
        bgP1.draw(1971.5-2220,2377.5-1514);
    ofPopMatrix();
    ofPushMatrix();
        ofTranslate(-offSet2.x,0);
        bgP2.draw(67-2220,587-1514);
    ofPopMatrix();
       //************** guy ******************
    
    ofPushMatrix();
        ofTranslate(-offSet.x,0);
        ofSetColor(255, 255, 255);
        ofNoFill();
        myEleP1.draw();
    ofPopMatrix();
     //************** girl ******************
    ofPushMatrix();
        ofTranslate(-offSet2.x,0);
        ofSetColor(255, 255, 255);
        ofNoFill();
        bgP2.draw(67-2220,587-1514);
        myEleP2.draw();
    ofPopMatrix();
    
    myGuy.draw();
    invP1.draw();
    myGirl.draw();
    invP2.draw();
    
    
    ofPushMatrix();
        ofTranslate(-offSet.x,0);
        ofSetColor(255, 255, 255);
        ofNoFill();
//        for (int i=0; i<polyLines1.size(); i++) {
//            polyLines1[i].draw();
//        }
        myChest1.draw();
        rope1.draw();
    ofPopMatrix();
  
        
    
//    ofFill();
//    ofSetColor(255, 255, 255,30);
//    chracater1.draw();
//    keysubstitute1.draw();
   
   
    ofPushMatrix();
        ofTranslate(-offSet2.x,0);
        ofSetColor(255, 255, 255);
        ofNoFill();
//        for (int i=0; i<polyLines2.size(); i++) {
//            polyLines2[i].draw();
//        }
        myChest2.draw();
        rope2.draw();
    ofPopMatrix();
    
    ropeMesh1.draw(ropeStroke1);
    ropeMesh2.draw(ropeStroke2);
    
    
//    ofFill();
//    ofSetColor(255, 255, 255,30);
//    chracater2.draw();
//    keysubstitute2.draw();
    //************** key *****************
    ofPoint temOffSet;
    ofPoint temOffSet2;
    if (keysubstitute1.getWorld() == worldP1.getWorld()) {
        temOffSet = offSet;
    }else{
        temOffSet = offSet2;
    };
    
    ofPushMatrix();
        ofTranslate(-temOffSet.x,0);
        key1.draw();
    ofPopMatrix();
    
    if (keysubstitute2.getWorld() == worldP1.getWorld()) {
        temOffSet2 = offSet;
    }else{
        temOffSet2 = offSet2;
    };
    
    ofPushMatrix();
        ofTranslate(-temOffSet2.x,0);
        key2.draw();
    ofPopMatrix();
    
    
    //*********buttons***********
    if (bFixedButtonP1) {
        P1L.bFixed = true;
        P1R.bFixed = true;
        P1J.bFixed = true;
        P1F.bFixed = true;
    }else{
        P1L.bFixed = false;
        P1R.bFixed = false;
        P1J.bFixed = false;
        P1F.bFixed = false;
    }
    
    if (bFixedButtonP2) {
        P2L.bFixed = true;
        P2R.bFixed = true;
        P2J.bFixed = true;
        P2F.bFixed = true;
    }else{
        P2L.bFixed = false;
        P2R.bFixed = false;
        P2J.bFixed = false;
        P2F.bFixed = false;
    }
    
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
//    ofLine(myGuy.getCenter.x,myGuy.getCenter.y, myGuy.getCenter.x, beltPosRopeP1.y);
    
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
    
    
    if (P1J.bPressed && fabs(diffP1.y)< 1){
        chracater1.setVelocity(0, -40);
        jumpSound.play();
    }
    if (P2J.bPressed && fabs(diffP2.y)< 1) {
        chracater2.setVelocity(0, 40);
        jumpSound.play();
    }
    
    //**********pick up & drop down ************************
    
    //********** key 1 ************************
    
    ofPoint length1;
    ofPoint length2;
    ofPoint length3;
    ofPoint length4;
    
    if (keysubstitute1.getWorld() == worldP1.getWorld()){
        length1 = myGuy.getCenter - key1.getCenter + offSet;
        length3 = myGirl.getCenter - key1.getCenter + offSet;
    }else{
        length1 = myGuy.getCenter - key1.getCenter + offSet2;
        length3 = myGirl.getCenter - key1.getCenter + offSet2;
    }
    
    if (keysubstitute2.getWorld() == worldP1.getWorld()){
        length2 = myGuy.getCenter - key2.getCenter + offSet;
        length4 = myGirl.getCenter - key2.getCenter + offSet;
    }else{
        length2 = myGuy.getCenter - key2.getCenter + offSet2;
        length4 = myGirl.getCenter - key2.getCenter + offSet2;
    }
   
  


    
    //****************************** open chest 1********************
    if ( P1F.bPressed && (chestSub1.getPosition()-keysubstitute2.getPosition()).length()<100 && keyState2 == 1 && myChest1.open == false) {
        
        myChest1.open = true;
        keysubstitute2.body->SetActive(false);
        key2.bfixed = true;
        keyState2 = 3;
        
    } else if (P1F.bPressed && length1.length()<100 && length2.length()<100 ) {

        if (keyState1 != 1 && keyState2 != 1) {
            
            if (length1.length() < length2.length()) {
                keyState1 = 1;
                keysubstitute1.destroy();
                keysubstitute1.setPhysics(30, 0.1, 0);
                keysubstitute1.setup(worldP1.getWorld(), chracater1.getPosition().x, chracater1.getPosition().y, key1.width/2, key1.height/2);
                keysubstitute1.body->SetActive(false);
                key1.angle = 0;
                pickUpKeySound.play();
            }else{
                keyState2 = 1;
                keysubstitute2.destroy();
                keysubstitute2.setPhysics(30, 0.1, 0);
                keysubstitute2.setup(worldP1.getWorld(), chracater1.getPosition().x, chracater1.getPosition().y, key2.width/2, key2.height/2);
                keysubstitute2.body->SetActive(false);
                key2.angle = 180;
                pickUpKeySound.play();
            }
            

        }else if(keyState1 != 1 && keyState2 == 1){
            keyState1 = 1;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP1.getWorld(), chracater1.getPosition().x, chracater1.getPosition().y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(false);
            key1.angle = 0;
            
            keyState2 = 0;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP1.getWorld(), chracater1.getPosition().x, chracater1.getPosition().y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(true);
            key2.angle = 180;
            pickUpKeySound.play();
            

        }else if(keyState1 == 1 && keyState2 != 1){
            keyState2 = 1;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP1.getWorld(), chracater1.getPosition().x, chracater1.getPosition().y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(false);
            key1.angle = 0;
            
            keyState1 = 0;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP1.getWorld(), chracater1.getPosition().x, chracater1.getPosition().y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(true);
            key2.angle = 180;
            pickUpKeySound.play();
            
        }
        
        beltPctP1 = 0;
    }else if(P1F.bPressed && length1.length()<100 && length2.length()>100 ){
        
        if (keyState1 != 1) {
            
            
            keyState1 = 1;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP1.getWorld(), chracater1.getPosition().x, chracater1.getPosition().y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(false);
            key1.angle = 0;
            pickUpKeySound.play();
        }else if(keyState1 == 1){
                        
            keyState1 = 0;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP1.getWorld(), chracater1.getPosition().x, chracater1.getPosition().y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(true);
            key1.angle = 0;
            pickUpKeySound.play();
        }
        beltPctP1 = 0;

    }else if(P1F.bPressed && length1.length()>100 && length2.length()<100 ){
        
        if (keyState2 != 1) {
            
            
            keyState2 = 1;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP1.getWorld(), chracater1.getPosition().x, chracater1.getPosition().y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(false);
            key2.angle = 180;
            pickUpKeySound.play();
            
        }else if(keyState2 == 1){
            
            keyState2 = 0;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP1.getWorld(), chracater1.getPosition().x, chracater1.getPosition().y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(true);
            key2.angle = 180;
            pickUpKeySound.play();
        }
        beltPctP1 = 0;
        
    }
    
    
    //--------------- key 2 --------------
    //****************************** open chest 2********************
    if ( P2F.bPressed && (chestSub2.getPosition()-keysubstitute1.getPosition()).length()<100 && keyState1 == 2 && myChest2.open == false) {
        
        myChest2.open = true;
        keysubstitute1.body->SetActive(false);
        key1.bfixed = true;
        keyState1 = 3;
    }else if (P2F.bPressed && length3.length()<100 && length4.length()<100 ) {
        
        if (keyState1 != 2 && keyState2 != 2) {
            
            if (length3.length() < length4.length()) {
                keyState1 = 2;
                keysubstitute1.destroy();
                keysubstitute1.setPhysics(30, 0.1, 0);
                keysubstitute1.setup(worldP2.getWorld(), chracater2.getPosition().x, chracater2.getPosition().y, key1.width/2, key1.height/2);
                keysubstitute1.body->SetActive(false);
                key1.angle = 180;
                pickUpKeySound.play();
            }else{
                keyState2 = 2;
                keysubstitute2.destroy();
                keysubstitute2.setPhysics(30, 0.1, 0);
                keysubstitute2.setup(worldP2.getWorld(), chracater2.getPosition().x, chracater2.getPosition().y, key2.width/2, key2.height/2);
                keysubstitute2.body->SetActive(false);
                key2.angle = 0;
                pickUpKeySound.play();
            }
            
        }else if(keyState1 != 2 && keyState2 == 2){
            keyState1 = 2;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP2.getWorld(), chracater2.getPosition().x, chracater2.getPosition().y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(false);
            key1.angle = 180;
            
            keyState2 = 0;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP2.getWorld(), chracater2.getPosition().x, chracater2.getPosition().y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(true);
            key2.angle = 180;
            pickUpKeySound.play();
            
        }else if(keyState1 == 2 && keyState2 != 2){
            keyState2 = 2;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP2.getWorld(), chracater2.getPosition().x, chracater2.getPosition().y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(false);
            key2.angle = 0;
            
            keyState1 = 0;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP2.getWorld(), chracater2.getPosition().x, chracater2.getPosition().y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(true);
            key1.angle = 180;
            pickUpKeySound.play();
            
        }
        
        beltPctP2 = 0;
        
    }else if(P2F.bPressed && length3.length()<100 && length4.length()>100 ){
        
        if (keyState1 != 2) {
            
            
            keyState1 = 2;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP2.getWorld(), chracater2.getPosition().x, chracater2.getPosition().y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(false);
            key1.angle = 180;
            pickUpKeySound.play();
            
        }else if(keyState1 == 2){
            
            keyState1 = 0;
            keysubstitute1.destroy();
            keysubstitute1.setPhysics(30, 0.1, 0);
            keysubstitute1.setup(worldP2.getWorld(), chracater2.getPosition().x, chracater2.getPosition().y, key1.width/2, key1.height/2);
            keysubstitute1.body->SetActive(true);
            key1.angle = 180;
            pickUpKeySound.play();
        }
        beltPctP2 = 0;
        
    }else if(P2F.bPressed && length3.length()>100 && length4.length()<100 ){
        
        if (keyState2 != 2) {
            
            
            keyState2 = 2;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP2.getWorld(), chracater2.getPosition().x, chracater2.getPosition().y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(false);
            key2.angle = 0;
            pickUpKeySound.play();
            
        }else if(keyState2 == 2){
            
            keyState2 = 0;
            keysubstitute2.destroy();
            keysubstitute2.setPhysics(30, 0.1, 0);
            keysubstitute2.setup(worldP2.getWorld(), chracater2.getPosition().x, chracater2.getPosition().y, key2.width/2, key2.height/2);
            keysubstitute2.body->SetActive(true);
            key2.angle = 0;
            pickUpKeySound.play();
        }
        beltPctP2 = 0;
        
    }
    //****************************** use rope ********************
    if(P2F.bPressed && (ropeStroke1.getClosestPoint(myGirl.getCenter)- myGirl.getCenter).length() < myGirl.height/2+20 && bRopeInUse1){
        bClimb = true;
        posClimb = chracater2.getPosition();
        cout<<"1"<<endl;
    }
    
    if(P2J.bPressed && (ropeStroke1.getClosestPoint(myGirl.getCenter)- myGirl.getCenter).length() < myGirl.height/2+20 && bRopeInUse1){
        bClimb = false;
        climbUp = 150;
        bRopeInUse1 = false;
        invP1.num = 2;
        ropeStroke1.clear();
        ropeMesh1.mesh.clear();
        cout<<"4"<<endl;
    }
    
    if(P1F.bPressed && (ropeStroke2.getClosestPoint(myGuy.getCenter)- myGuy.getCenter).length() < myGuy.height/2+20 && bRopeInUse2){
        bClimb2 = true;
        posClimb2 = chracater1.getPosition();
        cout<<"1"<<endl;
    }
    
    if(P1J.bPressed && (ropeStroke2.getClosestPoint(myGuy.getCenter)- myGuy.getCenter).length() < myGuy.height/2+20 && bRopeInUse2){
        bClimb2 = false;
        climbUp2 = -150;
        bRopeInUse2 = false;
        invP2.num = 3;
        ropeStroke2.clear();
        ropeMesh2.mesh.clear();
        cout<<"4"<<endl;
    }
    
    //****************************** use inventory ********************
    ofRectangle select1(426,943,48,44);
    ofRectangle select2(295,41,48,44);
    if (select1.inside(touch.x, touch.y)&& bRopeIconAnimationDone1 == true ) {
        bRopeInUse1 = true;
        bRopeIconAnimationDone1 = false;
        beltPctP1 = 0;
        invP1.num = 4;
    }
    
    if (select2.inside(touch.x, touch.y)&& bRopeIconAnimationDone2 == true ) {
        bRopeInUse2 = true;
        bRopeIconAnimationDone2 = false;
        beltPctP2 = 0;
        invP2.num = 5;
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

