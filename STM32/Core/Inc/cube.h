#include<stdio.h>
#include<stdlib.h>
//#include<math.h>
//#include<time.h>

#define WHITE 0
#define RED 1
#define GREEN 2
#define ORANGE 3
#define BLUE 4
#define YELLOW 5

#define U 0
#define F 1
#define L 2
#define B 3
#define R 4
#define D 5

#define UInitialColor 5
#define FInitialColor 1
#define LInitialColor 2
#define BInitialColor 3
#define RInitialColor 4
#define DInitialColor 0


class RubiksCube
{
        public:

                // constructeur
                RubiksCube();

                // destructeur
                ~RubiksCube();

                void affichage() const;

                // Amene la face voulu devant
                void BringToFront(int face);

                // Amene la face face au top (elle devient donc la nouvelle face Up=haut)
                void BringToTop(int face);

                // Amene la face face au top (elle devient donc la nouvelle face Up=haut) et la face front au front (elle devient donc la nouvelle face Front=devant)
                void BringToTop_Front(int top,int front);

                // Simule les rotations qu'effectue le robot sur le cube virtuel
                void RotCubePinceDroiteAntiHoraire();
                void RotCubePinceDroiteHoraire();
                void RotCubePinceGaucheAntiHoraire();
                void RotCubePinceGaucheHoraire();

                // Simule l'ensemble des mouvements de base du robot
                void MoveR();
                void MoveR2();
                void MoveRprime();

                void MoveL();
                void MoveL2();
                void MoveLprime();

                void MoveU();
                void MoveU2();
                void MoveUprime();

                void MoveD();
                void MoveD2(); 
                void MoveDprime();

                void MoveF();
                void MoveF2();
                void MoveFprime();

                void MoveB();
                void MoveB2();
                void MoveBprime();

                // Retourne le numéro de la face de la couleur demandé
                int WhereIsColor(int initialColorFace);

        protected:

                // Donnee du cube
                int **cube_data;

                // Stockage temporaire des donnees du cube
                int **temp_cube_data;

                //Compteur de mouvement
                int moves;

                // copy temp_cube_data into cube_data
                void CopyCube();

                // Réecrit les faces en fonction des mouvements effectués
                void RotateFace(int);
                void RotateEquatorX();
                void RotateEquatorY();
                void RotateEquatorZ();
                void RotateRight();
                void RotateLeft();
                void RotateUp();
                void RotateDown();
                void RotateFront();
                void RotateBack();

};

