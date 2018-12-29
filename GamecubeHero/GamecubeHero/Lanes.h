//
//  Lanes.h
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/29/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#ifndef __GamecubeHero__Lanes__
#define __GamecubeHero__Lanes__

#include <iostream>
#include "NoteTypes.h"

class Lanes {
    
public:
    float getXPosFromType(NoteTypes type) {
        return type*56.f+64.f;
    }
};

#endif /* defined(__GamecubeHero__Lanes__) */
