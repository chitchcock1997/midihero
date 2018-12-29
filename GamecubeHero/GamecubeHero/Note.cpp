//
//  Note.cpp
//  GamecubeHero
//
//  Created by Hitch Chriscock and Alex and Aaron :) on 12/28/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#include "Note.h"
#include <cmath>

std::array<std::string, NoteTypes::COUNT> Note::noteTexPaths={
    "twoButton.png",
    "oneButton.png",
    "leftButton.png",
    "upButton.png",
    "downButton.png",
    "rightButton.png",
    "squareButton.png",
    "triangleButton.png",
    "xButton.png",
    "circleButton.png",
    "oneButton.png",
    "twoButton.png"
};

std::array<std::string, NoteTypes::COUNT> LongNote::noteTrailTexPaths={
    "numberLongNote.png",
    "numberLongNote.png",
    "dpadLongNote.png",
    "dpadLongNote.png",
    "dpadLongNote.png",
    "dpadLongNote.png",
    "squareLongNote.png",
    "triangleLongNote.png",
    "xLongNote.png",
    "circleLongNote.png",
    "numberLongNote.png",
    "numberLongNote.png"
};

Note::Note(NoteTypes type, sf::Vector2f pos, float songSpeed):type(type), pos(pos), speed(songSpeed) {
    //std::cout<<"Note "<<type<<"="<<NamedNotes::toString(type)<<", noteTexPaths[type]="<<noteTexPaths[type]<<std::endl;
    spr.setTexture(ResourceManager::getTexture(resourcePath()+noteTexPaths[type]));
    spr.setScale(0.3f, 0.3f);
    spr.setOrigin(spr.getScale().x*spr.getTexture()->getSize().x,
                  spr.getScale().y*spr.getTexture()->getSize().y);
}
float Note::smack(float distance) {
    //if touching at all, kill the note
    //if not touching, lose points, note stays there
    float noteSize=SMACKSIZE;
    std::cout<<"distance="<<distance<<std::endl;
    if(std::fabsf(distance)<noteSize) {
        //HIT!
        return std::fabsf(distance)/noteSize;
    }
    else {
        //MISS
        return -1;
    }
}
void Note::release(float distance) {
    
}
void Note::update(sf::Time delta) {
    pos.y+=delta.asSeconds()*speed;
}
void Note::draw(sf::RenderTarget& window) {
    spr.setPosition(pos);
    window.draw(spr);
}

LongNote::LongNote(NoteTypes type, sf::Vector2f pos, float songSpeed, sf::Time duration):Note(type, pos, songSpeed), duration(duration) {
    longspr.setTexture(ResourceManager::getTexture(resourcePath()+noteTrailTexPaths[type]));
    longspr.setScale(0.3f, 0.3f);
    longspr.setOrigin(longspr.getScale().x*longspr.getTexture()->getSize().x,
                      longspr.getScale().y*longspr.getTexture()->getSize().y);
}
float LongNote::smack(float distance) {
    
}
void LongNote::release(float distance) {
    
}
void LongNote::update(sf::Time delta) {
    Note::update(delta);
}
void LongNote::draw(sf::RenderTarget& window) {
    longspr.setPosition(getPos());
    longspr.setScale(1.f, duration.asSeconds()*100.f);
    window.draw(longspr);
    Note::draw(window);
}