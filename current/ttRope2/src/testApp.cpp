#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    
    box2d.init();
	box2d.setGravity(0, 9.8);
//	box2d.createBounds();
	box2d.setFPS(60.0);
	box2d.registerGrabbing();


    ofRectangle temp;
    ofxBox2dRect preRect;
    temp.set(ofGetWidth()/2, 40, 10, 10);
    preRect.setup(box2d.world, temp);
    start = preRect;
//    rects.push_back(preRect);
    
    
   
   
    
//    for(int i =0; i<1; i++){
//        ofxBox2dRect rect;
//        temp.set(ofGetWidth()/2, 40+20+20*i, 1, 10);
//        rect.setPhysics(20.0f, 0.0f, 0.2f);
//        rect.setup(box2d.world, temp);
//        rects.push_back(rect);
//        
//        b2RevoluteJointDef revoluteJointDef;
//        revoluteJointDef.collideConnected = false;
//        //Initialize and setup local anchors
//        revoluteJointDef.Initialize(rects[i].body, rects[i+1].body,
//                                    rects[i].body->GetWorldCenter());
//        b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
//        revoluteJointDef.localAnchorA.Set(p.x, p.y);
//        p = screenPtToWorldPt(ofPoint(0,9));
//        revoluteJointDef.localAnchorB.Set(-p.x, -p.y);
//        
//        b2RevoluteJoint *joint = (b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef);
//        joints.push_back(joint);
//    }
    
    //enable angle limitation
    
//    revoluteJointDef.enableLimit = true;
//    revoluteJointDef.lowerAngle = -PI/8;
//    revoluteJointDef.upperAngle = PI/8;

    //add motor
    
//    revoluteJointDef.enableMotor = true;
//    revoluteJointDef.maxMotorTorque = 1000.0;
//    revoluteJointDef.motorSpeed = PI*2;
    
       
}
//--------------------------------------------------------------
void testApp::update(){
    box2d.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(30);
    start.draw();
    ofSetColor(255, 30, 220,100);
    for (int i =0; i<rects.size(); i++) {
        rects[i].draw();
    }
    ofSetColor(30, 255, 220);
   
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
   
    
    
//    joints.push_back(joint);

    
    if (joints.empty()) {
        ofxBox2dRect rect;
        rect.setPhysics(20.0f, 0.0f, 0.2f);
        rect.setup(box2d.world, start.getPosition().x, start.getPosition().y+20, 2, 10);
        rects.insert(rects.begin(), rect);
        
        b2RevoluteJointDef revoluteJointDef;
        revoluteJointDef.Initialize(start.body, rects[0].body, start.body->GetWorldCenter());
        b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
        revoluteJointDef.localAnchorA.Set(p.x, p.y);
        revoluteJointDef.localAnchorB.Set(p.x, -p.y);
        joints.insert(joints.begin(), (b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef));
        
    }else{
        box2d.world->DestroyJoint(joints.front());
        joints.erase(joints.begin());
        
        ofxBox2dRect rect;
        rect.setPhysics(20.0f, 0.0f, 0.2f);
        rect.setup(box2d.world, start.getPosition().x, start.getPosition().y+20, 2, 10);
        rects.insert(rects.begin(), rect);
        
        b2RevoluteJointDef revoluteJointDef;
        revoluteJointDef.Initialize(start.body, rects[0].body, start.body->GetWorldCenter());
        b2Vec2 p = screenPtToWorldPt(ofPoint(0,9));
        revoluteJointDef.localAnchorA.Set(p.x, p.y);
        revoluteJointDef.localAnchorB.Set(p.x, -p.y);
        joints.insert(joints.begin(), (b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef));
        
        rects[1].setPosition(start.getPosition().x, rects.back().getPosition().y+40);
        revoluteJointDef.Initialize(rects[0].body, rects[1].body, rects[0].body->GetWorldCenter());
        p = screenPtToWorldPt(ofPoint(0,9));
        revoluteJointDef.localAnchorA.Set(p.x, p.y);
        revoluteJointDef.localAnchorB.Set(p.x, -p.y);
        joints.insert(joints.end(), (b2RevoluteJoint*)box2d.world->CreateJoint(&revoluteJointDef));
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