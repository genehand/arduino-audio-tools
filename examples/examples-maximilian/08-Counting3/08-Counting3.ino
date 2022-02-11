#include "MaximilianDSP.h"

// Define Arduino output
I2SStream out;
Maximilian maximilian(out);

// Maximilian
maxiOsc myCounter,mySwitchableOsc;//these oscillators will help us count and make sound.
int CurrentCount;//we're going to put the current count in this variable so that we can use it more easily.
double myOscOutput;//we're going to stick the output here to make it easier to mess with stuff.

void setup() {//some inits
    // setup logging
    Serial.begin(115200);
    AudioLogger::instance().begin(Serial, AudioLogger::Info);

    // setup audio output
    auto cfg = out.defaultConfig(TX_MODE);
    out.begin(cfg);
    maxiSettings::setup(cfg.sample_rate, cfg.channels, 512);
}

void play(double *output) {
	
	CurrentCount=myCounter.phasor(1, 1, 9);//phasor can take three arguments; frequency, start value and end value.

// here we use a conditional to make something happen at a specific time.	

	if (CurrentCount<5)//simple if statement
		
		myOscOutput=mySwitchableOsc.square(CurrentCount*100);
	
	else if (CurrentCount>=5)//and the 'else' bit.
		
		myOscOutput=mySwitchableOsc.sinewave(CurrentCount*50);//one osc object can produce whichever waveform you want. 
	
    output[0]=myOscOutput;
    output[1]=output[0];

}

// Arduino loop
void loop() {
    maximilian.loop();
}