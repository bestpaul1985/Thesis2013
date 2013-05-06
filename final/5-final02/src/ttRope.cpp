//
//  ttRope.cpp
//  final02
//
//  Created by PengCheng on 5/4/13.
//
//

#include "ttRope.h"

//----------------------------------------
void ttRope::setup(ofxBox2d &_world_B, ttChar &_A, ttChar &_B,ofPoint &_rope_start_B, ofPoint &hook_start_A, ofPoint &hook_end_A, ofPoint &_accFrc, int CharNum){
    A = &_A;
    B = &_B;
    charNum = CharNum;
    world_B =_world_B;
    hook_pct = 0;
    
    condition = R_NO_USE;
    condition = R_NO_USE;
    
    bSwing_left = false;
    bSwing_right = false;
    
    rope_start = &_rope_start_B;
    hook_end = &hook_end_A;
    hook_start = &hook_start_A;
    accFrc = &_accFrc;
}
//----------------------------------------
void ttRope::update(){
    //swing rope A-------------------------------
    if (condition == R_SWING) {
        if (!rope_joint.isSetup()) {
            rope_anchor.setup(world_B.getWorld(), rope_start->x, rope_start->y, 10);
            rope_joint.setup(world_B.getWorld(), rope_anchor.body, B->character.body);
//          float length = fabs(rope_start_B.y - char_B.getPos.y) - 100;
            float length = 250;
            rope_joint.setLength(length);
            rope_joint.setFrequency(0.95);
        }
//          char_B.rope_frame = ofClamp((462-rope_anchor.getPosition().distance(char_A.character.getPosition()))/5, 0, 39) ;
    }
    
    
    if (condition == R_DESTROY) {
        if (rope_joint.isSetup()) {
            rope_joint.destroy();
            world_B.getWorld()->DestroyBody(rope_anchor.body);
        }
    }
        //swing acclerometer-------------------------------
    if (accFrc->y > 0.4 && !bSwing_left) {
        if (condition == R_SWING) {
            B->character.addForce(ofPoint(-30,0), 100);
        }
        bSwing_left = true;
    }
    
    if (accFrc->y < -0.4 && !bSwing_right) {
        if (condition == R_SWING) {
            B->character.addForce(ofPoint(30,0), 100);
        }
    
        bSwing_right = true;
    }
    if (condition == R_SWING) {
        ofPoint diff =  B->character.getPosition() - rope_anchor.getPosition();
        if (charNum == 0) {
            B->angle = atan2(diff.x, diff.y);
        }else{
            B->angle = PI-atan2(diff.x, diff.y);
        }
    }else{
        B->angle = 0;
    }
    
    //reset
    if (accFrc->x<0.3 && accFrc->x>-0.3) {
        if (condition !=R_SWING && condition !=R_MINIGAME) {
            condition = R_NO_USE;
        }
     
    }
    
    if (accFrc->y<0.4 && accFrc->y>-0.4) {
        bSwing_left = false;
        bSwing_right = false;
    }

}

//----------------------------------------
void ttRope::draw_swing(ofPoint screen_B){
    if (condition == R_SWING) {
        ofPushMatrix();
        ofTranslate(screen_B);
        if (rope_joint.isSetup()) {
            ofSetColor(44,220);
//            rope_anchor.draw();
            rope_joint.draw();
        }
//        ofCircle(B->character.getPosition().x, B->character.getPosition().y, 10);
        ofPopMatrix();
    }
}


//----------------------------------------
void ttRope::draw_push(){
    if (condition == R_PUSH) {
        float offset;
        charNum==0? offset = 500:offset = -500;
        float speed = 0.1f;
        hook_pct +=speed;
        if (hook_pct > 1) hook_pct = 1;
        hook_end->x = hook_start->x;
        hook_end->y = (1-hook_pct)*hook_start->y + hook_pct*(hook_start->y+offset);
        
        ofSetColor(0,100);
        ofLine(hook_start->x,hook_start->y,hook_end->x, hook_end->y);
        ofSetColor(255,0,100);
        ofCircle(hook_end->x, hook_end->y, 10);
        }
  
}
//----------------------------------------
void ttRope::draw_minigame(ofPoint End){
    if (condition == R_MINIGAME) {
        float offset;
        charNum==0? offset = 500:offset = -500;
        ofSetColor(44,220);
        ofLine(hook_start->x, hook_start->y,End.x,End.y);
    }
    cout<<hook_end->x<<"  "<<hook_end->y<<endl;
}



