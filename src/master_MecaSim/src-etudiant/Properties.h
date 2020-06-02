// ==========================================================================
// Copyright(c)'1999-2000 by APACHE Team
// Author: T. Gautier
// ==========================================================================
/**
* \file Properties.h
 * \brief Permet la lecture des donnees mises dans le fichier d execution.
 */
#ifndef _SAPPE_PROPERTIES_H_
#define _SAPPE_PROPERTIES_H_

#include <fstream>
#include <string>
#include <map>



/**
* \brief Parseur des parametres mis dans le fichier de donnees.
 */
class Properties {
public:

  /// Default Constructor
  Properties();

  /// Destructor
  virtual ~Properties();

  /// Open and read the file with name 'file'
  virtual void load( const std::string& filename );

  /// Close the file
  virtual void store( const std::string& filename, 
              const std::string& header = "" ) const;

  /// Print the set of parameters for the simulation
  virtual void print( std::ostream& ) const;

  /// Return the value with 'key' or a null string if doesn't exist
  std::string& operator[]( const std::string& key);

  /// Return the value with 'key' or a null string if doesn't exist
  const std::string& operator[]( const std::string& key) const;

  //@name Iterator over the couple <key,value>
  //@{
  typedef std::map<std::string,std::string>::iterator Iterator;
  typedef std::map<std::string,std::string>::const_iterator constIterator;
    ///
  Iterator begin() { return _map.begin(); }
    ///
  Iterator end() { return _map.end(); }
    ///
  constIterator begin() const { return _map.begin(); }
    ///
  constIterator end() const { return _map.end(); }
  //@}
  
protected:  
  std::map<std::string,std::string> _map;
};


#endif // TAK_PROPERTY 
