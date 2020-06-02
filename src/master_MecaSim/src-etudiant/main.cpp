#include <stdlib.h>
//#include <unistd.h>

#include "Viewer.h"
#include "vec.h"

using namespace std;




int main( int argc, char **argv )
{
    char tampon[100];
//    std:cout << "Le code s execute depuis " << getcwd(tampon, 100) << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    /**********************************/
    /** Pour la simulation mecanique **/
    /**********************************/

    /// Nombre d objets presents dans la simulation mecanique
    int NbObj;

    /// Tableau contenant les noms des fichiers de parametres des objets de la simulation mecanique
    string *Fichier_Param;

    /// Pour ne pas a avoir a mettre les fichiers en parametres de l execution
    /// Pour ne pas a avoir a mettre les fichiers en parametres de l execution
    if (argc == 1)
    {
        argc = 4; // modifie le nombre de parametre mis dans l execution

        argv = new char*[4];

        argv[0] = new char[256]; // Nom de l executable
        argv[1] = new char[256]; // Nb d objet dans la simulation - NB doit etre egale a 1
        argv[2] = new char[256]; // Nom du fichier de parametre de la simulation
        argv[3] = new char[256]; // Nom du fichier de parametre de l objet

        strcpy( argv[0], "./bin/master_MecaSim_etudiant");
        strcpy( argv[1], "1");
        strcpy( argv[2], "./src/master_MecaSim/exec/Fichier_Param.simu");
        strcpy( argv[3], "./src/master_MecaSim/exec/Fichier_Param.objet1");

        // Equivalent a la commande :
        //  ./bin/master_MecaSim_etudiant 1 ./src/master_MecaSim/exec/Fichier_Param.simu ./src/master_MecaSim/exec/Fichier_Param.objet1


    }

    /// Fichier contenant les parametres de l execution
    if (argc >= 2)
    {
        /// Nombre d objets a simuler
        NbObj = atoi(argv[1]);
            cout << "Nombre d objets dans la simulation mecanique : " << NbObj << endl;

        /// Tableau contenant les noms des fichiers de parametres
        // Element 0 correspond au fichier contenant les parametres generaux de l animation
        // Element i correspond au fichier contenant les parametres de l objet i
        Fichier_Param = new string[NbObj+1];

        // Recupere les noms des fichiers de donnees :
        // argv[0] : executable, argv[1] : nb objet
        // Fichier_Param[0] de la simulation correspond a argv[2]
        for (int i=0; i<= NbObj; i++)
            Fichier_Param[i] = argv[i+2];

        cout << "Fichiers de donnees de la simulation : " << Fichier_Param[0] << endl;

        for (int i=1; i<= NbObj; i++)
            cout << "Fichier de donnees de l objet " << i << " : " << Fichier_Param[i] << endl;

    }

    else
    {
        /// Usage de l execution du programme
        // Exemple pour un seul objet simule :

        cout << "Usage depuis le repertoire gkit2light:" << endl;
        cout << "<executable> NbObj <Fichier_Param_Anim> <Fichier_Param_Obj1> <Fichier_Param_Obj2> ..." << endl << endl;

        cout << "Exemple pour un seul objet : " << endl;
        cout << "./bin/master_MecaSim_etudiant 1 ./src/master_MecaSim/exec/Fichier_Param.simu ./src/master_MecaSim/exec/Fichier_Param.objet1" << endl;


        /// Arret du programme
        exit(1);

    }

    // Si pas de simulation mecanique
    //Viewer v;

    // Avec simulation mecanique
    Viewer v(Fichier_Param, NbObj);

    // Run du viewer
    v.run();


    return 0;

}
