#include "testApp.h"
static int w = 768;
static int h = 1024;
static int offset = 100;
static int pts_A[] = {0+offset,offset*2,    offset,offset,    w-offset, offset,    w-offset,offset*2};
static int nPts_A  = 4*2;

static int pts_B[] = {0+offset,h-offset*2,  offset,h-offset,    w-offset,h-offset,    w-offset,h-offset*2};
static int nPts_B  = 4*2;


//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.95f);
	//If you want a landscape oreintation 
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);
	
	ofBackground(30);
    ofEnableAlphaBlending();
    
    // setup world A
    world_A.init();
    world_A.setFPS(60);
    world_A.setGravity(0,-100);
    world_A.setIterations(1, 1);
    
    // setup world B
    world_B.init();
    world_B.setFPS(60);
    world_B.setGravity(0, 100);
    world_B.setIterations(1, 1);
    
    // register the listener so that we get the events
	ofAddListener(world_A.contactStartEvents, this, &testApp::contactStart_worldA);
	ofAddListener(world_A.contactEndEvents, this, &testApp::contactEnd_worldA);
    ofAddListener(world_B.contactStartEvents,this, &testApp::contactStart_worldB);
    ofAddListener(world_B.contactEndEvents,this, &testApp::contactStart_worldB);
    
    control_A.setup(0);
    control_B.setup(1);

    
    char_A.setup(world_A, world_B,
                 control_A.diff,
                 control_A.bSmallLeft,
                 control_A.bSmallRight,
                 control_A.bLeft,
                 control_A.bRight,
                 rope_A.bFixedMove,
                 ofPoint(384,512),
                 0);
    
    char_B.setup(world_B, world_A,
                 control_B.diff,
                 control_B.bSmallLeft,
                 control_B.bSmallRight,
                 control_B.bLeft,
                 control_B.bRight,
                 rope_B.bFixedMove,
                 ofPoint(384,512),
                 1);
 
    
    rope_A.setup(char_A.getPos,0);
    rope_B.setup(char_B.getPos,1);
    
    ropeExplorer_A.setup(world_B, rope_A, control_A);
    ropeExplorer_B.setup(world_A, rope_B, control_B);
    
    ropeJoint_A.setup(world_B,rope_A,ropeExplorer_A, control_A);
    ropeJoint_B.setup(world_A,rope_B,ropeExplorer_B,control_B);
    
    item[0].setPhysics(1, 0, 0);
    item[0].isFixed();
    item[0].setup(world_A.getWorld(), w/3, h/3, 20, 20);
    item[1].setPhysics(1, 0, 0);
    item[1].setup(world_B.getWorld(), w/3, h/3, 20, 20);
    
    for (int i=0; i<nPts_A; i+=2) {
		float xA = pts_A[i];
		float yA = pts_A[i+1];
		ground_A.addVertex(xA, yA);
	}
    
    ground_A.setPhysics(0.0 ,0.0, 0.0);
    ground_A.create(world_A.getWorld());
    ground_A.setData(new ttSetData);
    ttSetData* sd = (ttSetData*) ground_A.getData();
    sd->name = "ground_A";
    sd->bHit = false;
    sd->ID = 0;
    sd->bLast = false;
    
    for (int i=0; i<nPts_B; i+=2) {
        float xB = pts_B[i];
        float yB = pts_B[i+1];
        ground_B.addVertex(xB, yB);
    }
    ground_B.setPhysics(0.0 ,0.0, 0.0);
    ground_B.create(world_B.getWorld());
    ground_B.setData(new ttSetData);
    sd = (ttSetData*) ground_B.getData();
    sd->name = "ground_B";
    sd->bHit = false;
    sd->ID = 0;
    sd->bLast = false;
}
//--------------------------------------------------------------
void testApp::contactStart_worldA(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
               
            ttSetData  * aData = (ttSetData*)e.b->GetBody()->GetUserData();
            ttSetData  * bData = (ttSetData*)e.b->GetBody()->GetUserData();
            
            if (bData) {
                if (bData->name == "ropeExplorer_B")
                {
                    
                    bData->bHit = true;
                    ropeExplorer_A.bStop = true;
                    cout<<ropeExplorer_A.bStop<<endl;
                }
                
            }

        
    }
}
//--------------------------------------------------------------
void testApp::contactEnd_worldA(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
           
            ttSetData  * aData = (ttSetData*)e.b->GetBody()->GetUserData();
            ttSetData  * bData = (ttSetData*)e.b->GetBody()->GetUserData();
        
            if (aData) {
                bData->bHit = false;
                
            }
        
            if (bData) {
                bData->bHit = false;
                
            }
        }
    
}
//--------------------------------------------------------------
void testApp::contactStart_worldB(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
    
    }
}
//--------------------------------------------------------------
void testApp::contactEnd_worldB(ofxBox2dContactArgs &e){

}
//--------------------------------------------------------------
void testApp::update(){

    
    world_A.update();
    world_B.update();
    
    //Character
    char_A.update();
    char_B.update();
    
    rope_A.update(ofxAccelerometer.getForce(), char_A.getPos);
    rope_B.update(ofxAccelerometer.getForce(), char_B.getPos);
    
    ropeExplorer_A.update();
    ropeExplorer_B.update();
    ropeExplorer_A.swing();
    ropeExplorer_B.swing();
    
    ropeJoint_A.update();
    ropeJoint_B.update();
    ropeJoint_A.swing();
    ropeJoint_B.swing();
}

//--------------------------------------------------------------
void testApp::draw(){

    control_A.draw();
    control_B.draw();
    
    char_A.draw();
    char_B.draw();
    
//    rope_A.draw();
//    rope_B.draw();
    
    ropeExplorer_A.draw();
    ropeExplorer_B.draw();
    
    ropeJoint_A.draw();
    ropeJoint_B.draw();
    
    ofSetColor(ofColor::blueViolet);
    item[0].draw();
    item[1].draw();
    
    ofSetColor(255);
    ground_A.draw();
    ground_B.draw();
   
   

}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    control_A.touchDown(touch.x, touch.y,touch.id);
    control_B.touchDown(touch.x, touch.y,touch.id);
    

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    control_A.touchMove(touch.x, touch.y,touch.id);
    control_B.touchMove(touch.x, touch.y,touch.id);

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    control_A.touchUp(touch.x, touch.y,touch.id);
    control_B.touchUp(touch.x, touch.y,touch.id);

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

