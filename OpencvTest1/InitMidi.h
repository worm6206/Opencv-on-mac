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

void ChordMajor(int a){
    midiMessage.push_back( 144 );
    midiMessage.push_back( a );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    usleep(50000);
    midiMessage.clear();
    midiMessage.push_back( 144 );
    midiMessage.push_back( a+4 );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    usleep(50000);
    midiMessage.clear();
    midiMessage.push_back( 144 );
    midiMessage.push_back( a+7 );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    usleep(50000);
    midiMessage.push_back( 128 );
    midiMessage.push_back( a );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    midiMessage.clear();
    midiMessage.push_back( 128 );
    midiMessage.push_back( a+4 );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    midiMessage.clear();
    midiMessage.push_back( 128 );
    midiMessage.push_back( a+7 );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
}

void ChordMinor(int a){
    midiMessage.push_back( 144 );
    midiMessage.push_back( a );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    usleep(50000);
    midiMessage.clear();
    midiMessage.push_back( 144 );
    midiMessage.push_back( a+3 );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    usleep(50000);
    midiMessage.clear();
    midiMessage.push_back( 144 );
    midiMessage.push_back( a+7 );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    usleep(50000);
    midiMessage.push_back( 128 );
    midiMessage.push_back( a );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    midiMessage.clear();
    midiMessage.push_back( 128 );
    midiMessage.push_back( a+3 );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
    midiMessage.clear();
    midiMessage.push_back( 128 );
    midiMessage.push_back( a+7 );
    midiMessage.push_back( 90 );
    midiout->sendMessage( &midiMessage );
}


