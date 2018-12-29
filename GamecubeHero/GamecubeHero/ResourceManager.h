//
//  ResourceManager.h
//  GamecubeHero
//
//  Created by Christopher Hitchcock on 12/28/18.
//  Copyright © 2018 Christopher Hitchcock. All rights reserved.
//

#ifndef __GamecubeHero__ResourceManager__
#define __GamecubeHero__ResourceManager__

#include <iostream>
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFml/Audio/SoundBuffer.hpp>

struct TextureManager {
    std::map<std::string, sf::Texture> textures;
};

struct SoundManager {
    std::map<std::string, sf::SoundBuffer> sounds;
};

class ResourceManager {
    static TextureManager tm;
    static SoundManager sm;
public:
    static sf::Texture& getTexture(std::string path) {
        auto t=tm.textures.find(path);
        if(t==tm.textures.end()) {
            tm.textures[path]=sf::Texture();
            if(!tm.textures[path].loadFromFile(path)) {
                std::cout<<"tex didn't load @ "<<path<<std::endl;
            }
            
            return getTexture(path);
        }
        else {
            return t->second;
        }
    }
    
    static sf::SoundBuffer& getSound(std::string path) {
        auto s=sm.sounds.find(path);
        if(s==sm.sounds.end()) {
            sm.sounds[path]=sf::SoundBuffer();
            sm.sounds[path].loadFromFile(path);
            return getSound(path);
        }
        else {
            return s->second;
        }
    }
};

#endif /* defined(__GamecubeHero__ResourceManager__) */
