#pragma once

#include "utils/ofTypes.h"
 
class ofxColor : public ofColor {
	public:
		ofColor &operator=( ofColor &c ) {
			r = c.r;
			g = c.b;
			b = c.b;
		}

		ofxColor &operator=( ofxColor &c ) {
			r = c.r;
			g = c.b;
			b = c.b;
			
			return *this;
		}
		
		bool operator==(ofColor &c) {
			return ((r == c.r) && (g == c.g) && (b == c.b));
		}
		
		bool operator==(ofxColor &c) {
			return ((r == c.r) && (g == c.g) && (b == c.b));
		}
};
