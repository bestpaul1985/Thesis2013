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
                   ttControl &ctrl_A,
                   ttControl &ctrl_B,
                   ofPoint SetPos,
                   ofPoint &Acc,
                   int iCharNum){
   
    world = characterWorld;
    control_A = &ctrl_A;
    control_B = &ctrl_B;
    accFroce = &Acc;
    setWidth = 15;
    setHeight = 30;
    step = 0;
    bFixedMove = false;
    setPos = SetPos;
    getPos = SetPos;
    charNum = iCharNum;
    bSwing = false;
    if(charNum ==1)mirrorLeft = false;
    if(charNum ==0)mirrorLeft = true;
    bDead = false;
    bDestroyRect = false;
    bHookIt = false;
    alpha = 255;
    deadStep = 2;
    hold_Num = 0;
    
    color.set(255, 255, 255, 255);
    character.setPhysics(40.f, 0.0f, 0.95f);
    character.setup(world.getWorld(), setPos.x, setPos.y, setWidth, setHeight);
    character.body->SetFixedRotation(true);
    character.body->SetLinearDamping(b2dNum(0.95));
    numFootContacts = 0;
    adjustedHeight = 85;
    ofDirectory dir;
    int nFiles;
    b2Vec2 v2;
    if (charNum == 0) {
        nFiles = dir.listDir("sprites/girl");
        v2 = screenPtToWorldPt(ofPoint(0,-30));
     
    }
    else
    {
        nFiles  = dir.listDir("sprites/boy");
        v2 = screenPtToWorldPt(ofPoint(0,30));
    }
 
    if (nFiles) {
        for (int i= 0; i<dir.numFiles(); i++) {
            string filePath = dir.getPath(i);
            sprite.push_back(ofImage());
            sprite.back().loadImage(filePath);
        }
    }
    
    b2PolygonShape shape;
    shape.SetAsBox(b2dNum(10), b2dNum(10), v2, b2dNum(0));
	b2FixtureDef fixture;
    fixture.isSensor = true;
    fixture.shape = &shape;
    b2Fixture* footSensorFixture = character.body->CreateFixture(&fixture);
    footSensorFixture->SetUserData(new ttSetData());
    ttSetData * sd = (ttSetData*)footSensorFixture->GetUserData();
    sd->name	= "footSenser";
    
    startTime = ofGetElapsedTimeMillis();
}
//----------------------------------------------
void ttChar::update(){
    
    float x =20;
    float scale = 1000;
    float smallMove;
    float smallMoveSale = 1.2;

    if (charNum == 0) {
        if (bFixedMove==true){
            control_A->bSmallLeft = false;
            control_A->bSmallRight = false;
            control_A->bLeft = false;
            control_A->bRight = false;
            
            if (bReset) {
                character.setVelocity(0, 0);
                bReset = false;
            }
        }else{
        
            bReset = true;
            
            if (control_A->diff.x>1||control_A->diff.x<-1) {
                smallMove = control_A->diff.x*smallMoveSale;
            }
            else
            {
                smallMove  = 0;
            }
            
            
            
            
            if (control_A->bLeft == true && character.getVelocity().x< 15)
            {
                character.addForce(ofVec2f(x,0), scale);
                control_A->bLeft = false;
                mirrorLeft = true;
            }
            else if(control_A->bRight == true && character.getVelocity().x> -15)
            {

                character.addForce(ofVec2f(-x,0), scale);
                control_A->bRight = false;
                mirrorLeft = false;
            }else if (control_A->bSmallLeft == true) {
                character.setVelocity(smallMove, 0);
                control_A->bSmallLeft = false;
                mirrorLeft = true;
            }
            
            else if(control_A->bSmallRight == true)
            {
                character.setVelocity(smallMove, 0);
                control_A->bSmallRight = false;
                mirrorLeft = false;
            }
        
        }
        
    }
    
    if(charNum  == 1){
        if (bFixedMove == true) {
            control_B->bSmallLeft = false;
            control_B->bSmallRight = false;
            control_B->bLeft = false;
            control_B->bRight = false;
            if (bReset) {
                character.setVelocity(0, 0);
                bReset = false;
            }
        }
        else
        {
        
            bReset = true;
            
            if (control_B->diff.x>1||control_B->diff.x<-1) {
                smallMove = control_B->diff.x*smallMoveSale;
            }else{
                smallMove  = 0;
            }
            
            
            

            if (control_B->bLeft == true && character.getVelocity().x>-15)
            {
                character.addForce(ofVec2f(-x,0), scale);
                control_B->bLeft = false;
                mirrorLeft = true;
            }
            
            else if(control_B->bRight == true && character.getVelocity().x<15)
            {
                character.addForce(ofVec2f(x,0), scale);
                control_B->bRight = false;
                mirrorLeft = false;
            }else if (control_B->bSmallLeft == true)
            {
                
                character.setVelocity(smallMove, 0);
                control_B->bSmallLeft = false;
                mirrorLeft = true;
            }
            
            else if(control_B->bSmallRight == true){
                
                character.setVelocity(smallMove, 0);
                control_B->bSmallRight = false;
                mirrorLeft = false;
            }
            
        }
        
       
    }
    
    
    if (bSwing) {
        
         swing();
    }else{
        getPos = character.getPosition();
        bHookIt = false;
    }
   
    dead();
        
    if (joints.empty()&&!rects.empty()) {
        alpha-=5;
    }
    
    if (alpha<=100) {
        destroyRect();
        alpha = 255;
        bDestroyRect = false;
    }
}

//-----------------------------------------------
void ttChar::copyRope(vector<ofxBox2dRect> Rects, vector<b2RevoluteJoint *> Joints, ofPoint screen){
   

    float rectOff = 9;
    
    for (int i=0; i<Joints.size(); i++) {
        if (joints.empty()) {
            ofxBox2dRect rect;
            ofPoint pos;
            pos = Rects[i].getPosition() - screen;
            rect.setPhysics(Rects[i].density, Rects[i].bounce, Rects[i].friction);
            rect.setup(world.getWorld(), pos.x,pos.y, Rects[i].getWidth(), Rects[i].getHeight());
            rect.body->GetFixtureList()->SetSensor(true);
//            rect.setVelocity(Rects[i].getVelocity());
            rect.setAngle(Rects[i].body->GetAngle()*DEG_TO_RAD);
            rects.push_back(rect);
            
            pos = Rects[i+1].getPosition() - screen;
            rect.setPhysics(Rects[i+1].density, Rects[i+1].bounce, Rects[i+1].friction);
            rect.setup(world.getWorld(), pos.x,pos.y, Rects[i+1].getWidth(), Rects[i+1].getHeight());
            rect.body->GetFixtureList()->SetSensor(true);
//            rect.setVelocity(Rects[i+1].getVelocity());
            rect.setAngle(Rects[i+1].getRotation()*DEG_TO_RAD);
//            rect.body->SetAngularDamping(b2dNum(0.9f));
            rects.push_back(rect);
            
            b2RevoluteJointDef revoluteJointDef;
            revoluteJointDef.Initialize(rects[i].body, rects[i+1].body, rects[0].body->GetWorldCenter());
            b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
            revoluteJointDef.localAnchorA.Set(p.x, p.y);
            p = screenPtToWorldPt(ofPoint(-rectOff,0));
            revoluteJointDef.localAnchorB.Set(p.x, p.y);
            joints.push_back((b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef));
        }else if(i<Joints.size()-1){
            ofxBox2dRect rect;
            ofPoint pos;
            pos = Rects[i+1].getPosition() - screen;
            rect.setPhysics(Rects[i+1].density, Rects[i+1].bounce, Rects[i+1].friction);
            rect.setup(world.getWorld(), pos.x,pos.y, Rects[i+1].getWidth(), Rects[i+1].getHeight());
            rect.body->GetFixtureList()->SetSensor(true);
//            rect.setVelocity(Rects[i+1].getVelocity());
            rect.setAngle(Rects[i+1].getRotation()*DEG_TO_RAD);
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
            pos = Rects[i+1].getPosition() - screen;
            rect.setPhysics(Rects[i+1].density, Rects[i+1].bounce, Rects[i+1].friction);
            rect.setup(world.getWorld(), pos.x,pos.y, Rects[i+1].getWidth(), Rects[i+1].getHeight());
            rect.body->GetFixtureList()->SetSensor(true);
//            rect.setVelocity(Rects[i+1].getVelocity());
            rect.setAngle(Rects[i+1].getRotation()*DEG_TO_RAD);
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
// 
    jointSize = joints.size();
    rectSize = rects.size();
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
    
    cout<<joints.empty()<<endl;
    
}
//-----------------------------------------------
void ttChar::destroyRect(){
    
    if (!rects.empty()) {
        for(int i =0; i<rects.size(); i++){
            world.world->DestroyBody(rects.back().body);
            rects.pop_back();
        }
        rects.clear();
    }
}
//-----------------------------------------------
void ttChar::controlRope(){
    
    int size = (fabs(rects[0].getPosition().y - getPos.y)-100)/20+2;
    
        if (!joints.empty() && rects.size()>size) {
            if (ofGetElapsedTimeMillis()-startTime>50) {
                world.getWorld()->DestroyJoint(joints.front());
                world.getWorld()->DestroyBody(rects[1].body);
                joints.erase(joints.begin());
                rects.erase(rects.begin()+1);
                
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(rects[0].body, rects[1].body, rects[0].body->GetWorldCenter());
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                p = screenPtToWorldPt(ofPoint(-9,0));
                revoluteJointDef.localAnchorB.Set(p.x, p.y);
                revoluteJointDef.enableLimit = true;
                revoluteJointDef.lowerAngle = -PI/3;
                revoluteJointDef.upperAngle = PI/3;
                joints.front() = (b2RevoluteJoint*)world.world->CreateJoint(&revoluteJointDef);
                
                startTime = ofGetElapsedTimeMillis();
            }
        }
        else
        {
                rects.back().setDensity(30.0);
        }
        
    


}
//-----------------------------------------------
void ttChar::swing(){
    
    if (bHookIt == false) {
        float dis;
        
        dis = rects.back().getPosition().y - character.getPosition().y;
        
        if (dis<0 && dis>-40) {
            bHookIt = true;
        }
        
        cout<<dis<<endl;
    }
    
    if (bHookIt) {
        character.setPosition(rects.back().getPosition().x-10,rects.back().getPosition().y+10);
    }
    
   
    if (charNum == 0) {
        if (control_B->bSwingLeft) {
            for (int i=1; i<5; i++) {
                rects[i].addForce(ofPoint(-2,0), 1);
            }
            control_B->bSwingLeft = false;
        }
        
        else if (control_B->bSwingRight) {
            for (int i=1; i<5; i++) {
                rects[i].addForce(ofPoint(2,0), 1);
            }
            control_B->bSwingRight = false;
        }
        
       
    }else{

        if (control_A->bSwingLeft) {
            for (int i=1; i<5; i++) {
                rects[i].addForce(ofPoint(2,0), 1);
            }
            
            control_A->bSwingLeft = false;
        }
        else if (control_A->bSwingRight) {
            for (int i=1; i<5; i++) {
                rects[i].addForce(ofPoint(-2,0), 1);
            }
        
            control_A->bSwingRight = false;
        }
    }
    
    
    
    if (accFroce->y>0.15 && !bAccRight) {
        
        for (int i=1; i<rects.size(); i++) {
            rects[i].addForce(ofPoint(-1,0), 1);
        }
        bAccRight = true;
    }
    
    if(accFroce->y<-0.15 && !bAccLeft){
        for (int i=1; i<rects.size(); i++) {
            rects[i].addForce(ofPoint(1,0), 1);
        }
        bAccLeft = true;
    }
    
    if (accFroce->y<0.15&&accFroce->y>-0.15) {
        bAccLeft = false;
        bAccRight = false;
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
    if (step>0) {
        start.draw();
        joint.draw();
    }
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
    //if no picture files, draw box2d rect instead
    if ((int)sprite.size() <=0 ) {
        ofSetColor(255, 30, 220,100);
        character.draw();
    }
    
    int frameIndex = 0;
    frameIndex = (int) (ofGetElapsedTimef() * 24) % sprite.size();
    
    if(character.getVelocity().lengthSquared() >  0)
    {
        sprite[frameIndex].draw (0,0, adjustedHeight, adjustedHeight);
    }
    else
    {
        sprite[16].draw(0,0, adjustedHeight, adjustedHeight);
    }
    
    ofPopMatrix();
    ofSetRectMode(OF_RECTMODE_CORNER);

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
