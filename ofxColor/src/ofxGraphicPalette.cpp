/*
 * Use an external graphic file containing colour samples of size "samplesize" 
 * as a configurable colour palette in openFrameworks. Include basic operation 
 * such as simple color cycling for palette rotation. 
 *
 * @author Luis Rodil-Fernandez
 * @date 12/27/2010
 */
#include "ofxGraphicPalette.h"

ofxGraphicPalette::ofxGraphicPalette() {
	firstColor = 0;
}

void ofxGraphicPalette::rotateRight(int shift) {
	firstColor += shift;
	if(firstColor >= (colors.size()) ) {
		int tmp = firstColor % colors.size();
		firstColor = tmp;
	}
}

void ofxGraphicPalette::rotateLeft(int shift) {
	firstColor -= shift;
	if(firstColor < 0) {
		int tmp = firstColor + colors.size();
		firstColor = tmp;
	}
}

ofxColor ofxGraphicPalette::getColor(int idx) {
	ofxColor retval;
	int nidx = firstColor + idx;
	if(nidx < colors.size() ) {
	  retval.r = colors[nidx].r;
	  retval.g = colors[nidx].g;
	  retval.b = colors[nidx].b;
	  retval.a = colors[nidx].a;
	} else {
		nidx = nidx % colors.size();
		retval = colors[nidx];
	  retval.r = colors[nidx].r;
	  retval.g = colors[nidx].g;
	  retval.b = colors[nidx].b;
	  retval.a = colors[nidx].g;
	} 
	
	return retval;
}

void ofxGraphicPalette::load(string fname, int samplesize) {
	src.loadImage(fname);
	
	unsigned char* data = src.getPixels();
	
	int iColorCount = src.getWidth() / samplesize;
	//colors = new ofColor[iColorCount];
	colors.clear();
		
	if( src.type == OF_IMAGE_COLOR_ALPHA ) { 
		ofLog(OF_LOG_VERBOSE, "getting palette from image with alpha channel");
	} else if( src.type == OF_IMAGE_COLOR ) {
		ofLog(OF_LOG_VERBOSE, "getting palette from RGB image");
	}

	for(int i = 0; i < iColorCount; i++) {
		ofxColor color;
		unsigned long px = ((i * samplesize) + 1) * (src.bpp / 8); 

		/*if( src.type == OF_IMAGE_COLOR_ALPHA ) { 
			color.a = data[px]; 
			color.r = data[px+1]; 
			color.g = data[px+2]; 
			color.b = data[px+3]; 
		} else if( src.type == OF_IMAGE_COLOR ) {*/
			color.r = data[px]; 
			color.g = data[px+1]; 
			color.b = data[px+2]; 
		//} // if colorspace
		
			cout << "indexing byte " << px << " for color " << i << " with value (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << endl;
		 colors.push_back( color );
	} // create color palette

}
