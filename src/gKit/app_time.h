
#ifndef _APP_TIME_H
#define _APP_TIME_H

#include "glcore.h"
#include "app.h"
#include "text.h"


//! \addtogroup application utilitaires pour creer une application
///@{

//! \file
/*! squelette d'application: creation d'une fenetre, d'un contexte openGL et gestion des evenements.
    tuto7.cpp et tuto8.cpp presentent un exemple simple d'utilisation.

    la class App expose les fonctionnalites de window.h, elles sont juste presentees differemment.
    les fonctions globales de window.h sont toujours utilisables (a part run() qui est remplace par App::run()).
*/

//! classe application.
class AppTime : public App
{
public:
    //! constructeur, dimensions de la fenetre et version d'openGL.
    AppTime( const int width, const int height, const int major= 3, const int minor= 3 );
    virtual ~AppTime( );

    //! a deriver pour creer les objets openGL.
    virtual int init( ) = 0;
    //! a deriver pour detruire les objets openGL.
    virtual int quit( ) = 0;

    //! a deriver et redefinir pour animer les objets en fonction du temps.
    //~ virtual int update( const float time, const float delta ) { return 0; }
    using App::update;

    //! a deriver pour afficher les objets.
    virtual int render( ) = 0;

    //! execution de l'application.
    int run( );

protected:
    Text m_console;
    GLuint m_time_query;
};


#endif // _APP_H
