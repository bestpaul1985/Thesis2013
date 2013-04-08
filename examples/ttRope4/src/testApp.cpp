#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    
    box2d.init();
	box2d.setGravity(0, 0);
	box2d.setFPS(60.0);
    box2d.createBounds();
	box2d.registerGrabbing();
//
//
//    ofRectangle temp;
//    temp.set(ofGetWidth()/2, 40, 1, 1);
//    start.setup(box2d.world, temp);
//   
//
//    rects.push_back(preRect);
    //enable angle limitation
    
//    revoluteJointDef.enableLimit = true;
//    revoluteJointDef.lowerAngle = -PI/8;
//    revoluteJointDef.upperAngle = PI/8;

    //add motor
    
//    revoluteJointDef.enableMotor = true;
//    revoluteJointDef.maxMotorTorque = 1000.0;
//    revoluteJointDef.motorSpeed = PI*2;
    
    enableGravity = true;
    bFall = false;
    m_num =30;
    m_preNum = 30;
    startTime = ofGetElapsedTimeMillis();
    duration = 100;
}
//--------------------------------------------------------------
void testApp::update(){
    box2d.update();
    
    if(enableGravity){
        box2d.setGravity(0, 9.8);
    }else{
        box2d.setGravity(0, 0);
    }
    
    if (!joints.empty()) {
        
        for (int i =0; i<rects.size(); i++) {
            if (i<m_preNum) {
                rects[i].body->SetType(b2_staticBody);
            }else{
                rects[i].body->SetType(b2_dynamicBody);
            }
        }
        
        cout<<rects.size()<<"  "<<m_preNum<<endl;
    }
    
    
    if (ofGetElapsedTimeMillis()-startTime>duration && bFall) {
        if (m_preNum>1) {
            m_preNum--;
        }
        startTime = ofGetElapsedTimeMillis();
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(30);
//    start.draw();
    ofSetColor(255, 30, 220);

        for (int i =0; i<rects.size(); i++) {
            rects[i].draw();
        }
    
    ofSetColor(30, 255, 220);
//    end.draw();
//    cout<<joints.empty()<<endl;
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
//    joints.push_back(joint);

    if (key=='s'){
        
        
        for(int i =0; i<m_num; i++){
            
            if (joints.empty()) {
                ofxBox2dRect rect;
                
                rect.setup(box2d.getWorld(), ofGetWidth()/2,150, 1,1);
                rect.body->GetFixtureList()->SetSensor(true);
                rects.push_back(rect);
                
                rect.setPhysics(1.0f, 0.0f, 0.2f);
                rect.setup(box2d.world, rects[0].getPosition().x+9, rects[0].getPosition().y, 10, 2);
                rect.body->GetFixtureList()->SetSensor(true);
                rects.push_back(rect);
            
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(rects[0].body, rects.back().body, rects[0].body->GetWorldCenter());
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,0));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                p = screenPtToWorldPt(ofPoint(-9,0));
                revoluteJointDef.localAnchorB.Set(p.x, p.y);
                revoluteJointDef.enableLimit = true;
                revoluteJointDef.lowerAngle = -180*DEG_TO_RAD;
                revoluteJointDef.upperAngle = 180*DEG_TO_RAD;
                joints.push_back((b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef));
                
            }else if(i<m_num-1){
                
                ofxBox2dRect rect;
                rect.setPhysics(1.0f, 0.0f, 0.2f);
                rect.setup(box2d.world, rects.back().getPosition().x, rects.back().getPosition().y, 10, 2);
                rect.body->GetFixtureList()->SetSensor(true);
                rects.push_back(rect);
                
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(rects[rects.size()-2].body, rects.back().body, rects.back().body->GetWorldCenter());
                b2Vec2 p;
                if(i%2==1){
                    p = screenPtToWorldPt(ofPoint(9,0));
                }
                else{
                    p = screenPtToWorldPt(ofPoint(-9,0));
                }
                
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                revoluteJointDef.localAnchorB.Set(p.x, p.y);
                joints.push_back((b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef));
                
            }else{
                ofxBox2dRect rect;
                rect.setPhysics(30.0f, 0.0f, 0.2f);
                rect.setup(box2d.world, rects.back().getPosition().x, rects.back().getPosition().y, 8, 8);
                rect.body->GetFixtureList()->SetSensor(true);
                rect.body->SetFixedRotation(true);
                rects.push_back(rect);

                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(rects[rects.size()-2].body, rects.back().body, rects[rects.size()-2].body->GetWorldCenter());
                b2Vec2 p1;
                b2Vec2 p2;
                if(i%2==1){
                p1 = screenPtToWorldPt(ofPoint(9,0));
                p2 = screenPtToWorldPt(ofPoint(0,0));
                }
                else{
                p1 = screenPtToWorldPt(ofPoint(-9,0));
                p2 = screenPtToWorldPt(ofPoint(0,0));
                }

                revoluteJointDef.localAnchorA.Set(p1.x, p1.y);
                revoluteJointDef.localAnchorB.Set(p2.x, p2.y);
                joints.push_back((b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef));
            }
        }
    }
    
    if (key=='d') {

        
        for(int i =0; i<m_num; i++){
            
            if (joints.size()>1)
            {
                
                box2d.world->DestroyJoint(joints.front());
                box2d.world->DestroyBody(rects[1].body);
                joints.erase(joints.begin());
                rects.erase(rects.begin()+1);
                
                ofPoint pos = rects.front().getPosition();
                rects.front().setPosition(pos.x, pos.y-20);
                b2RevoluteJointDef revoluteJointDef;
                revoluteJointDef.Initialize(rects[0].body, rects[1].body, rects[0].body->GetWorldCenter());
                
                b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
                revoluteJointDef.localAnchorA.Set(p.x, p.y);
                revoluteJointDef.localAnchorB.Set(p.x, -p.y);
                joints.front() = (b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef);
                
            }
            else if(joints.size()==1)
            {
                box2d.world->DestroyJoint(joints.back());
                box2d.world->DestroyBody(rects.back().body);
                joints.clear();
                rects.clear();
            }
        }
        
        m_preNum = m_num;
       
    }

    if (key=='g') {
        
        enableGravity = !enableGravity;
    
    }
    
    if (key=='=') {
        if (m_preNum<31) {
            m_preNum++;
        }
    }
    
    if (key=='-') {
        if (m_preNum>1) {
            m_preNum--;
        }
    }
    
    if (key=='a') {
        bFall = !bFall;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
   
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}