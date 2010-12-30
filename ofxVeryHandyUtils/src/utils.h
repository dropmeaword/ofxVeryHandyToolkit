/*
 *  timestamp.h
 *  blinker
 *
 *  Created by zilog on 11/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "ofMain.h"

string getTimestamp();
unsigned long getEpoch(string tstamp);
void testTimestampStuff();
string pathCombine(const string& p1, const string& p2);

string pprintBool(bool b);

class Lissajous {
public: 

	float phasex, phasey, phasez;

  Lissajous() {
    phasex = 1;
    phasey = 3;
    phasez = 2;
  }

  Lissajous(int a, int b, int c) {
    phasex = a;
    phasey = b;
    phasez = c;
  }

  float x(float step) {
    float X = 300 * sin(phasex * step * TWO_PI);
    return X;
  }

  float y(float step) {
    float Y = 160 * sin(phasey * step * TWO_PI + PI/2);
    return Y;
  }

  float z(float step) {
    float Z = 300 * sin(phasez * step * TWO_PI);
    return Z;
  }
};
