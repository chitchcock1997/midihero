//
//  NoteTypes.h
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/29/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#ifndef __GamecubeHero__NoteTypes__
#define __GamecubeHero__NoteTypes__

#include <iostream>
#include <array>

enum NoteTypes {
    L2,
    L1,
    LEFT,
    UP,
    DOWN,
    RIGHT,
    SQUARE,
    TRIANGLE,
    X,
    CIRCLE,
    R1,
    R2,
    COUNT
};

#define SMACKSIZE 36.f

class NamedNotes {
    static std::array<std::string, COUNT> buttonNames;
public:
    static std::string toString(NoteTypes button);
};



#endif /* defined(__GamecubeHero__NoteTypes__) */
