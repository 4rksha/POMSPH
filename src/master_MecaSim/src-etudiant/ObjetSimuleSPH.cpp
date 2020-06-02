/*
 * ObjetSimuleSPH.cpp : definition pour la methode SPH (simulation de fluide).
 * Copyright (C) 2017 Florence Zara, LIRIS
 *               florence.zara@liris.univ-lyon1.fr
 *               http://liris.cnrs.fr/florence.zara/
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/** \file ObjetSimuleSPH.cpp
 \brief Methodes specifiques aux fluides avec methode SPH.
 */

/** Librairies **/
#include <stdio.h>
#include <vector>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>

// Fichiers de master_meca_sim
#include "Noeuds.h"
#include "ObjetSimule.h"
#include "ObjetSimuleSPH.h"
#include "Viewer.h"

#include "vec.h"
#include "draw.h"
#include "Viewer.h"

/**
 * Constructeur de la class ObjetSimuleSPH.
 */
ObjetSimuleSPH::ObjetSimuleSPH(std::string fich_param)
    : ObjetSimule(fich_param)
{

    /** Recuperation des parametres de la methode sph mis dans le fichier **/
    Param_sph(fich_param);
}

/**
 * Pour creer particules a l interieur d une boite englobant le fluide.
 */
int box_indicator(float x, float y, float z)
{
    return (x < 0.5) && (y < 0.5) && (z < 0.5);
}

/**
 * Initialisation des tableaux a partir des donnees lues dans le fichier.
 */
void ObjetSimuleSPH::initObjetSimule()
{
    /* Initialisation des etats des particules */
    float hh = h /1.4;

    float x, y, z;

    // Nombre de particules
    _Nb_Sommets = 0;

    for (x = 0; x < 1; x += hh)
    {
        for (y = 0; y < 1; y += hh)
        {
            for (z = 0; z < 1; z += hh)
            {

                // Pour un point (x,y,z) dans la region
                if (box_indicator(x, y, z))
                {
                    // Initialisation de ses donnees
                    P.push_back(Vector(x, y, z));
                    V.push_back(Vector(0.0, 0.0, 0.0));
                    Vprec.push_back(Vector(0.0, 0.0, 0.0));
                    A.push_back(Vector(0.0, 0.0, 0.0));
                    Force.push_back(Vector(0.0, 0.0, 0.0));
                    rho.push_back(0.0);
                    M.push_back(1);

                    // Compte les points qui tombent dans la région indiquee
                    ++_Nb_Sommets;
                }
            }
        }
    }

    /* Calcul de la densite */
    CalculDensite();

    /* Initialisation des masses */
    // Calcul de la densite moyenne
    // en considerant que toutes les particules ont une masse egale a 1
    float rho2s = 0;
    float rhos = 0;

    for (int i = 0; i < _Nb_Sommets; ++i)
    {
        rho2s += rho[i] * rho[i];
        rhos += rho[i];
    }

    // Puis repartition de cette densite sur les masses
    for (int i = 0; i < _Nb_Sommets; ++i)
        M[i] *= (rho0 * rhos / rho2s);

    _SolveurExpl->CalculPremierPas(_Nb_Sommets, A, V, Vprec, P);
    /** Message pour la fin de la creation du maillage **/
    std::cout << "SPH build ..." << std::endl;
}

/**
 * Creation du maillage (pour affichage) du fluide SPH.
 */
void ObjetSimuleSPH::initMeshObjet()
{
    // Rien car on utilise une sphere + translation par rapport aux positions P[i] des particules
    // Pas de Mesh a creer
}

/**
 * Mise a jour du Mesh (pour affichage) de l objet en fonction des nouvelles positions calculees.
 */
void ObjetSimuleSPH::updateVertex()
{
    // Rien car on utilise une sphere + translation par rapport aux positions P[i] des particules
    // Pas de Mesh a mettre a jour
}




/**
 * Simulation de l objet.
 */
void ObjetSimuleSPH::Simulation(Vector gravite, float viscosite, int Tps)
{
    /* Calcul des interactions entre particules */
    CalculInteraction(viscosite);
    /* Calcul des accelerations (avec ajout de la gravite aux forces) */
    //std::cout << "Accel.... " << std::endl;
    _SolveurExpl->CalculAccel_ForceGravite(gravite, _Nb_Sommets, A, Force, M);

    /* Calcul des vitesses et positions au temps t */
    //std::cout << "Vit.... " << std::endl;
    _SolveurExpl->Solve(viscosite, _Nb_Sommets, Tps, A, V, Vprec, P);

    /* Gestion des collisions  */
    // Reponse : rebond
    // Penser au Translate de l objet dans la scene pour trouver plan coherent
    Collision();

    // Affichage des positions
    // AffichagePos(Tps);
}
