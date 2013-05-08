//
//  ttChar.cpp
//  thatThey
//
//  Created by PengCheng on 3/11/13.
//
//
#include "ttChar.h"

//----------------------------------------------
void ttChar::setup(ofxBox2d &world, ofPoint SetPos,int CharNum,ofxSpriteSheetRenderer  *char_Render0,ofxSpriteSheetRenderer  *char_Render1,ofxSpriteSheetRenderer  *char_Render2){
    charNum = CharNum;
    character.setPhysics(4.0f, 0.1f, 0.1);
    character.setup(world.getWorld(), SetPos.x, SetPos.y, 15, 33);
    character.body->SetFixedRotation(true);
    b2PolygonShape shape;
    
    b2Vec2 v2;
    charNum==0? v2.Set(b2dNum(0), b2dNum(-30)):v2.Set(b2dNum(0), b2dNum(30));
    shape.SetAsBox(b2dNum(10), b2dNum(10), v2 , b2dNum(0));
	b2FixtureDef fixture;
    fixture.isSensor = true;
    fixture.shape = &shape;
    b2Fixture* footSensorFixture = character.body->CreateFixture(&fixture);
    footSensorFixture->SetUserData(new ttSetData());
    ttSetData * sd = (ttSetData*)footSensorFixture->GetUserData();
    sd->name	= "footSenser";
    
    
    
    if (charNum == 0) {
        char_render[0]= char_Render0;
        char_render[1] = char_Render1;
        Sprite * newSprite = new Sprite();
        newSprite->pos.set(0,0);
        newSprite->animation = GIRL_RUN;
        sprites[0]=newSprite;
        
        Sprite * newSprite2 = new Sprite();
        newSprite2->pos.set(0,340);
        newSprite2->animation = GIRL_PUSH_ROPE;
        sprites[1]=newSprite2;
        
        Sprite * newSprite3 = new Sprite();
        newSprite3->pos.set(0,0);
        newSprite3->animation = GIRL_HOOK_ROPE;
        sprites[2]=newSprite3;
    }
    
    if (charNum == 1) {
        char_render[0]= char_Render0;
        char_render[1] = char_Render1;
        char_render[2] = char_Render2;
        
        Sprite * newSprite = new Sprite();
        newSprite->pos.set(0,0);
        newSprite->animation = BOY_RUN;
        sprites[0]=newSprite;
        
        Sprite * newSprite2 = new Sprite();
        newSprite2->pos.set(0,-170);
        newSprite2->animation = BOY_PUSH_ROPE;
        sprites[1] =newSprite2;
        
        Sprite * newSprite3 = new Sprite();
        newSprite3->pos.set(0,0);
        newSprite3->animation = BOY_HOOK_ROPE;
        sprites[2]=newSprite3;
    }
    
    moveLeft = false;
    condition = C_STOP;
    getPos = SetPos;
    angle = 0;
    step = 0;
}

//----------------------------------------------
void ttChar::update(){
    
    ofPoint frc(0,0);
    char_render[0]->clear();
    char_render[1]->clear();
    if (charNum == 1) {
        char_render[2]->clear();
    }
    // change conditions
    switch (condition) {
        case C_STOP:{
            sprites[1]->animation.loops = 1;
            frc.x = character.getVelocity().x * -20;

            if (character.getVelocity().length()<0.5) {
                char_render[0]->update(ofGetElapsedTimeMillis());
                sprites[0]->animation.frame = 0;
                sprites[0]->animation.total_frames = 1;
                char_render[0]->addCenteredTile(&sprites[0]->animation, 0,0);
            }else{
                char_render[0]->update(ofGetElapsedTimeMillis());
                sprites[0]->animation.frame_duration = 100;
                sprites[0]->animation.frame_duration /= ofClamp(fabs(character.getVelocity().x), 1, 5);
                char_render[0]->addCenteredTile(&sprites[0]->animation, 0,0);
            }
        }break;
                
        case C_LEFT:{
            moveLeft = true;
            if ( character.getVelocity().x > -5 ) frc.x = -50;
            char_render[0]->update(ofGetElapsedTimeMillis());
           
            sprites[0]->animation.total_frames = 13;
            sprites[0]->animation.frame_duration = 120;
            sprites[0]->animation.frame_duration /= ofClamp(fabs(character.getVelocity().x), 1, 5);
            char_render[0]->addCenteredTile(&sprites[0]->animation, 0,0);
        }break;

        case C_RIGHT:{
            step = 2;
            moveLeft = false;
            if ( character.getVelocity().x < 5 ) frc.x = 50;
            char_render[0]->update(ofGetElapsedTimeMillis());
            
            sprites[0]->animation.total_frames = 13;
            sprites[0]->animation.frame_duration = 120;
            sprites[0]->animation.frame_duration /= ofClamp(fabs(character.getVelocity().x), 1, 5);
            char_render[0]->addCenteredTile(&sprites[0]->animation, 0,0);
           
        }break;
       
        case C_PUSH_ROPE:{
            frc.x = character.getVelocity().x * -30;
            char_render[1]->update(ofGetElapsedTimeMillis());

            sprites[1]->animation.total_frames = 8;
            sprites[1]->animation.frame_duration = 35;
            char_render[1]->addCenteredTile(&sprites[1]->animation,sprites[1]->pos.x,sprites[1]->pos.y);
        }break;
            
        case C_HOOK_ROPE:{
            if (charNum == 0) {
                char_render[0]->update(ofGetElapsedTimeMillis());
                sprites[2]->animation.frame_duration = 120;
                sprites[2]->animation.frame_duration /= ofClamp(fabs(character.getVelocity().x), 1, 3);
                sprites[2]->pos.set(25, 5);
                char_render[0]->addCenteredTile(&sprites[2]->animation, sprites[2]->pos.x,sprites[2]->pos.y);
            }else{
                
                char_render[2]->update(ofGetElapsedTimeMillis());
                sprites[2]->animation.frame_duration = 120;
                sprites[2]->animation.frame_duration /= ofClamp(fabs(character.getVelocity().x), 1, 3);
                sprites[2]->pos.set(-12, 0);
                char_render[2]->addCenteredTile(&sprites[2]->animation, sprites[2]->pos.x,sprites[2]->pos.y);
            }
           
            
        }break;
            
        case C_SWING_ROPE:{
            frc.x = character.getVelocity().x * -30;
            sprites[1]->animation.frame = 8;
            sprites[1]->animation.total_frames = 1;
            char_render[1]->addCenteredTile(&sprites[1]->animation,sprites[1]->pos.x,sprites[1]->pos.y);

        }break;
            
        case C_DEAD:{
            dead();
        }break;
            
        case C_MINIGAME:{
            frc.x = character.getVelocity().x * -30;
            sprites[1]->animation.frame = 8;
            sprites[1]->animation.total_frames = 1;
            char_render[1]->addCenteredTile(&sprites[1]->animation,sprites[1]->pos.x,sprites[1]->pos.y);
            
        }break;
    }
    
    //add force on char
    character.addForce(frc, 10);
    
    //update postion
    if (condition !=C_HOOK_ROPE) {
        getPos = character.getPosition();
    }
    
  
}
//----------------------------------------------
void ttChar::draw(){
//    ofSetColor(255, 100);
//    character.draw();
    
    ofPushMatrix();
    ofTranslate(character.getPosition().x, character.getPosition().y);
    
    if (charNum == 0) {
        if (moveLeft) {
            ofScale(1, 1);
            ofRotateZ(angle*RAD_TO_DEG);
        }else{
            ofScale(-1, 1);
            ofRotateZ(-angle*RAD_TO_DEG);
        }  
        
    }
    
    if (charNum == 1) {
        if (moveLeft) {
            ofScale(-1, 1);
            ofRotateZ(angle*RAD_TO_DEG);
        }else{
            ofScale(1, 1);
            ofRotateZ(-angle*RAD_TO_DEG);
        }
        
    }
    
    char_render[0]->draw();
    char_render[1]->draw();
    if (charNum == 1) {
        char_render[2] ->draw();
    }
    ofPopMatrix();
    
   
}
//-----------------------------------------------
void ttChar::dead(){
    
    
    if (charNum == 0) {
    
        
            character.setPosition(0, -200);
        
        
    }
    
    if (charNum == 1) {
    
        
            character.setPosition(0, 200);
        
        
    }
    
    condition = C_STOP;
}
