
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "MidiFile.h"
#include "Options.h"

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "NoteManager.h"
#include "PlayableSong.h"
#include "Lanes.h"

int main(int argc, char const** argv) {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    smf::MidiFile midifile;
    
    //std::string file="alphabet_songvoice";
    std::string file="MIDIlovania";
    //std::string file="The_Eagles_-_Hotel_California";
    
    sf::Font font;
    font.loadFromFile(resourcePath()+"sansation.ttf");
    
    sf::Text text("", font, 30);
    
    if(argc==0) {
        midifile.read(std::cin);
    }
    else {
        midifile.read(resourcePath()+file+".mid");
        //midifile.read(resourcePath()+"alphabet_songvoice.mid");
    }
    midifile.doTimeAnalysis();
    midifile.linkNotePairs();
    
    //generate song from midifile
    PlayableSong song(midifile, resourcePath()+file+".ogg");
    Lanes lanes;
    float songSpeed=250.f;
    float smackZoneY=500.f;
    
    srand(unsigned(time(NULL)));
    
    sf::Texture& backgroundTex=ResourceManager::getTexture(resourcePath()+"gradient"+std::to_string((int)rand()%6)+".png");
    sf::Sprite background;
    background.setTexture(backgroundTex);
    background.setScale(window.getSize().x/(float)backgroundTex.getSize().x,
                        window.getSize().y/(float)backgroundTex.getSize().y);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    NoteManager noteManager(smackZoneY-SMACKSIZE);
    for(int i=0;i<10;i++) {
        //Note note = note_to_type(Song.notes[i].note));
        //noteManager.addNote(note);
        //noteManager.addNote(new Note(static_cast<NoteTypes>(rand()%NoteTypes::COUNT), sf::Vector2f(rand()%800, 0), 12));
    }
    //noteManager.addNote(new Note(NoteTypes::X, sf::Vector2f(45, 0), songSpeed));
    
    sf::RectangleShape smackZone;
    smackZone.setSize(sf::Vector2f(window.getSize().x, SMACKSIZE));
    smackZone.setOrigin(0, smackZone.getSize().y/2.f);
    smackZone.setFillColor(sf::Color(127, 127, 127, 127));
    smackZone.setPosition(0, smackZoneY);
    
    sf::Clock clock;
    sf::Time prev;
    sf::Time curr=clock.getElapsedTime();
    
    sf::Time noteSpawnDelay=sf::seconds(5.f);
    sf::Time startTime=curr;
    sf::Time playMusicTime=noteSpawnDelay-sf::seconds(0.25f)+song.getFirstSpawn().spawnTime;//add songoffset to noteSpawnDelay
    //sf::Time playMusicTime=noteSpawnDelay;//+sf::seconds(1.33f);
    //sf::Time noteSpawnTimer=curr+noteSpawnDelay;
    bool startedPlayingSong=false;
    
    // Start the game loop
    while (window.isOpen()) {
        prev=curr;
        curr=clock.getElapsedTime();
        
        
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if(event.type==sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                noteManager.onInputDown(X);
            }
            if(event.type == sf::Event::JoystickButtonPressed) {
                switch(event.joystickButton.button) {
                    case 4:
                        noteManager.onInputDown(UP);
                        break;
                    case 5:
                        noteManager.onInputDown(RIGHT);
                        break;
                    case 6:
                        noteManager.onInputDown(DOWN);
                        break;
                    case 7:
                        noteManager.onInputDown(LEFT);
                        break;
                    case 8:
                        noteManager.onInputDown(L2);
                        break;
                    case 9:
                        noteManager.onInputDown(R2);
                        break;
                    case 10:
                        noteManager.onInputDown(L1);
                        break;
                    case 11:
                        noteManager.onInputDown(R1);
                        break;
                    case 12:
                        noteManager.onInputDown(TRIANGLE);
                        break;
                    case 13:
                        noteManager.onInputDown(CIRCLE);
                        break;
                    case 14:
                        noteManager.onInputDown(X);
                        break;
                    case 15:
                        noteManager.onInputDown(SQUARE);
                        break;
                }
            }
        }
        
        if(curr>=playMusicTime&&!startedPlayingSong) {
            song.playSong();
            startedPlayingSong=true;
        }
        
        auto spawns=song.getSpawns(curr-startTime, prev-startTime);
        for(int i=0;i<spawns.size();i++) {
            if(spawns[i].isLong) {
                //noteManager.addNote(new LongNote(spawns[i].button, sf::Vector2f(lanes.getXPosFromType(spawns[i].button), smackZoneY-(curr-spawns[i].spawnTime+noteSpawnDelay).asSeconds()*songSpeed), songSpeed, spawns[i].duration));
                noteManager.addNote(new Note(spawns[i].button, sf::Vector2f(lanes.getXPosFromType(spawns[i].button), smackZoneY-(curr-spawns[i].spawnTime+noteSpawnDelay).asSeconds()*songSpeed), songSpeed));
            }
            else {
                noteManager.addNote(new Note(spawns[i].button, sf::Vector2f(lanes.getXPosFromType(spawns[i].button), smackZoneY-(curr-spawns[i].spawnTime+noteSpawnDelay).asSeconds()*songSpeed), songSpeed));
            }
        }
        
        // Clear screen
        window.clear();
        
        noteManager.update(curr-prev);
        window.draw(background);
        window.draw(smackZone);
        
        noteManager.draw(window);
        if(noteManager.getFirst()!=nullptr) {
            text.setString(std::to_string(noteManager.getFirst()->getPos().y));
        }
        window.draw(text);
        
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
