// ==========================================================================
// Copyright(c)'2001 by Apache Team
// Author: Thierry Gautier
// $Id: Properties.cpp,v 1.1.1.1 2005/02/03 17:06:14 zara Exp $
// ==========================================================================
/**
* \file Properties.cpp
* \brief Permet la lecture des donnees mises dans le fichier d execution.
*/

#include "Properties.h"
#include <iostream>
#include <sstream>
#include <ctype.h>


// ---------------------------------------------------------------------------
//
// Skip any caracters until the end of the line
//
inline std::istream& skip_line(std::istream& s_in)
{
  char c =' ';
  while ( s_in.get(c) )
#ifdef macintosh
    if (c == '\r') break;
#else
    if (c == '\n') break;
#endif
  return s_in;
}

// ---------------------------------------------------------------------------
//
// lower case all caracters of a string
//
std::string lower( const std::string& s )
{
  std::string tmp = s;
  for (int i=tmp.size(); --i >=0;)
    tmp[i] = (char)::tolower(s[i]);
  return tmp;
}


// ---------------------------------------------------------------------------
//
//
Properties::Properties() 
{}


// ---------------------------------------------------------------------------
//
//
Properties::~Properties()
{}


// ---------------------------------------------------------------------------
//
//
void Properties::load(const std::string &fileName)
{
  std::ifstream file;
  file.open( fileName.c_str(), std::ios::in );

  std::string key;
  std::string value;
  while( !file.eof() )
  {
    key = "";

    // - read a line ? read what ?
    file >> std::ws;
    std::getline(file, key, '=');
    if (key == "") continue;
    
    // - skip comment
    if ((key[0] == '#') || (key[0] == '!') 
      || ((key[0] == '/') && (key[1] =='/')))
         file >> skip_line;
    else {
      file >> std::ws; 
      std::getline(file, value, ';');

      size_t ipos = key.find(' ',0); // -get before ' '
      if (ipos != std::string::npos) key = key.substr(0,ipos);

      // assignement
      (*this)[lower(key)] = lower(value);
    }
  }
  file.close();
}

// ---------------------------------------------------------------------------
//
//
void Properties::store(
  const std::string& filename, 
  const std::string& header) const
{
  std::ofstream file;
  file.open( filename.c_str(), std::ios::out );
  file << "# " << header << std::endl;
  print( file );
  file.close();
}

// ---------------------------------------------------------------------------
//
//
void Properties::print( std::ostream& cout ) const
{
  std::map<std::string,std::string>::const_iterator curr = _map.begin(); 
  std::map<std::string,std::string>::const_iterator end = _map.end(); 
  while (curr != end) {
    if ( (*curr).second != "") 
      cout << (*curr).first << "=" << (*curr).second << ';' << std::endl;
    ++curr;
  }
}


// ---------------------------------------------------------------------------
//
//
std::string&  Properties::operator[]( const std::string& key)
{
  return _map[key];
}

const std::string&  Properties::operator[]( const std::string& key) const
{
  // not a operator[](...) const  on map ???
  return ((std::map<std::string,std::string>&)_map)[key];
}

