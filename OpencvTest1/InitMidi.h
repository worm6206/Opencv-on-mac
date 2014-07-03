//
//  InitMidi.h
//  OpencvTest1
//
//  Created by Kevin Yen on 6/29/14.
//  Copyright (c) 2014 Kevin Yen. All rights reserved.
//

#include "RtMidi.h"
#include <iostream>
#include <sstream>
#include <unistd.h>

std::vector<unsigned char> midiMessage;
std::vector<unsigned char> message;
RtMidiOut *midiout = new RtMidiOut();

void Chord(int a){
    midiMessage.push_back( 144 );
    midiMessage.push_back( a );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    midiMessage.clear();
    }
void clear(){
    int t =12;
    while(t<25){
    midiMessage.push_back( 128 );
    midiMessage.push_back( t );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    midiMessage.clear();
    t++;
    }
}
