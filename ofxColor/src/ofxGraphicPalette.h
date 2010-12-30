/*
 *  ofxGraphicPalette.h
 *  displayVoting
 *
 *  Created by zilog on 12/27/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __OFXGRAPHICPALETTE_H__
#define __OFXGRAPHICPALETTE_H__

#include "ofMain.h"
#include "ofxColor.h"

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class ofxGraphicPalette {
private:
	unsigned int firstColor;
	
	ofImage src;
	vector<ofxColor> colors;

public:
	ofxGraphicPalette();
	
	void load(string fname, int gridsize);
	vector<ofxColor> getAllColors() { return colors; }
	unsigned int getColorCount() { return colors.size(); }
	ofxColor getColor(int idx);
	
	void rotateRight(int shift);
	void rotateLeft(int shift);
}; // class

#endif // __OFXGRAPHICPALETTE_H__