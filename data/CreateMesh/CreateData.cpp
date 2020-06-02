/** \file CreateData.cpp
    Creation des fichiers de donnees : points, masses, textures.
*/


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <stdlib.h>
#include <math.h>
#include <cmath>


using namespace std;




/* return a random number (float) between rmin to rmax included */
float frand(float rmin, float rmax)
{
    float r = static_cast<float>(rand()) / RAND_MAX;
    return rmin + r * (rmax - rmin);
}


/** Programme principale **/
int main(int argc, char ** argv)
{
  std::cout << "This program computes a rectangular mesh with fixed upper corners.\n The output consists of four files in a given directory: points, faces, texture coordinates, masses.\nFixed points have null mass." << std::endl;


  // ==================  Output directory ====================
  /* Nom du repertoire contenant les fichiers de sortie **/
  std::string nomRep;
  std::cout << "repertoire de sortie: ";
  std::cin >> nomRep;

  /* Existence du repertoire */
  std::string buf("test -d ");
  buf += nomRep;
  int directoryExists = system(buf.c_str());
  std::cerr << "directoryExists == " << directoryExists << std::endl;

  // Erreur
  if (directoryExists == -1) 
    std::cerr << "test error"<< std::endl;

  // Le repertoire n existe pas
  else if (directoryExists) 
    {
      buf = "mkdir " + nomRep;
      system( buf.c_str() );
    }
  // Le repertoire existe deja
  else 
    { 
      std::cerr << "le repertoire " << nomRep <<" existe deja, voulez-vous continuer (y/n) ?" << std::endl;
      char reponse;
      std::cin >> reponse;

      if (reponse != 'y') 
	{
	  std::cerr << "aborting" << std::endl;
	  exit(0);
	}
    }
        


  // ==================  Parameters  ====================
  int nbX, nbY, nbPart;

  double taille;

  std::cout << "nombre de points en abscisse: " ;
  std::cin >> nbX;

  std::cout << "nombre de points en ordonnee: ";
  std::cin >> nbY;

  nbPart = nbX * nbY;

  std::cout << "taille d'un element: " ;
  std::cin >> taille;

        
        
        


  // =======  Points ==========================
  // ============================================
  std::string nomPoints = nomRep + "/points.eti";
  std::ofstream fichierPoints(nomPoints.c_str());
  fichierPoints << nbPart << std::endl;

  for (int i=0;i<nbY;i++)
    for (int j=0;j<nbX;j++)
        //fichierPoints << frand(5,-5 ) << " " << frand(0, 5 )<< " " << frand(5, -5 )   << std::endl; // particules
      //fichierPoints << j*taille << " " << -i*taille << " " << 0 << std::endl; // tissu
       fichierPoints << j*taille << " " << -i*taille << " " << -0.1*sin(j*taille*25) << std::endl; //tissu
    
  fichierPoints.close();
                        

  // ======= Faces ==========================
  // ============================================
  std::string nomFaceSet;
  nomFaceSet = nomRep + "/faceset.eti";
  std::ofstream fichierFaceSet(nomFaceSet.c_str());
 
  for (int i=0; i<nbX-1;i++)
    for (int j=0;j<nbY-1; j++)
      {
	fichierFaceSet << j*nbX + i << " " << j*nbX + i + 1 << " " << (j+1)*nbX + i << std::endl;
	fichierFaceSet << j*nbX + i + 1 << " " << (j+1)*nbX + i + 1 << " " << (j+1)*nbX + i <<  std::endl;
      }

  fichierFaceSet.close();



  // ========= Texture coordinates =============
  // ============================================
  std::string nomTexCoord = nomRep + "/texcoord.eti";
  std::ofstream fichierTexCoord(nomTexCoord.c_str());

  //double tx =  1.0/(nbX-1); // tex coord step along x
  //double ty = -1.0/(nbY-1); // tex coord step along y

    double tx =  1.0/(nbX-1); // tex coord step along x
    double ty =  1.0/(nbY-1); // tex coord step along y
    
    std::cout << tx << " " << ty << std::endl;

  for (int i=0;i<nbY;i++)
    for (int j=0;j<nbX; j++)
      fichierTexCoord << j*tx << " " <<  1 - (i*ty) << std::endl;
  
  fichierTexCoord.close();




  // ======= Masses =============================
  // Null mass means fixed point 
  // ============================================
  std::string nomMasses = nomRep + "/masses.eti";
  std::ofstream fichierMasses(nomMasses.c_str());
  double elementMass;

  std::cout << "masse d'un element: " ;
  std::cin >> elementMass;
  std::cout << std::endl;

  for (int j=0;j<nbY;j++)
    for (int i=0;i<nbX;i++)
      {
	if(( i==0 && j==0) ||(j==0 && i==nbX-1 )) // fixe deux coins superieurs
	  fichierMasses << 0 << std::endl;
	else
	 fichierMasses << elementMass << std::endl;
      }
  
  fichierMasses.close();

       
  std::cout << "c'est fini !!! Bonne journee ..." << std::endl;            
        
}
