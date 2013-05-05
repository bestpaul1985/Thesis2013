//
//  ttBaseScene.h
//  final02
//
//  Created by PengCheng on 5/4/13.
//
//

#ifndef __final02__ttBaseScene__
#define __final02__ttBaseScene__

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"
#include "ttChar.h"
#include "ttSetData.h"
#include "ttControl.h"
#include "ttGround.h"
#include "ttThorn.h"
#include "ttSky.h"
#include "ttIndicator.h"
#include "ttDog.h"
#include "ttEmoji.h"
#include "ttRope.h"
#include "ttRabit.h"

class baseScene {
	
    
public:
	
	virtual void setup(){};
	virtual void update(){};
	virtual void draw(){};
    virtual void exit();
    
    virtual void drawScene(int iCameraDraw);
    
    virtual void touchDown(ofTouchEventArgs & touch);
    virtual void touchMoved(ofTouchEventArgs & touch);
    virtual void touchUp(ofTouchEventArgs & touch);
    virtual void touchDoubleTap(ofTouchEventArgs & touch);
    virtual void touchCancelled(ofTouchEventArgs & touch);
    
    virtual void contactStart_worldA(ofxBox2dContactArgs &e);
    virtual void contactEnd_worldA(ofxBox2dContactArgs &e);
    virtual void contactStart_worldB(ofxBox2dContactArgs &e);
    virtual void contactEnd_worldB(ofxBox2dContactArgs &e);
    
    virtual void lostFocus();
    virtual void gotFocus();
    virtual void gotMemoryWarning();
    virtual void deviceOrientationChanged(int newOrientation);
    virtual void position();
	
};


#endif /* defined(__final02__ttBaseScene__) */
