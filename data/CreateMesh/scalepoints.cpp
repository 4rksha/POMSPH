/** \file scalepoints.cpp
  Applique un scale aux coordonnees.
*/

#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "Donnees.h"


/**
 * Conversion du fichier de points de Vincent pour Sappe.
 */
int main(int argc, char** argv)
{  
  // Verification des arguments
  if (argc <2) 
    {
      std::cout << "Usage " << argv[0] << " fich_coord  facteur" << std::endl;	
      exit(1);
    }

  // Noms des fichiers de donnees textes : fich_coord fich_faceset
  std::string n_fich_coord = argv[1];
  float facteur = atof(argv[2]);
  std::cout << facteur << std::endl; 
	
  // Lecture des fichiers textes
  std::ifstream fich_coord(n_fich_coord.c_str()) ;

  // Noms des fichiers de donnees converties : fich_coord_sappe  fich_faceset_sappe
  std::string n_fich_coord_sappe = n_fich_coord + "_sappe";

  // Ecriture des fichiers pour Sappe
  std::ofstream fich_coord_sappe(n_fich_coord_sappe.c_str()) ;

  /** Ouverture des fichiers de donnees **/  
  /* Fichier des points */
  if ((fich_coord.eof()) || (! fich_coord)) 
    {
      std::cout << "Erreur d ouverture du fichier de donnees des points " << n_fich_coord << std::endl;
      exit(1);
    }
  
  
  /** Positions des particules **/
  /* Nombre de particules */
  int nbparticules;
  Precision tmp;
  Coord coord;
  
  /* RŽcupŽration du nombre de particules */
  fich_coord >> nbparticules;
  
  /* Ecriture du nom de particules dans le fichier */
  fich_coord_sappe << nbparticules << std::endl;

  /* Positions des particules */
  for(int i=0; i<nbparticules; ++i)
    {
      // Lecture des valeurs 	
      fich_coord >> coord.x;
      fich_coord >> coord.y;
      fich_coord >> coord.z;
	  
	  // Ecriture des valeurs 
      fich_coord_sappe << coord.x / facteur  << " " ;
      fich_coord_sappe << coord.y / facteur << " ";
      fich_coord_sappe << coord.z / facteur << std::endl;
	  
    }//for_i  
  
  return 0;
  
}//main
