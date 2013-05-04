//
//  ttEmoji.cpp
//  springBreak05
//
//  Created by Firm Read on 4/10/13.
//
//

#include "ttEmoji.h"
void ttEmoji::setup(ofPoint Pos, int CharNum){
    
    charNum = CharNum;
    pos = Pos;
    emoji_renderer[0] = new ofxSpriteSheetRenderer(1, 100, 0, 35);
    emoji_renderer[1] = new ofxSpriteSheetRenderer(1, 100, 0, 35);
    emoji_renderer[2] = new ofxSpriteSheetRenderer(1, 100, 0, 36);
    emoji_renderer[3] = new ofxSpriteSheetRenderer(1, 100, 0, 35);
    emoji_renderer[4] = new ofxSpriteSheetRenderer(1, 100, 0, 36);
    emoji_renderer[0]->loadTexture("sprites/emoji_love.png", 500, GL_NEAREST);
    emoji_renderer[1]->loadTexture("sprites/emoji_happy.png", 500, GL_NEAREST);
    emoji_renderer[2]->loadTexture("sprites/emoji_laughing.png", 500, GL_NEAREST);
    emoji_renderer[3]->loadTexture("sprites/emoji_supprise.png", 500, GL_NEAREST);
    emoji_renderer[4]->loadTexture("sprites/emoji_angry.png", 500, GL_NEAREST);

    emoji_Sprite * newSprite = new emoji_Sprite();
    newSprite->pos = pos;
    newSprite->animation = EMOJI_LOVE;
    sprites[0]=newSprite;
    
    emoji_Sprite * newSprite1 = new emoji_Sprite();
    newSprite1->pos = pos;
    newSprite1->animation = EMOJI_HAPPY;
    sprites[1]=newSprite;
    
    emoji_Sprite * newSprite2 = new emoji_Sprite();
    newSprite2->pos = pos;
    newSprite2->animation = EMOJI_SURPRISE;
    sprites[2]=newSprite;
    
    emoji_Sprite * newSprite3 = new emoji_Sprite();
    newSprite3->pos=pos;
    newSprite3->animation = EMOJI_LAUGHING;
    sprites[3]=newSprite;
    
    emoji_Sprite * newSprite4 = new emoji_Sprite();
    newSprite4->pos = pos;
    newSprite4->animation = EMOJI_ANGRY;
    sprites[4]=newSprite;
    
    condition = E_NONE;
    step = S_START;
    alpha = 0;
    startTime = ofGetElapsedTimeMillis();
    duration = 1000;
    speed = 1;
    moveLeft = false;
}
//-----------------------------------------
void ttEmoji::update(ofPoint Pos, bool move_left){
    pos = Pos;
    moveLeft = move_left;
    emoji_renderer[0]->clear();
    emoji_renderer[1]->clear();
    emoji_renderer[2]->clear();
    emoji_renderer[3]->clear();
    emoji_renderer[4]->clear();
    
    switch (condition) {
        case E_NONE:{
            step = S_START;
        }
            break;
        case E_LOVE:{
            
            timer();
            emoji_renderer[0]->update(ofGetElapsedTimeMillis());
            emoji_renderer[0]->addCenteredTile(&sprites[0]->animation, 0,0,-1,F_NONE,1,255,255,255,alpha);
        }
            break;
        case E_HAPPY:{
            timer();
            emoji_renderer[1]->update(ofGetElapsedTimeMillis());
            emoji_renderer[1]->addCenteredTile(&sprites[1]->animation, 0,0,-1,F_NONE,1,255,255,255,alpha);
        }
            break;
        case E_SURPRISE:{
            timer();
            emoji_renderer[2]->update(ofGetElapsedTimeMillis());
            emoji_renderer[2]->addCenteredTile(&sprites[2]->animation, 0,0,-1,F_NONE,1,255,255,255,alpha);
        }
            break;
        case E_LAUGHING:{
            timer();
            emoji_renderer[3]->update(ofGetElapsedTimeMillis());
            emoji_renderer[3]->addCenteredTile(&sprites[3]->animation,0,0,-1,F_NONE,1,255,255,255,alpha);
        }
            break;
        case E_ANGRY:{
            timer();
            emoji_renderer[4]->update(ofGetElapsedTimeMillis());
            emoji_renderer[4]->addCenteredTile(&sprites[4]->animation, 0,0,-1,F_NONE,1,255,255,255,alpha);
        }
            break;
    }
}
//-----------------------------------------
void ttEmoji::draw(){
    ofPoint offSet;
    if (charNum == 0) moveLeft?offSet.set(35, -30):offSet.set(-35, -30);
    else moveLeft?offSet.set(30, 40):offSet.set(-30, 40);
    pos = pos - offSet;
    
    ofPushMatrix();
    ofTranslate(pos);
    if (charNum ==0) ofScale(1, -1);
    moveLeft? ofScale(-1, 1):ofScale(1, 1);
    
    if (condition == E_LOVE)  emoji_renderer[0]->draw();
    if (condition == E_HAPPY)  emoji_renderer[1]->draw();
    if (condition == E_LAUGHING)  emoji_renderer[2]->draw();
    if (condition == E_SURPRISE)  emoji_renderer[3]->draw();
    if (condition == E_ANGRY)  emoji_renderer[4]->draw();
    
    ofPopMatrix();
}
//-----------------------------------------
void ttEmoji::timer(){

    if (step==S_START) {
        alpha+=20;
        if (alpha >255) {
            alpha = 255;
            startTime = ofGetElapsedTimeMillis();
            step = S_WAIT;
        }
    }
    
    if(step==S_WAIT){
        if (ofGetElapsedTimeMillis() - startTime > duration) {
            step = S_END;
        }
    }
    
    if(step == S_END){
        alpha-=30;
        if (alpha <0) {
            alpha = 0;
            
            condition = E_NONE;
        }
    }
}


























