
/** \file ObjetSimuleSPH.h
 \brief Structures de donnes relatives a la methode SPH (Smoothed Particle Hydrodynamics)
 pour simuler le comportement d un fluide.
 */

#ifndef OBJET_SIMULE_SPH_H
#define OBJET_SIMULE_SPH_H



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
#include "SolveurExpl.h"

/**
 * \brief Structure de donnees pour la methode SPH.
 */
class ObjetSimuleSPH: public ObjetSimule
{
public:
    
    /*! Constructeur */
    ObjetSimuleSPH(std::string fich_param);
    
    /*!  Lecture des parametres de l execution relatifs a la methode SPH */
    void Param_sph(std::string Fichier_Param);

    /*! Initialisation a partir des fichiers de donnees */
    void initObjetSimule();
    
    /*! Creation du maillage (pour affichage) de l objet simule */
    void initMeshObjet();
    
    /*! Calcul des densites des particules */
    void CalculDensite();
    
    /*! Calcul des forces d interaction entre particules */
    void CalculInteraction(float viscosite);
    
    /*! Simulation de l objet */
    void Simulation(Vector gravite, float viscosite, int Tps);
    
    /*! Traitement des collisions */
    void damp_reflect(int which, float barrier, int indice_part);
  
    /*! Gestion des collisions  */
    void Collision();
    
    /*! Mise a jour du Mesh (pour affichage) de l objet en fonction des nouvelles positions calculees */
    void updateVertex();

    
    /// SolveurExpl : schema d integration semi-implicite 
    SolveurExpl *_SolveurExpl;
    
    /// Declaration du tableau des densites
    std::vector<float> rho;
    
    /// Taille d une particule
    float h;
    
    /// Densite de reference
    float rho0;
    
    /// Module de Bulk (de compressibilite)
    float bulk;



};



#endif
