// ==========================================================================
// (c) projet SAPPE
// Author : F. Zara
//
// ==========================================================================

/** \file Donnees.h
    Programme parallele calculant pour chaque particule i             
    son etat au pas de temps suivant :                     
    structures de donnees generales.                                       
*/ 


#ifndef _DONNEES_H
#define _DONNEES_H


#ifdef WIN32
#include <time.h>
#include <string>
#include <fcntl.h>
#include <io.h>
#else
#include <sys/time.h>
#endif

#include <vector>


/// Pour changer facilement de la precision simple a la double pour les points flottants
typedef float Precision;


/** 
 * Coordonnees generales.
 */
class Coord
{    
 public:      

  /*! Constructeur vide */
  Coord() : x(0.0), y(0.0), z(0.0) {}

  /*! Ajout d un constructeur */
  inline Coord(Precision coord_x, 
	       Precision coord_y, 
	       Precision coord_z) : x(coord_x), y(coord_y), z(coord_z)
    {}

  /*! Surcharge de += */
  inline Coord& operator+=(const Coord& b) 
  {
    x += b.x; 
    y += b.y; 
    z += b.z;
    
    return *this;
  }
    
  /*! Surcharge de -= */
  Coord& operator-=(const Coord& b) 
  {
    x -= b.x; 
    y -= b.y; 
    z -= b.z;
    
    return *this;
  }

  /*! Surcharge de - */
  Coord operator-(const Coord& b) const
    {
      Coord tmp(*this);
    
      return tmp -= b;
    }

  /*! Calcul du min (Coord, Coord) */
  friend Coord min(const Coord& a, const Coord& b) 
    {
      return Coord( std::min(a.x, b.x), std::min(a.y, b.y),std::min(a.z, b.z));
    }

  /*! Calcul du max (Coord, Coord) */
  friend Coord max(const Coord& a, const Coord& b) 
    {
      return Coord( std::max(a.x, b.x), std::max(a.y, b.y),std::max(a.z, b.z));
    }

 public:

  /// Coordonnees en x
  Precision x; 

  /// Coordonnees en y
  Precision y; 

  /// Coordonnees en z
  Precision z; 

};


/**
 * Facette determinee par valeurs fi, fj, fk : indices des particules dans le fichier.
 */
struct Facet 
{
  int fi, fj, fk;
};


/**
 * Texture determinee par valeurs a et b.
 */
struct Texture 
{
  Precision a, b;
};


#endif
