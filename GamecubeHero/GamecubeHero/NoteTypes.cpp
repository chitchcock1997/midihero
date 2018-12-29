//
//  NoteTypes.cpp
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/29/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#include "NoteTypes.h"

std::array<std::string, COUNT> NamedNotes::buttonNames={
    "L2\t\t",
    "L1\t\t",
    "LEFT\t",
    "UP\t\t",
    "DOWN\t",
    "RIGHT\t",
    "SQUARE\t",
    "TRIANGLE",
    "X\t\t",
    "CIRCLE\t",
    "R1\t\t",
    "R2\t\t"
};
std::string NamedNotes::toString(NoteTypes button) {
    return buttonNames[button];
}