/** \file Viewer.h
 * \brief Viewer de l application.
 */


#ifndef VIEWER_H
#define VIEWER_H

#include "glcore.h"

// Fichiers de gkit2light
#include "window.h"
#include "program.h"
#include "buffer.h"
#include "texture.h"
#include "mesh.h"
#include "draw.h"
#include "vec.h"
#include "mat.h"
#include "orbiter.h"
#include "app.h"

// Fichiers de master_meca_sim
#include "Scene.h"
#include "ObjetSimule.h"

using namespace std;


/// Dimension pour les collisions
const int DIMW = 6;




class Viewer : public App
{
public:
    
    //! Constructeur
    Viewer();
    
    //! Constructeur dans le cas de la simulation mecanique
    Viewer(string *Fichier_Param, int NbObj);

    //! Initialise tout : compile les shaders et construit le programme + les buffers + le vertex array.
    //! renvoie -1 en cas d'erreur.
    // Definition de la procedure dans Viewer-init.cpp
    int init();

    //! La fonction d'affichage
    int render();

    //! Libere tout
    int quit();

    //! Affichage de l aide
    void help();

    //! Mise a jour
    int update(const float time, const float delta);

protected:

    Orbiter m_camera;
    DrawParam gl;

    // Graphe de scene des objets de la simulation mecanique
    Scene *_Simu;
    
    // Mouvement au clavier
    Vector MousePos;
    
    // Le temps
    int Tps;
    
    // Booleens sur le mode d affichage
    bool mb_cullface;
    bool mb_wireframe;

    // Booleens pour l affichage des objets de la scene
    bool b_draw_grid;
    bool b_draw_axe;
 
    // Concerne uniquement les objets qui ne sont pas soumis a la simulation mecanique
    // Declaration des maillages relatifs aux objets de la scene
    // Exemple : Mesh m_votreObjet;
    Mesh m_axe;
    Mesh m_grid;
    Mesh m_cube;
    Mesh m_plan;
    Mesh m_sphere;
    
    // Declaration des textures
    // Exemple : GLuint m_votreObjet_texture;
    GLuint m_cube_texture;
    
    /// Declaration de la texture pour le tissu
    GLuint m_tissu_texture;
    
    // Concerne uniquement les objets qui ne sont pas soumis a la simulation mecanique
    // Declaration des procedures d initialisation des objets de la scene
    // Definition des procedures dans Viewer-init.cpp
    // Exemple : void init_votreObjet();
    void init_axe();
    void init_grid();
    void init_cube();
    void init_sphere();
  
    
    // Creation du maillage du plan de collision (x, y, z)
    void init_plan(float x, float y, float z);
    
    
    // Gestion de la camera et de la lumiere
    void manageCameraLight();
    
    
    /* POUR RESUMER :
     
     Pour creer un nouvel objet non simule (declaration + creation du maillage + affichage), vous devez :
     
     - declarer votre objet de type Mesh : Mesh m_votreObjet;
     
     - declarer une texture si besoin : GLuint m_votreObjet_texture;
     
     - declarer une fonction init_votreObjet() - et faire son appel dans la fonction Viewer::init()
     
     - ajouter dans la fonction Viewer::render() un appel a l'affichage de votre objet (gl.draw(Mesh))
     
     */
    
};



#endif
