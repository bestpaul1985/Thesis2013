//
//  ttEmoji.cpp
//  springBreak05
//
//  Created by Firm Read on 4/10/13.
//
//

#include "ttEmoji.h"
void ttEmoji::setup(){
    
    renderer =  new ofxSpriteSheetRenderer(1, 10000, 0, 80);
    renderer->loadTexture("sprites/emoji_all.png", 800, GL_NEAREST);
    
    for (int i=0; i<5; i++) {
        emoji_Sprite * newSprite = new emoji_Sprite ();
        newSprite->pos.set(100,100);
        if       (i==0)     newSprite->animation = EMOJI_LOVE;
        else if  (i==1)     newSprite->animation = EMOJI_HAPPY;
        else if  (i==2)     newSprite->animation = EMOJI_LAUGHING;
        else if  (i==3)     newSprite->animation = EMOJI_SURPRISE;
        else if  (i==4)     newSprite->animation = EMOJI_ANGRY;
        sprites[i]=newSprite;
    }
    
    condition = E_LOVE;
    step = S_START;
    alpha = 255;
    startTime = ofGetElapsedTimeMillis();
    duration = 1000;
    speed = 1;
}
//-----------------------------------------
void ttEmoji::update(){
    renderer->clear();
    switch (condition) {
        case E_NONE:{
            startTime = ofGetElapsedTimeMillis();
            step = S_START;
        }break;
        case E_LOVE:{
            renderer->update(ofGetElapsedTimeMillis());
            renderer->addCenteredTile(&sprites[1]->animation, sprites[1]->pos.x,sprites[1]->pos.y);
        }break;
        case E_HAPPY:{
            timer();
            renderer->update(ofGetElapsedTimeMillis());
            renderer->addCenteredTile(&sprites[2]->animation, sprites[1]->pos.x,sprites[1]->pos.y);
        }break;
        case E_SURPRISE:{
            timer();
            renderer->update(ofGetElapsedTimeMillis());
            renderer->addCenteredTile(&sprites[3]->animation, sprites[1]->pos.x,sprites[1]->pos.y);
        }break;
        case E_LAUGHING:{
            timer();
            renderer->update(ofGetElapsedTimeMillis());
            renderer->addCenteredTile(&sprites[4]->animation, sprites[1]->pos.x,sprites[1]->pos.y);
        }break;
        case E_ANGRY:{
            timer();
            renderer->update(ofGetElapsedTimeMillis());
            renderer->addCenteredTile(&sprites[5]->animation, sprites[1]->pos.x,sprites[1]->pos.y);
        }break;
    }

    
}
//-----------------------------------------
void ttEmoji::draw(){
    ofSetColor(255, alpha);
    ofCircle(100, 100, 100);
    renderer->draw();
   
}
//-----------------------------------------
void ttEmoji::timer(){

    if (step==S_START) {
        alpha+=1;
        if (alpha >255) {
            alpha = 255;
            startTime = ofGetElapsedTimeMillis();
            step = S_WAIT;
        }
    }else if(step==S_WAIT){
        if (ofGetElapsedTimeMillis() - startTime > duration) {
            step = S_END;
        }
    }else if(step == S_END){
        alpha-=1;
        if (alpha <0) {
            alpha = 0;
            condition = E_NONE;
        }
    }
    
}


























