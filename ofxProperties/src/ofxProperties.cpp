// Java-Style Properties in C++
//
// based on code by Paul D. Senzee http://senzee.blogspot.com
#include "ofxProperties.h"

#include <sstream>
#include <fstream>
//#include <exception>
#include <stdexcept>

bool a2bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

ofxProperties::ofxProperties() 
{
}

void ofxProperties::load(string filename)
{
	read(filename.c_str(), this->properties);
}

void ofxProperties::save(string filename)
{
	write(filename.c_str(), this->properties);
}
		
string ofxProperties::getProperty( string prop )
{
	string retval;

	if( !properties.empty() ) {
		retval = this->properties[ prop ];
	} else {
		retval.clear();
	}
	
	return retval;
}

int ofxProperties::getPropertyAsInteger( string prop )
{
	return atoi( getProperty(prop).c_str() );
}

float ofxProperties::getPropertyAsFloat( string prop )
{
	return atof( getProperty(prop).c_str() );
}

bool ofxProperties::getPropertyAsBoolean( string prop )
{
	return a2bool( getProperty(prop).c_str() ); 
}


void ofxProperties::read(const char *filename, PropertyMapT &map)
{
	string fname = ofToDataPath(filename);
	
	std::ifstream file( fname.c_str() );
	if (!file) {
		stringstream ss;
		ss << "properties file " << filename << " was not found!" << endl;
		ofLog(OF_LOG_WARNING, ss.str());
	}
	read(file, map);
	file.close();
}

void ofxProperties::read(std::istream &is, PropertyMapT &map)
{
    if (!is) {
			stringstream ss;
			ss << "unable to process properties file, stream read failed" << endl;
			ofLog(OF_LOG_WARNING, ss.str());
    }
		
    char ch = 0, next = 0;

    ch = is.get();

    while (!is.eof())
    {
        switch (ch)
        {
        case '#' :
        case '!' : 
            do ch = is.get();
            while (!is.eof() && ch >= 0 && ch != '\n' && ch != '\r');               
            continue;
        case '\n':
        case '\r':
        case ' ' :
        case '\t': ch = is.get(); continue;
        }

        // Read the key
        std::ostringstream key, val;

        while (!is.eof() && ch >= 0 && ch != '=' && ch != ':' &&
               ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r')
        {
            key << ch;
            ch = is.get();
        }

        while (!is.eof() && (ch == ' ' || ch == '\t'))
            ch = is.get();

        if (!is.eof() && (ch == '=' || ch == ':'))
            ch = is.get();

        while (!is.eof() && (ch == ' ' || ch == '\t'))
            ch = is.get();

        // Read the value
        while (!is.eof() && ch >= 0 && ch != '\n' && ch != '\r')
        {
            int next = 0;
            if (ch == '\\')
            {
                ch = is.get();
                switch (ch)
                {
                case '\r':
                    ch = is.get();
                    if (ch != '\n' && ch != ' ' && ch != '\t')
                        continue;
                    // fall through
                case '\n':
                    ch = is.get();
                    while (!is.eof() && (ch == ' ' || ch == '\t')) { is >> ch; }
                    continue;
                case 't': ch = '\t'; next = is.get(); break;
                case 'n': ch = '\n'; next = is.get(); break;
                case 'r': ch = '\r'; next = is.get(); break;
                case 'u':
                    {
                        ch = is.get();
                        while (!is.eof() && ch == 'u') { is >> ch; }
                        int d = 0;
                    loop:
                        for (int i = 0 ; !is.eof() && i < 4 ; i++)
                        {
                            next = is.get();
                            switch (ch)
                            {
                            case '0': case '1': case '2': case '3': case '4':
                            case '5': case '6': case '7': case '8': case '9':           d = (d << 4) +      ch - '0'; break;
                            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': d = (d << 4) + 10 + ch - 'a'; break;
                            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': d = (d << 4) + 10 + ch - 'A'; break;
                            default:                                                                                  goto loop;
                            }
                            ch = is.get();
                        }
                        ch = d;
                        break;
                    }
                default: next = is.get(); break;
                }
            }
            else
                next = is.get();

            val << ch;
            ch = next;
        }
        if (DEBUG)
            std::cout << "key:" << key.str() << "|value:" << val.str() << std::endl;
        map[key.str()] = val.str();
    }
}

void ofxProperties::write(const char *filename, PropertyMapT &map, const char *header)
{
    std::ofstream file(filename);
    write(file, map, header);
    file.close();
}

void ofxProperties::write(std::ostream &os, PropertyMapT &map, const char *header)
{
    if (header != NULL)
        os << '#' << header << std::endl;

    os << '#';
    os << " <date> " << std::endl;

    for (iterator it = map.begin(), end = map.end(); it != end; ++it)
    {
        const std::string &key = (*it).first,
                          &val = (*it).second;
        os << key << '=';

        bool empty = false;

        for (size_t i = 0, sz = val.size(); i < sz; i++)
        {
            char ch = val[i];

            switch (ch)
            {
            case '\\': os << '\\' << '\\'; break;
            case '\t': os << '\\' << 't';  break;
            case '\n': os << '\\' << 'n';  break;
            case '\r': os << '\\' << 'r';  break;
            default:
                if (ch < ' ' || ch >= 127 || (empty && ch == ' '))
                    os << '\\' << 'u'
                       << m_hex((ch >> 12) & 0x0f) << m_hex((ch >> 8) & 0x0f)
                       << m_hex((ch >>  4) & 0x0f) << m_hex((ch >> 0) & 0x0f);
                else
                    os << ch;
            }

            empty = false;
        }
        os << std::endl;
    }
}

void ofxProperties::print(std::ostream &os, PropertyMapT &map)
{
    iterator it = map.begin(), end = map.end();
    for (; it != end; ++it)
        os << (*it).first << "=" << (*it).second << std::endl;
}