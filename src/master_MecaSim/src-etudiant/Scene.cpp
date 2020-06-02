/*
 * Scene.cpp : Scene 3D
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

/** \file Scene.cpp
\brief Definition du graphe de scene. 
Appel des differentes fonctions sur l'ensemble des noeuds du graphe de scene. 
*/



/** Librairie de base **/
#include <list>
#include <string>
#include <iostream>

#include "vec.h"

/** Fichiers de l application **/
#include "Noeuds.h"
#include "Scene.h"




/**
* Constructeur de la class Scene. 
 */
Scene::Scene(std::string Fichier_Param, int NbObj)
{
    /// Nombre d objets presents dans la scene
    _NbObj = NbObj;
    
	// Lecture du fichier de parametres : 
	// recuperation de la gravite et de la viscosite
	Param(Fichier_Param);
    
}



/**
* Ajoute un enfant dans le graphe de scene. 
 */
void Scene::attache(Noeud *n)
{ 
	_enfants.push_back(n); 
}


/** 
* Renvoie le nom des enfants du graphe de scene. 
*/
void Scene::getName()
{
	ListeNoeuds::iterator e;
	std::cout << "----------------- Objets de la scene : " ;
	
	for(e=_enfants.begin(); e!=_enfants.end(); e++)
	{
		std::cout << (*e)->getName() << " " ;
	}
	
	std::cout << " " << std::endl;
}


/**
* Initialisation des enfants du graphe de scene.
 */
void Scene::initObjetSimule()
{
	//std::cout << "----------------- Scene::initObjetSimule()-------------" << std::endl;
    
	ListeNoeuds::iterator e;
    int i = 0;
	
	for(e=_enfants.begin(); e!=_enfants.end(); e++)
	{
        std::cout << "-------------------------------------- " << std::endl;

        std::cout << "Initialisation de l objet " << _type_objet[i] << std::endl;

		(*e)->initObjetSimule();
        
        i++;
        
	}

    
    //std::cout << "----------------- FIN -- Scene::initObjetSimule()-------------" << std::endl;

}


/**
 * Creation du maillage (servant a l affichage) des enfants du graphe de scene.
 */
void Scene::initMeshObjet()
{
    //std::cout << "----------------- Scene::initMeshObjet()-------------" << std::endl;
    
    ListeNoeuds::iterator e;
    int i = 0;
    
    for(e=_enfants.begin(); e!=_enfants.end(); e++)
    {
        std::cout << "-------------------------------------- " << std::endl;

        std::cout << "Pour objet " << _type_objet[i] << std::endl;

        (*e)->initMeshObjet();
        
        i++;
        
    }
    std::cout << "-------------------------------------- " << std::endl;

    
    //std::cout << "----------------- FIN -- Scene::initMeshObjet()-------------" << std::endl;
    
}



/**
 * Simulation des enfants du graphe de scene.
 */
void Scene::Simulation(int Tps)
{
	//std::cout << "----------------- Scene::Simulation()-------------" << std::endl;
    
	ListeNoeuds::iterator e;
	
	for(e=_enfants.begin(); e!=_enfants.end(); e++)
	{
		(*e)->Simulation(_g, _visco, Tps);
	}
}


/**
 * Gestion des collisions.
 */
void Scene::Collision()
{
    //std::cout << "----------------- Scene::Collision()-------------" << std::endl;
    
    ListeNoeuds::iterator e;
    
    for(e=_enfants.begin(); e!=_enfants.end(); e++)
    {
        (*e)->Collision();
    }
}


/**
* Interation de l utilisateur avec chacun des enfants. 
*/
void Scene::Interaction(Vector MousePos)
{
	//std::cout << "----------------- Scene::interaction()-------------" << std::endl;
    
	ListeNoeuds::iterator e;
	
	// Appel de la fonction interaction pour chacun des enfants
	for(e=_enfants.begin(); e!=_enfants.end(); e++)
	{
		(*e)->Interaction(MousePos);
	}
}


/*
 * Modification de la gravite de la scene.
 */
void Scene::setGravite(Vector g)
{
    // Vecteur de gravite
    _g = g;
    
}


/*
 * Modification de la viscosite du milieu. 
 */
void Scene::setVisco(float visco)
{
	// Viscosite du milieu
	_visco = visco;
}
