/*
 * Part of the ofxVeryHandyToolkit openFrameworks addon.
 * (c) 2010 Luis Rodil-Fernandez
 */
#include "ofxVeryHandyUtils.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

unsigned long getTimestampAsLong() {
	time_t t0 = time(NULL);
	return (unsigned long)t0;
}

string getTimestampAsString() {
	stringstream s;
	s << getTimestampAsLong();
	return s.str();
}

unsigned long parseTimestamp(string tstamp) {
	unsigned long retval = (unsigned long)strtoul( tstamp.c_str(), NULL, 0 ); 
	return retval;
}

void testTimestampStuff() {
	cout << "timestamp: " << getTimestampAsLong() << endl;
	cout << "parsed timestamp: " << parseTimestamp( getTimestampAsString() ) << endl;
}

string pprintBool(bool b) {
	return ((b == true) ? "true" : "false");
}

string pathCombine(const string& p1, const string& p2) {
   char sep = '/';
   string tmp = p1;

#ifdef _WIN32
  sep = '\\';
#endif

  if (p1[p1.length( )] != sep) { // Need to add a
     tmp += sep;                // path separator
     return(tmp + p2);
  }
  else
     return(p1 + p2);
}
