//
//  NoteManager.h
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/28/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#ifndef __GamecubeHero__NoteManager__
#define __GamecubeHero__NoteManager__

#include <iostream>
#include <vector>
#include "Note.h"

class NoteManager {
    std::vector<Note*> notes;
    float smackCenter;
public:
    NoteManager(float smackCenter):smackCenter(smackCenter) { }
    void addNote(Note* note) { notes.push_back(note); }
    void update(sf::Time delta) {
        for(int i=0;i<notes.size();i++) {
            notes[i]->update(delta);
            if(notes[i]->getPos().y>700.f) {
                notes.erase(notes.begin()+i);
                i--;
            }
        }
    }
    void draw(sf::RenderTarget& window) {
        for(int i=0;i<notes.size();i++) {
            notes[i]->draw(window);
        }
    }
    ~NoteManager() {
        for(int i=0;i<notes.size();i++) {
            delete notes[i];
        }
    }
    Note* getFirst() { if(notes.size()>0) { return notes[0]; } else { return nullptr; } }
    void onInputDown(NoteTypes button);
    void onInputUp(NoteTypes button);
};

#endif /* defined(__GamecubeHero__NoteManager__) */
