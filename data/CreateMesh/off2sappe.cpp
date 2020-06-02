/** \file off2sappe.cpp
  Conversion des fichiers .off en fichiers pour Sappe.
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
  if (argc <1) 
    {
      std::cout << "Usage " << argv[0] << " fich_faceset " << std::endl;	
      exit(1);
    }

  // Noms des fichiers de donnees textes : fich_faceset
  std::string n_fich_faceset = argv[1];
	
  // Lecture des fichiers textes
  std::ifstream fich_faceset(n_fich_faceset.c_str()) ;

  // Noms des fichiers de donnees converties : fich_coord_sappe  fich_faceset_sappe
  std::string n_fich_faceset_sappe = n_fich_faceset + "_sappe";

  // Ecriture des fichiers pour Sappe
  std::ofstream fich_faceset_sappe(n_fich_faceset_sappe.c_str()) ;

  /** Ouverture des fichiers de donnees **/  
  
  /* Fichier des facettes */
  if ((fich_faceset.eof()) || (! fich_faceset)) 
  {
      std::cout << "Erreur d ouverture du fichier de donnees des facettes " << n_fich_faceset << std::endl;
      exit(1);
  }
    
  
  /** Facettes **/
  Facet faceset;
  int tmp2;
  
  /* Parcours du fichier des facettes */
  while (!fich_faceset.eof())
  {
	  // Lecture des valeurs
	  fich_faceset >> tmp2; // (valeur à supprimer) 
		  
	  // Lecture des facettes
	  fich_faceset >> faceset.fi;
	  fich_faceset >> faceset.fj;
	  fich_faceset >> faceset.fk;
	  
	  // Ecriture des valeurs
	  fich_faceset_sappe << faceset.fi << " " << faceset.fj << " " << faceset.fk << std::endl;
  }
  
  
  return 0;
  
}//main
