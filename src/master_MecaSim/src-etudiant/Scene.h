/*
 * Scene.h : Scene 3D
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

/** \file Scene.h
\brief Definition du graphe de scene 
*/


#ifndef SCENE_H
#define SCENE_H


/** Librairie de base **/
#include <list>
#include <string>
#include <iostream>

#include "vec.h"

/** Fichiers de l application master_meca_sim **/
#include "Noeuds.h"



/// Nombre d'objets maximum presents dans la scene
const int NB_OBJ_MAX = 100;

/**
* \brief Type liste de noeuds.
 */
typedef std::list<Noeud*> ListeNoeuds;


/**
* \brief Scene 3D (visualisation et animation).
 */
class Scene 
{
public:
	
	/*! Constructeur avec en parametres fichier + nb objets */
	Scene(std::string Fichier_Param, int NbObj);
	
	/*! Ajoute un enfant dans le graphe de scene */
	void attache(Noeud *n);
	
	/*! Renvoie le nom des enfants */
	void getName();
	
	/*! Lecture des parametres de l execution relatifs a la scene */
	void Param(std::string Fichier_Param);
	
	/*! Modification de la gravite de la scene */
	void setGravite(Vector g);
	
	/*! Modification de la viscosite du milieu */
	void setVisco(float visco);
	
	/*! Action d initialisation */
	void initObjetSimule();
		
    /*! Action de creation du maillage des objets */
    void initMeshObjet();
	
	/*! Action de simulation */
	void Simulation(int Tps);
    
    /*! Gestion des collisions. Rajoutez des parametres si besoin. */
    void Collision();
	
	/*! Interation de l utilisateur avec chacun des enfants */
	void Interaction(Vector MousePos);
		
	/*! Destructeur */
	virtual ~Scene(){};
	
	
public:
		
	/// Liste de pointeurs sur les enfants	
	ListeNoeuds _enfants;  
	
	/// Gravite de la scene 
	Vector _g;
	
	/// Viscosite du milieu
	float _visco;
	
	/// Nombre d iterations de la boucle de simulation 
	int _nb_iter;
    
    /// Type d objet simule
    std::string _type_objet[NB_OBJ_MAX];
    
    /// Nombre d objets presents dans la scene
    int _NbObj;
	
};


#endif
