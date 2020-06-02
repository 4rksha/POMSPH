
/** \file ObjetSimule.h
 \brief Structures de donnes communes relatives aux objets simules.
 */

#ifndef OBJET_SIMULE_H
#define OBJET_SIMULE_H

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

/**
 * \brief Texture determinee par valeurs a et b.
 */
struct Texture
{
    /// Coordonnee a de la texture
    float u;

    /// Coordonnee b de la texture
    float v;
};

/**
 * \brief Facette determinee par valeurs fi, fj, fk :
 * indices des sommets dans le fichier.
 */
struct FacetTriangle
{
    /// Premier sommet de la facette
    int fi;

    /// Second sommet de la facette
    int fj;

    /// Troisieme sommet de la facette
    int fk;
};

/**
 * \brief Structure de donnees de base des objets simules.
 */
class ObjetSimule : public Noeud
{
public:
    /*! Constructeur */
    ObjetSimule(std::string fich_param);

    /*! Lecture des parametres lies au maillage */
    void Param_mesh(std::string fich_param);

    /*! Initialisation des tableaux des sommets a partir du fichier de donnees de l objet */
    virtual void initObjetSimule() = 0;

    /*! Mise a jour du Mesh (pour affichage) de l objet en fonction des nouvelles positions calculees */
    virtual void updateVertex() = 0;

    /*! Operation de creation du maillage (servant a l affichage) */
    virtual void initMeshObjet() = 0;

    /*! Gestion des collisions */
    virtual void Collision() = 0;

    /*! Simulation de l objet */
    virtual void Simulation(Vector gravite, float viscosite, int Tps) = 0;

    /*! Interaction avec l utilisateur */
    void Interaction(Vector MousePos);

    /*! Affichage des positions de chaque sommet */
    void AffichagePos(int tps);

protected:
    /// Fichier de donnees contenant les points
    std::string _Fich_Points;

    /// Fichier de donnees contenant les masses
    std::string _Fich_Masses;

    /// Interaction avec l utilisateur ou non
    std::string _Interaction;

    /// valeur d'absorption de la vitesse en cas de collision:
    /// 1=la particule repart aussi vite, 0=elle s'arrete
    float _Friction = 1.0f;

    /// Declaration du tableau des vitesses
    std::vector<Vector> V;

    /// Declaration du tableau des accelerations
    std::vector<Vector> A;

    /// Declaration du tableau des forces
    std::vector<Vector> Force;

    /// Declaration du tableau des masses
    std::vector<float> M;

    std::vector<Vector> Vprec;
};

#endif
