//
//  ttLevelScene01.h
//  final02
//
//  Created by PengCheng on 5/4/13.
//
//

#ifndef __final02__ttLevelScene01__
#define __final02__ttLevelScene01__

#include "ofMain.h"
#include "ttBaseScene.h"

class ttLevelScene01 : public baseScene{
public:
    void setup(int &CurrentScene);
	void update();
	void draw();
    void drawScene(int iCameraDraw);
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    
    void contactStart_worldA(ofxBox2dContactArgs &e);
    void contactEnd_worldA(ofxBox2dContactArgs &e);
    void contactStart_worldB(ofxBox2dContactArgs &e);
    void contactEnd_worldB(ofxBox2dContactArgs &e);
    
    void position();
    

};




#endif /* defined(__final02__ttLevelScene01__) */
