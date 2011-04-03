// Java-Style Properties in C++
//
// based on code by Paul D. Senzee http://senzee.blogspot.com
#ifndef _OFXPROPERTIES_H
#define _OFXPROPERTIES_H

#include "ofMain.h"

#include <map>
#include <string>
#include <iostream>

class ofxProperties
{
    enum { DEBUG = 0 };

public:

    typedef std::map<std::string, std::string> PropertyMapT;
    typedef PropertyMapT::value_type           value_type;
    typedef PropertyMapT::iterator             iterator;
		
		ofxProperties();

		void load(string filename);
		void save(string filename);
		
		string getProperty( string prop );
		int getPropertyAsInteger( string prop );
		float getPropertyAsFloat( string prop );
		bool getPropertyAsBoolean( string prop );
		
		
    static void read(const char *filename, PropertyMapT &map);
    static void read(std::istream &is, PropertyMapT &map);
    static void write(const char *filename, PropertyMapT &map, const char *header = NULL);
    static void write(std::ostream &os, PropertyMapT &map, const char *header = NULL);
    static void print(std::ostream &os, PropertyMapT &map);

private:

    static inline char m_hex(int nibble)
    {
        static const char *digits = "0123456789ABCDEF";
        return digits[nibble & 0xf];
    }
		
		PropertyMapT properties;
};

#endif  // _OFXPROPERTIES_H