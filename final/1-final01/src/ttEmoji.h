//
//  ttEmoji.h
//  springBreak05
//
//  Created by Firm Read on 4/10/13.
//
//

#ifndef __springBreak05__ttEmoji__
#define __springBreak05__ttEmoji__

#include <iostream>
#include "ofMain.h"

class ttEmoji{
public:
    
    void setup();
    void update();
    void drawMoodbar(float x, float y, float w, float h);
    void drawCountGraph(float x, float y, float r);
    void triggerEmotion(int emotion);
    
        /*
    0 = surprised,
    1 = laugh,
    2 = love,
    3 = cry,
    4 = angry
         */
    
    int         emoScore;
    int         emotionOccur[5] = {0,1,2,-2,-1};
    int         emotionOccurCount[5];
    int         mostOccurCount;

    ofColor     currentMood[5];
    ofPoint     emotionCountPos[5];

    
};
#endif /* defined(__springBreak05__ttEmoji__) */
