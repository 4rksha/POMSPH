/*
 * ObjetSimule.cpp : definition des objets anime.
 * Copyright (C) 2016 Florence Zara, LIRIS
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

/** \file ObjetSimule.cpp
 \brief Methodes communes aux objets a simuler.
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
#include "Viewer.h"

#include "vec.h"
#include "draw.h"
#include "Viewer.h"



/**
 * Constructeur de la class ObjetSimule.
 */
ObjetSimule::ObjetSimule(std::string fich_param)
{
    /** Recuperation des parametres du maillage mis dans le fichier **/
    Param_mesh(fich_param);
    
}


/**
 * \brief Interaction avec l utilisateur.
 * Methode invoquee par le graphe de scene.
 */
void ObjetSimule::Interaction(Vector MousePos)
{
    if (_Interaction == "yes")
    {
        
        
    }//if
    
}//void



/**
 * Affichage des positions de chaque sommet.
 */
void ObjetSimule::AffichagePos(int tps)
{
    /* Affichage des vecteurs par bloc */
    for(int i=0; i<_Nb_Sommets; ++i)
    {
        // Affichage du temps
        std::cout << "[T=" << tps;
        
        // Ecriture du numero du sommet
        std::cout << " ; Vertex=" << i;
        
        // Affichage des coordonnees de la position
        std::cout << " ; P=" << P[i] << std::endl;
        
    }//for_i
}

