//
//  InitMidi.h
//  OpencvTest1
//
//  Created by Kevin Yen on 6/29/14.
//  Copyright (c) 2014 Kevin Yen. All rights reserved.
//

#include "RtMidi.h"

std::vector<unsigned char> midiMessage;
std::vector<unsigned char> message;
RtMidiOut *midiout = new RtMidiOut();

void SendMidi(int tone, int velocity){
    midiout->openPort( 0 );
    midiMessage.push_back( 144 );
    midiMessage.push_back( tone );
    midiMessage.push_back( velocity );
    midiout->sendMessage( &midiMessage );
    midiMessage.clear();
}
