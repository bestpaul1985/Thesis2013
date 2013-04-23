//
//  ttChar.cpp
//  thatThey
//
//  Created by PengCheng on 3/11/13.
//
//


#include "ttChar.h"

//----------------------------------------------
void ttChar::setup(ofxBox2d &characterWorld,
                   ttControl &ctrl,
                   ofPoint SetPos,
                   ofPoint &Acc,
                   int iCharNum){
   
    world = characterWorld;
    control = &ctrl;
    accForce = &Acc;
    setWidth = 15;
    setHeight = 30;
    step = 0;
   
    setPos = SetPos;
    getPos = SetPos;
    charNum = iCharNum;
    
    if(charNum ==1)mirrorLeft = false;
    if(charNum ==0)mirrorLeft = true;
    bSwing = false;
    bDead = false;
    bDestroyRect = false;
    bInSky = false;
    alpha = 255;
    deadStep = 2;
    hold_Num = 0;
    
    color.set(255, 255, 255, 255);
    character.setPhysics(4.0f, 0.1f, 0.1);
    
    character.setup(world.getWorld(), setPos.x, setPos.y, setWidth, setHeight);
    character.body->SetLinearDamping(b2dNum(0.999));
    character.body->SetFixedRotation(true);
    numFootContacts = 0;
    adjustedHeight = 85;
    ofDirectory walkDir;
    int walknFiles;
    b2Vec2 v2;
    if (charNum == 0) {
        walknFiles = walkDir.listDir("sprites/girl");
        v2.Set(b2dNum(0), b2dNum(-30));
     
    }
    else
    {
        walknFiles  = walkDir.listDir("sprites/boy");
        v2.Set(b2dNum(0), b2dNum(30));
    }
 
    if (walknFiles) {
        for (int i= 0; i<walkDir.numFiles(); i++) {
            string filePath = walkDir.getPath(i);
            sprite.push_back(ofImage());
            sprite.back().loadImage(filePath);
        }
    }
    
    b2PolygonShape shape;
    shape.SetAsBox(b2dNum(10), b2dNum(10), v2 , b2dNum(0));
	b2FixtureDef fixture;
    fixture.isSensor = true;
    fixture.shape = &shape;
    b2Fixture* footSensorFixture = character.body->CreateFixture(&fixture);
    footSensorFixture->SetUserData(new ttSetData());
    ttSetData * sd = (ttSetData*)footSensorFixture->GetUserData();
    sd->name	= "footSenser";
    
    startTime = ofGetElapsedTimeMillis();
    
    // frame index April 22
    //            girl      boy
    //walk        0-19      52-71
    //die         20-26     0-6
    //fall        27-36     72-77
    //starthung   37-42     7-10
    //hung        43-54     11-19
    //startpull   55-70     20-38
    //pull        71-81     39-51
    
    //set sprite constants
    if (charNum == 0) {
        fOffsetWalk         = 0 ;
        fOffsetDie          = 20;
        fOffsetFall         = 27;
        fOffsetStarthung    = 37;
        fOffsetHung         = 43;
        fOffsetStartpull    = 55;
        fOffsetPull         = 71;
        
        fAmountWalk         = 19;
        fAmountDie          = 26-20;
        fAmountFall         = 36-27;
        fAmountStarthung    = 42-37;
        fAmountHung         = 54-43;
        fAmountStartpull    = 70-55;
        fAmountPull         = 81-71;
    }
    else{
        fOffsetWalk         = 52 ;
        fOffsetDie          = 0;
        fOffsetFall         = 72;
        fOffsetStarthung    = 7;
        fOffsetHung         = 11;
        fOffsetStartpull    = 20;
        fOffsetPull         = 39;
        
        fAmountWalk         = 71-52;
        fAmountDie          = 6;
        fAmountFall         = 77-72;
        fAmountStarthung    = 10-7;
        fAmountHung         = 19-11;
        fAmountStartpull    = 38-20;
        fAmountPull         = 51-39;
        
    }
}
//----------------------------------------------
void ttChar::moveLeft(){
    
    float x = 10;
    float scale = 10;
    if (character.getVelocity().x >0) {
        character.setVelocity(0, character.getVelocity().y);
    }
    character.addForce(ofPoint(-x,0), scale);
    
    if (charNum == 0) {
        mirrorLeft = false;
    }else{
        mirrorLeft = true;
    }
    
}
//----------------------------------------------
void ttChar::moveRight(){
    
    float x = 10;
    float scale = 10;
    if (character.getVelocity().x <0) {
        character.setVelocity(0, character.getVelocity().y);
    }
    character.addForce(ofPoint(x,0), scale);
    
    if (charNum == 0) {
        mirrorLeft = true;
    }else{
        mirrorLeft = false;
    }
}
//----------------------------------------------
void ttChar::update(){
   

    if (!bInSky) {
        if (character.getVelocity().x > 7) {
            character.setVelocity(7, character.getVelocity().y);
        }else if(character.getVelocity().x < -7){
            character.setVelocity(-7, character.getVelocity().y);
        }
    }else{
        if (character.getVelocity().x > 10) {
            character.setVelocity(10, character.getVelocity().y);
        }else if(character.getVelocity().x < -10){
            character.setVelocity(-10, character.getVelocity().y);
        }
    }
   

    dead();
    destroyRect();
    
    if (!bSwing) {
        getPos = character.getPosition();
    }
    
    
}

//-----------------------------------------------
void ttChar::copyRope(vector<ofxBox2dRect> _rects, vector<b2RevoluteJoint *> _joints, ofPoint screen){
   
    float rectOff = 14;
    
    for (int i=0; i<_joints.size(); i++) {
        if (joints.empty()) {
            ofxBox2dRect rect;
            ofPoint pos;
            pos = _rects[i].getPosition() - screen;
            rect.setPhysics(_rects[i].density, _rects[i].bounce, _rects[i].friction);
            rect.setup(world.getWorld(), pos.x,pos.y, _rects[i].getWidth(), _rects[i].getHeight());
            rect.body->GetFixtureList()->SetSensor(true);
            rect.body->SetType(_rects[i].body->GetType());
            rect.setVelocity(_rects[i].getVelocity());
            //            rect.setAngle(Rects[i].body->GetAngle()*DEG_TO_RAD);
            rects.push_back(rect);
            
            pos = _rects[i+1].getPosition() - screen;
            rect.setPhysics(_rects[i+1].density, _rects[i+1].bounce, _rects[i+1].friction);
            rect.setup(world.getWorld(), pos.x,pos.y, _rects[i+1].getWidth(), _rects[i+1].getHeight());
            rect.body->GetFixtureList()->SetSensor(true);
            rect.body->SetType(_rects[i+1].body->GetType());
            rect.setVelocity(_rects[i+1].getVelocity());
            //            rect.setAngle(Rects[i+1].getRotation()*DEG_TO_RAD);
            //            rect.body->SetAngularDamping(b2dNum(0.9f));
            rects.push_back(rect);
            
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.Initialize(rects[i].body, rects[i+1].body, rects[0].body->GetWorldCenter());
            b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
            revoluteJointDef.localAnchorA.Set(p.x, p.y);
            p = screenPtToWorldPt(ofPoint(-rectOff,0));
            revoluteJointDef.localAnchorB.Set(p.x, p.y);
            joints.push_back((b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef));
       
        }else if(i<_joints.size()-1){
            ofxBox2dRect rect;
            ofPoint pos;
            pos = _rects[i+1].getPosition() - screen;
            rect.setPhysics(_rects[i+1].density, _rects[i+1].bounce, _rects[i+1].friction);
            rect.setup(world.getWorld(), pos.x,pos.y, _rects[i+1].getWidth(), _rects[i+1].getHeight());
            rect.body->GetFixtureList()->SetSensor(true);
            rect.body->SetType(_rects[i+1].body->GetType());
            rect.setVelocity(_rects[i+1].getVelocity());
            //            rect.setAngle(Rects[i+1].getRotation()*DEG_TO_RAD);
            rects.push_back(rect);
            
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.Initialize(rects[i].body, rects[i+1].body, rects[0].body->GetWorldCenter());
            b2Vec2 p = screenPtToWorldPt(ofPoint(rectOff,0));
            revoluteJointDef.localAnchorA.Set(p.x, p.y);
            p = screenPtToWorldPt(ofPoint(-rectOff,0));
            revoluteJointDef.localAnchorB.Set(p.x, p.y);
            joints.push_back((b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef));
            
        }else{
            ofxBox2dRect rect;
            ofPoint pos;
            pos = _rects[i+1].getPosition() - screen;
            rect.setPhysics(_rects[i+1].density, _rects[i+1].bounce, _rects[i+1].friction);
            rect.setup(world.getWorld(), pos.x,pos.y, _rects[i+1].getWidth(), _rects[i+1].getHeight());
            rect.body->GetFixtureList()->SetSensor(true);
            rect.body->SetType(_rects[i+1].body->GetType());
            rect.setVelocity(_rects[i+1].getVelocity());
            //            rect.setAngle(Rects[i+1].getRotation()*DEG_TO_RAD);
            rects.push_back(rect);
            
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.Initialize(rects[i].body, rects[i+1].body, rects[0].body->GetWorldCenter());
            b2Vec2 p = screenPtToWorldPt(ofPoint(rectOff,0));
            revoluteJointDef.localAnchorA.Set(p.x, p.y);
            p = screenPtToWorldPt(ofPoint(0,0));
            revoluteJointDef.localAnchorB.Set(p.x, p.y);
            joints.push_back((b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef));
        }
    }
    
    //    b2RevoluteJointDef revoluteJointDef;
    //    revoluteJointDef.Initialize(rects.back().body, character.body, rects.back().body->GetWorldCenter());
    //    b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
    //    revoluteJointDef.localAnchorA.Set(p.x, p.y);
    //    p = screenPtToWorldPt(ofPoint(15,0));
    //    revoluteJointDef.localAnchorB.Set(p.x, p.y);
    //    joints.push_back((b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef));



}


//-----------------------------------------------
void ttChar::destroyRope(){
    
    if (joints.empty()) {
        return;
    }
    
    for(int i =joints.size()-1; i>=0; i--){
        world.world->DestroyJoint(joints[i]);
    }
    
    joints.clear();
    
    for(int i =0; i<rects.size(); i++){
        if (charNum == 0) {
        rects[i].setVelocity(ofRandom(-10,10),ofRandom(0,5));
        }else{
        rects[i].setVelocity(ofRandom(-10,10),ofRandom(-5,0));
        }
        
        rects[i].body->SetFixedRotation(false);
        rects[i].body->SetAngularDamping(b2dNum(0));
        rects[i].body->SetAngularVelocity(b2dNum(ofRandom(-3000,3000)));
    }

    
}
//-----------------------------------------------
void ttChar::destroyRect(){
    
    
    if (joints.empty()&&!rects.empty()) {
        alpha-=5;
    }
    
    if (alpha<=100) {
        for(int i =0; i<rects.size(); i++){
            world.world->DestroyBody(rects.back().body);
            rects.pop_back();
        }
        rects.clear();
        alpha = 255;
        bDestroyRect = false;
    }
    
   
}
//-----------------------------------------------
void ttChar::controlRope(){
    
    if (rects.empty()) {
        return;
    }
    
    int size = (fabs(rects[0].getPosition().y - getPos.y)-100)/28+2;
    if (size>15) {
        size = 15;
    }
        if (!joints.empty() && rects.size()>size) {
            int counter = 0;
            for (int i = 0 ; i<rects.size(); i++) {
                if (rects[i].body->GetType() == 0) {
                    counter ++;
                }
            }
        
            if (ofGetElapsedTimeMillis()-startTime>30) {
                world.getWorld()->DestroyJoint(joints.front());
                world.getWorld()->DestroyBody(rects[1].body);
                joints.erase(joints.begin());
                rects.erase(rects.begin()+1);
                
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(rects[0].body, rects[1].body, rects[0].body->GetWorldCenter());
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                p = screenPtToWorldPt(ofPoint(-14,0));
                revoluteJointDef.localAnchorB.Set(p.x, p.y);
//                revoluteJointDef.enableLimit = true;
//                revoluteJointDef.lowerAngle = -PI/3;
//                revoluteJointDef.upperAngle = PI/3;
                joints.front() = (b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef);
                
                if (counter>1) {
                    startTime = ofGetElapsedTimeMillis();
                }
            }
            
        }
       
//            b2PolygonShape shape;
//            b2Vec2 v2;
//            if (charNum == 0) {
//               
//                v2.Set(b2dNum(0), b2dNum(-30));
//                
//            }
//            else
//            {
//                
//                v2.Set(b2dNum(0), b2dNum(30));
//            }
//
//            shape.SetAsBox(b2dNum(15), b2dNum(30),v2, 0);
//            b2FixtureDef fixture;
//            fixture.shape = &shape;
//            rects.back().body->CreateFixture(&fixture);
           
        

}
//-----------------------------------------------
void ttChar::swing(){
   
    
    if (rects.empty()) {
        return;
    }
    
    
    if (rects.back().getPosition().distance(character.getPosition())<60) {
        
         character.setPosition(rects.back().getPosition());
 
        if (accForce->y>0.15 && !bAccRight) {
            
            for (int i=1; i<rects.size(); i++) {
                rects[i].addForce(ofPoint(-1.5,0), 1);
            }
            bAccRight = true;
        }
        
        if(accForce->y<-0.15 && !bAccLeft){
            for (int i=1; i<rects.size(); i++) {
                rects[i].addForce(ofPoint(1.5,0), 1);
            }
            bAccLeft = true;
        }
        
        if (accForce->y<0.15&&accForce->y>-0.15) {
            bAccLeft = false;
            bAccRight = false;
        }
        
        bSwing = true;
    }

}
//----------------------------------------------
void ttChar::dead(){

    if (charNum == 0) {
        if (bDead) {
            deadStep = 0;
            color.a = 200;
            bDead = false;
        }
        
        if (deadStep == 0) {
            color.a -= 5;
            if (color.a <=0) {
                color.a = 100;
                deadStep = 1;
            }
        }
        
        if(deadStep == 1){
            if (character.getPosition().x<2593) {
                character.setPosition(0, 0);
            }else if(character.getPosition().x>2593 && character.getPosition().x<4384){
                character.setPosition(2691, 41);
            }else if(character.getPosition().x>4384){
                character.setPosition(4693, -185);
            }
            
            color.a+=5;
            if (color.a>=255) {
                color.a = 255;
                deadStep = 2;
            }
        }
    }
    
    if (charNum == 1) {
        if (bDead) {
            deadStep = 0;
            color.a = 200;
            bDead = false;
        }
        
        if (deadStep == 0) {
            color.a -= 5;
            if (color.a <=0) {
                color.a = 100;
                deadStep = 1;
            }
        }
        
        if (deadStep == 1) {
            if (character.getPosition().x<2718) {
                character.setPosition(0, 0);
            }else if(character.getPosition().x>2718&&character.getPosition().x<4533){
                character.setPosition(2809, 75);
            }else if(character.getPosition().x>4533){
                character.setPosition(4860, 196);
            }
            color.a+=5;
            if (color.a>=255) {
                color.a = 255;
                deadStep = 2;
            }
        }
    }

}

//----------------------------------------------
void ttChar::drawBox2dObject(){
    ofSetColor(255, 30, 220,100);
    
    character.draw();
    //draw sensor
    ofPolyline   shape;
    const b2Transform& xf = character.body->GetTransform();
    for (b2Fixture* f = character.body->GetFixtureList(); f; f = f->GetNext())
    {
        if (f->IsSensor()) {
            
            ofSetColor(255,30,230,100);
            //            ofCircle(sensor.getPosition(),f->GetShape()->m_radius*OFX_BOX2D_SCALE);
            b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
            if(poly) {
                for(int i=0; i<poly->m_vertexCount; i++) {
                    b2Vec2 pt = b2Mul(xf, poly->m_vertices[i]);
                    shape.addVertex(worldPtToscreenPt(pt));
                }
            }
        }
        
    }
    shape.setClosed(true);
    ofPath path;
    for (int i=0; i<shape.size(); i++) {
        if(i==0)path.moveTo(shape[i]);
        else path.lineTo(shape[i]);
    }
    
    path.setColor(ofGetStyle().color);
    path.setFilled(ofGetStyle().bFill);
    path.draw();

    
}

//----------------------------------------------
void ttChar::draw(){
    ofSetColor(color);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(character.getPosition());
    //turn left flip
    if (mirrorLeft) ofScale(-1, 1);
    if (charNum == 0) ofScale(-1, -1);
    //if no picture files, draw box2d rect instead
    if ((int)sprite.size() <=0 ) {
        ofSetColor(255, 30, 220,100);
        character.draw();
    }
    
    int frameIndex = 0;
//    walkFrameIndex = (int) (ofGetElapsedTimef() * 24) % sprite.size();
    
    if (!bSwing) {
        if      (character.getVelocity().x != 0 && character.getVelocity().y ==0){
            frameIndex = (int) (ofGetElapsedTimef() * 24) % fAmountWalk;
            sprite[fOffsetWalk+frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
            
        }else if(character.getVelocity().y != 0){
            frameIndex = (int) (ofGetElapsedTimef() * 24) % fAmountFall;
            sprite[fOffsetFall+frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
        
        }else   {
            sprite[fOffsetWalk+16].draw(0,0, adjustedHeight, adjustedHeight);
        }
    
    }else{
        frameIndex = (int) (ofGetElapsedTimef() * 12) % fAmountHung;
        sprite[fOffsetHung +frameIndex].draw(0,0, adjustedHeight, adjustedHeight);
    }
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofDrawBitmapStringHighlight(ofToString(frameIndex), -20,-20);
    
    ofPopMatrix();

}
//----------------------------------------------
void ttChar::drawRope(){

    if (!rects.empty()) {
        for (int i =0; i<rects.size(); i++) {
            ofSetColor(255, 220, 30,alpha);
            rects[i].draw();
        }
    }
}
