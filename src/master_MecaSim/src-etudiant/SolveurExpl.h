//
//  SolveurExpl.h
//
//
//  Created by fzara on 15/12/2016.
//
//

#ifndef Solveur_Expl_h
#define Solveur_Expl_h


/** Librairies de base **/
#include <stdio.h>
#include <vector>
#include <string.h>
#include <fstream>

// Fichiers de gkit2light
#include "vec.h"
#include "mesh.h"

// Fichiers de master_meca_sim
#include "Noeuds.h"
#include "Properties.h"
#include "ObjetSimule.h"



/*
 * Class pour le schema d integration d'Euler semi-implicite.
 */
class SolveurExpl
{
public:
    
    /*! Constructeur */
    SolveurExpl(){}
    
    /*! Calcul des accelerations (avec ajout de la gravite aux forces) */
    void CalculAccel_ForceGravite(Vector g,
                                  int nb_som,
                                  std::vector<Vector> &A,
                                  std::vector<Vector> &Force,
                                  std::vector<float> &M);
    
    void CalculPremierPas(
               int nb_som,
               std::vector<Vector> &A,
               std::vector<Vector> &V,
               std::vector<Vector> &Vprec,
               std::vector<Vector> &P);

    
    /*! Calcul des vitesses et positions */
    void Solve(float visco,
               int nb_som,
               int Tps,
               std::vector<Vector> &A,
               std::vector<Vector> &V,
               std::vector<Vector> &Vprec,
               std::vector<Vector> &P);
    
    
    
    /// Pas de temps
    float _delta_t;
};



#endif
