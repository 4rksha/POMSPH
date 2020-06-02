/** \file obj2sappe.cpp
  Conversion des fichiers .obj en fichiers pour Sappe.
*/

#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "Donnees.h"


/**
 * Conversion du fichier .obj pour Sappe.
 */
int main(int argc, char** argv)
{  

      std::cout << "Programme permettant la conversion des ficheirs .obj en fichiers de donnees pour SAPPE. Au prealable, il faut avoir separer dans deux fichiers distincts les points, et les facettes, et avoir ote via un editeur les v et f. Ce programme permet seulement de numerote les particules de 0 a n-1 et non de 1 a n comme le fait obj." << std::endl; 


  // Verification des arguments
  if (argc <2) 
    {
      std::cout << "Usage " << argv[0] << " fich_faceset " << std::endl;	
      exit(1);
    }

  // Noms des fichiers de donnees textes : fich_coord fich_faceset
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
	  // Lecture des facettes
	  fich_faceset >> faceset.fi;
	  fich_faceset >> faceset.fj;
	  fich_faceset >> faceset.fk;
	  
	  // Ecriture des valeurs
	  fich_faceset_sappe << faceset.fi - 1  << " " 
	  					 << faceset.fj - 1  << " " 
	  					 << faceset.fk - 1 << std::endl;
  }
  
  
  return 0;
  
}//main
