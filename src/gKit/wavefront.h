
#ifndef _OBJ_H
#define _OBJ_H

#include "mesh.h"


//! \addtogroup objet3D
///@{

//! \file 
//! charge un fichier wavefront .obj et construit un mesh.

//! charge un fichier wavefront .obj et renvoie un mesh compose de triangles non indexes. utiliser glDrawArrays pour l'afficher. a detruire avec Mesh::release( ).
Mesh read_mesh( const char *filename );

//! enregistre un mesh dans un fichier .obj.
int write_mesh( const Mesh& mesh, const char *filename );

///@}
#endif
