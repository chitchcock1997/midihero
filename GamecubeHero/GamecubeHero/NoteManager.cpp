//
//  NoteManager.cpp
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/28/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#include "NoteManager.h"

void NoteManager::onInputDown(NoteTypes button) {
    //find bottom most one that isn't dead in button's lane
    Note* bottom=nullptr;
    int saved=-1;
    for(int i=0;i<notes.size();i++) {
        if(notes[i]->getType()==button) {
            //check if not dead
            if(notes[i]->getPos().y<smackCenter+SMACKSIZE) {
                if(bottom==nullptr||notes[i]->getPos().y>bottom->getPos().y) {
                    bottom=notes[i];
                    saved=i;
                }
            }
        }
    }
    if(bottom!=nullptr) {
        float s=bottom->smack(smackCenter-bottom->getPos().y);
        if(s==-1) {
            //MISS
        }
        else {
            //HIT
            //remove it from list
            notes.erase(notes.begin()+saved);
        }
    }
}
void NoteManager::onInputUp(NoteTypes button) {
    //find bottom most one that isn't dead in button's lane
    
}