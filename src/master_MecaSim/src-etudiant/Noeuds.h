/*
 * Noeuds.h : Scene 3D
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


/** \file Noeuds.h
\brief Definition des classes de noeuds du graphe de scene 
*/


#ifndef NOEUDS_H
#define NOEUDS_H


/** Librairie de base **/
#include <list>
#include <string>
#include <iostream>


#include "vec.h"
#include "draw.h"





/**
* \brief Classe de base pour tous les elements de la scene.
 */
class Noeud 
{
public:
	
	/*! Constructeur */
	Noeud() {}
	
	/*! Set name */
	void setName(const char* n) {_name = std::string(n); }
	
	/*! Get name */
	const std::string &getName() const {return _name;}
	
	/*! Operation d initialisation */
	virtual void initObjetSimule() = 0;
    
    /*! Operation de creation du maillage (servant a l affichage) */
    virtual void initMeshObjet() = 0;
		
	/*! Operation de simulation */
	virtual void Simulation(Vector gravite, float viscosite, int Tps) = 0;
    
    /*! Gestion des collisions */
    virtual void Collision() = 0;
    
	/*! Operation d'interaction */
	virtual void Interaction(Vector MousePos) = 0;
    
    /*! Mise a jour du Mesh (pour affichage) */
    virtual void updateVertex() = 0;
	
	/*! Destructeur */
	virtual ~Noeud(){};
	
	
public:
		
    /// Nom du noeud
    std::string _name;
    
    /// Declaration du Mesh (maillage pour l affichage)
    Mesh m_ObjetSimule;
    
    /// Coordonnees du point d interaction
    Vector Coord_Point_Inter;
    
    /// Nombre de sommets
    int _Nb_Sommets;
    
    /// Declaration du tableau des positions
    std::vector<Vector> P;
    
    /// Booleen : utilisation texture pour affichage
    bool _use_texture;
    
};




#endif
