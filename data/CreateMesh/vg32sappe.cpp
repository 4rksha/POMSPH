/** \file vg32sappe.cpp
  Conversion des fichiers .vg3 en fichiers pour Sappe.
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
      std::cout << "Usage " << argv[0] << " fich_coord  " << " fich_faceset " << std::endl;	
      exit(1);
    }

  // Noms des fichiers de donnees textes : fich_coord fich_faceset
  std::string n_fich_coord = argv[1];
  std::string n_fich_faceset = argv[2];
	
  // Lecture des fichiers textes
  std::ifstream fich_coord(n_fich_coord.c_str()) ;
  std::ifstream fich_faceset(n_fich_faceset.c_str()) ;

  // Noms des fichiers de donnees converties : fich_coord_sappe  fich_faceset_sappe
  std::string n_fich_coord_sappe = n_fich_coord + "_sappe";
  std::string n_fich_faceset_sappe = n_fich_faceset + "_sappe";

  // Ecriture des fichiers pour Sappe
  std::ofstream fich_coord_sappe(n_fich_coord_sappe.c_str()) ;
  std::ofstream fich_faceset_sappe(n_fich_faceset_sappe.c_str()) ;

  /** Ouverture des fichiers de donnees **/  
  /* Fichier des points */
  if ((fich_coord.eof()) || (! fich_coord)) 
    {
      std::cout << "Erreur d ouverture du fichier de donnees des points " << n_fich_coord << std::endl;
      exit(1);
    }
  
  /* Fichier des facettes */
  if ((fich_faceset.eof()) || (! fich_faceset)) 
  {
      std::cout << "Erreur d ouverture du fichier de donnees des facettes " << n_fich_faceset << std::endl;
      exit(1);
  }
  
  /** Positions des particules **/
  /* Nombre de particules */
  int nbparticules;
  Precision tmp;
  Coord coord;
  
  /* Récupération du nombre de particules */
  fich_coord >> nbparticules;
  
  /* Ecriture du nom de particules dans le fichier */
  fich_coord_sappe << nbparticules << std::endl;

  /* Positions des particules */
  for(int i=0; i<nbparticules; ++i)
    {
      // Lecture des valeurs 
	  fich_coord >> tmp; // (valeur à supprimer)
      fich_coord >> coord.x;
      fich_coord >> coord.y;
      fich_coord >> coord.z;
	  fich_coord >> tmp; // (valeur à supprimer)
	  
	  // Ecriture des valeurs (supprime la première et la dernière valeurs de chacune des lignes)
      fich_coord_sappe << coord.x << " " ;
      fich_coord_sappe << coord.y << " ";
      fich_coord_sappe << coord.z << std::endl;
	  
    }//for_i
  
  
  /** Facettes **/
  Facet tmp2;
  int tmp3;
  
  /* Parcours du fichier des facettes */
  while (!fich_faceset.eof())
  {
	  // Lecture des valeurs
	  fich_faceset >> tmp3; // (valeur à supprimer) 
	  
	  // Lecture des facettes
	  fich_faceset >> tmp2.fi;
	  fich_faceset >> tmp2.fj;
	  fich_faceset >> tmp2.fk;
	  
	  // Ecriture des valeurs
	  fich_faceset_sappe << tmp2.fi << " " << tmp2.fj << " " << tmp2.fk << std::endl;
  }
  
  
  return 0;
  
}//main
