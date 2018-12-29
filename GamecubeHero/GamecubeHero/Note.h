//
//  Note.h
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/28/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#ifndef __GamecubeHero__Note__
#define __GamecubeHero__Note__

#include <iostream>
#include <array>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include "ResourceManager.h"
#include "ResourcePath.hpp"
#include "NoteTypes.h"

class Note {
    static std::array<std::string, NoteTypes::COUNT> noteTexPaths;
    
    sf::Sprite spr;
    sf::Vector2f pos;
    float speed;
    NoteTypes type;
    
public:
    Note(NoteTypes type, sf::Vector2f pos, float songSpeed);
    
    sf::Vector2f getPos() { return pos; }
    NoteTypes getType() { return type; }
    
    ///returns -1 on miss, otherwise returns value from 0 to 1 on how far off the hit was (0==perfect)
    virtual float smack(float distance);
    virtual void release(float distance);
    virtual void update(sf::Time delta);
    virtual void draw(sf::RenderTarget& window);
    virtual ~Note() { }
};



class LongNote:public Note {
    static std::array<std::string, NoteTypes::COUNT> noteTrailTexPaths;
    
    sf::Sprite longspr;
    sf::Time duration;
    
public:
    LongNote(NoteTypes type, sf::Vector2f pos, float songSpeed, sf::Time duration);
    virtual float smack(float distance) override;
    virtual void release(float distance) override;
    virtual void update(sf::Time delta) override;
    virtual void draw(sf::RenderTarget& window) override;
    virtual ~LongNote() { }
};

#endif /* defined(__GamecubeHero__Note__) */
