//
//  baseScene.h
//  final02
//
//  Created by PengCheng on 5/4/13.
//
//

#ifndef __final02__baseScene__
#define __final02__baseScene__

#include "ofMain.h"


class baseScene {
	
    
public:
	
	virtual void setup(){};
	virtual void update(){};
	virtual void draw(){};
    
    virtual void touchDown(ofTouchEventArgs & touch){};
    virtual void touchMoved(ofTouchEventArgs & touch){};
    virtual void touchUp(ofTouchEventArgs & touch){};
    virtual void touchDoubleTap(ofTouchEventArgs & touch){};
    virtual void touchCancelled(ofTouchEventArgs & touch){};
    
    virtual void lostFocus(){};
    virtual void gotFocus(){};
    virtual void gotMemoryWarning(){};
    virtual void deviceOrientationChanged(int newOrientation){};
    
    
	
    int goToScene;
    bool end;
	
    float startTime;
    float delayTime = 2;
};

#endif /* defined(__final02__baseScene__) */
