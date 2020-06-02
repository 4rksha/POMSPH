/*
 * Param.cpp : lecture des fichiers de parametres.
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

/** \file Param.cpp
   \brief Lecture des parametres de l execution.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string.h> 


/** Fichiers de l application **/
#include "Properties.h"
#include "Scene.h"
#include "ObjetSimule.h"
#include "ObjetSimuleSPH.h"
#include "Matrix.h"


/**
 * Macro qui definit la variable var en lisant le fichier de parametres avec la cle str.
 */
#define GET_PARAM(str, var)			\
  do {						\
  std::string s = Prop[str];			\
  std::istringstream iss(s);			\
  iss >> var;					\
  } while (0);


	
/**
* Lecture des parametres de l execution relatifs a la scene.
 */
void Scene::Param(std::string Fichier_Param)
{
	/** Donnees du fichier contenant les parametres de l execution **/
	/* Proprietes du fichier */
	Properties Prop;
	
	/* Chargement du fichier */
	Prop.load(Fichier_Param);
		
	/* Viscosite du milieu */
	GET_PARAM("viscosite", _visco);
	
	/* Coordonnee de la gravite */
	float vargx, vargy, vargz;
	
	/* Coordonnee en x de la gravite */
	GET_PARAM("gx", vargx); 
	_g.x = vargx;
	
	/* Coordonnee en y de la gravite */
	GET_PARAM("gy", vargy);
	_g.y = vargy;
	
	/* Coordonnee en z de la gravite */
	GET_PARAM("gz", vargz);
	_g.z = vargz;
	
	/* Nombre d iterations de la boucle de simulation */
	GET_PARAM("nbiter", _nb_iter);
    
    /* Type d objet simule */
    std::string typeObjet;
    
    for (int i=1; i<= _NbObj ; i++){
        typeObjet = "objet";
        typeObjet += '0' + i;

        GET_PARAM(typeObjet, _type_objet[i-1]);
    }
	
}


/**
* Lecture des parametres de l execution relatfs au maillage.
 */
void ObjetSimule::Param_mesh(std::string Fichier_Param)
{
	/** Donnees du fichier contenant les parametres de l execution **/
	/* Proprietes du fichier */
	Properties Prop;
	
	/* Chargement du fichier */
	Prop.load(Fichier_Param);
	
	/* Fichier contenant les positions des particules */
	GET_PARAM("points", _Fich_Points);
	
	/* Fichier contenant les masses du maillage */
	GET_PARAM("masses", _Fich_Masses);
    
	// Interaction avec l utilisateur ou non
	GET_PARAM("interaction", _Interaction);

    
}//void


/**
 * Lecture des parametres de l execution relatfs au fluide de type SPH.
 */
void ObjetSimuleSPH::Param_sph(std::string Fichier_Param)
{
    /** Donnees du fichier contenant les parametres de l execution **/
    /* Proprietes du fichier */
    Properties Prop;
    
    /* Chargement du fichier */
    Prop.load(Fichier_Param);
    
    /// Choix du solveur
    _SolveurExpl = new SolveurExpl();
    
    std::cout << "Utilisation du schema d integration d'Euler semi-implicite"
    << std::endl;
    
    /* Intervalle de temps */
    GET_PARAM("dt", _SolveurExpl->_delta_t);
    
    /* Densite de reference */
    GET_PARAM("rho0", rho0);
    
    /* Module de Bulk */
    GET_PARAM("bulk", bulk);
    
    /* Taille des particules */
    GET_PARAM("h", h);
    
}
