//
//  ttEmoji.cpp
//  final03
//
//  Created by PengCheng on 5/3/13.
//
//

#include "ttEmoji.h"
//---------------------------------------------
void ttEmoji::setup(){
    renderer =  new ofxSpriteSheetRenderer(1, 10000, 0, 85);
    renderer->loadTexture("sprites/emoji_all.png", 2040, GL_NEAREST);

    for (int i=0; i<5; i++) {
        emoji_Sprite * newSprite = new emoji_Sprite ();
        newSprite->pos.set(0,0);
        if       (i==0)     newSprite->animation = EMOJI_LOVE;
        else if  (i==1)     newSprite->animation = EMOJI_HAPPY;
        else if  (i==2)     newSprite->animation = EMOJI_LAUGHING;
        else if  (i==3)     newSprite->animation = EMOJI_SURPRISE;
        else if  (i==4)     newSprite->animation = EMOJI_ANGRY;
        sprites[i]=newSprite;
    }
    condition = E_NONE;
};

//---------------------------------------------
void ttEmoji::update(){
     renderer->clear();
    switch (condition) {
        case E_NONE:{
        
            
        
        }break;
        case E_LOVE:{
            
            
            
        }break;
        case E_HAPPY:{
            
            
            
        }break;
        case E_SURPRISE:{
            
            
            
        }break;
        case E_ANGRY:{
            
            
            
        }break;
    }
    
};

//---------------------------------------------
void ttEmoji::draw(){

};