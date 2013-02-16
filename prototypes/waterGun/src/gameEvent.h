//
//  gameEvent.h
//  waterGun
//
//  Created by PengCheng on 2/10/13.
//
//

#ifndef __waterGun__gameEvent__
#define __waterGun__gameEvent__

#include "ofMain.h"
#include "Enemy.h"
#include "Bullet.h"

class GameEvent : public ofEventArgs {
    
public:
    
    Bullet * bullet;
    Enemy    * enemy;
    string   message;
    
    GameEvent() {
        bullet = NULL;
        enemy    = NULL;
    }
    
    static ofEvent <GameEvent> events;
};
#endif /* defined(__waterGun__gameEvent__) */
