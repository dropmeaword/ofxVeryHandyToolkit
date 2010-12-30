/*
 *  timestamp.cpp
 *  blinker
 *
 *  Created by zilog on 11/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "utils.h"
#include <iostream>
#include <string>

string getTimestamp() {
	stringstream s;
	//s << ofGetYear() << ofGetMonth() << ofGetDay() << ofGetHours() << ofGetMinutes() << ofGetSeconds();

	Poco::Timestamp epoch(0);
	Poco::Timestamp now;
	Poco::Timestamp::TimeDiff diffTime = (now - epoch);
	unsigned long secSince1970 = (unsigned long) (diffTime/1000);	
	
	s << (unsigned long)secSince1970;
	
	return s.str();
}

unsigned long getEpoch(string tstamp) {
	return std::atol( tstamp.c_str() );
}

void testTimestampStuff() {
	cout << "timestamp: " << getTimestamp() << endl;
	cout << "epoch: " << getEpoch( getTimestamp() ) << endl;
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
