//
//  ttMainMenuScene.h
//  final02
//
//  Created by PengCheng on 5/4/13.
//
//

#ifndef __final02__ttMainMenuScene__
#define __final02__ttMainMenuScene__

#include "ofMain.h"
#include "ttBaseScene.h"


class ttMainMenuScene : public baseScene {
public: 	
	void setup(int &CurrentScene);
	void update();
	void draw();
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);

    ofImage bg;
    int *currentScene
};

#endif /* defined(__final02__ttMainMenuScene__) */
