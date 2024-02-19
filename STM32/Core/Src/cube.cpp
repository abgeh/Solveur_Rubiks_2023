#include "cube.h"

/*===============================================
     b           3
   l u r       2 0 4				Correspondance face et numéro de face
     f   d       1    5                                 


WHITE 0				Correspondances couleurs et numéro de couleurs
RED 1
GREEN 2
ORANGE 3
BLUE 4
YELLOW 5

               0|1|2                       Numéro des petits carrés sur chaque face
               3|4|5                            
               6|7|8                            
                                                
        0|1|2  0|1|2  0|1|2                     
        3|4|5  3|4|5  3|4|5                     
        6|7|8  6|7|8  6|7|8                     
                                                
               0|1|2            0|1|2           
               3|4|5            3|4|5           
               6|7|8            6|7|8           
                                                
===============================================*/




//Constructeur
RubiksCube::RubiksCube() {
	cube_data         = (int**)malloc(sizeof(int*)*6);
	temp_cube_data    = (int**)malloc(sizeof(int*)*6);

	for (int i = 0; i < 6; i++){
		cube_data[i]         = (int*)malloc(sizeof(int)*9);
		temp_cube_data[i]    = (int*)malloc(sizeof(int)*9);
	}

	for (int i =0; i < 6; i++){
		for (int j=0;j<9;j++){
			switch (i)
			      {
			         case 0:
			 			cube_data[i][j] = UInitialColor;
			            temp_cube_data[i][j] = UInitialColor;
			            break;
			         case 1:
						cube_data[i][j] = FInitialColor;
						temp_cube_data[i][j] = FInitialColor;
						break;
			         case 2:
						cube_data[i][j] = LInitialColor;
						temp_cube_data[i][j] = LInitialColor;
						break;
			         case 3:
						cube_data[i][j] = BInitialColor;
						temp_cube_data[i][j] = BInitialColor;
						break;
			         case 4:
						cube_data[i][j] = RInitialColor;
						temp_cube_data[i][j] = RInitialColor;
						break;
			         case 5:
						cube_data[i][j] = DInitialColor;
						temp_cube_data[i][j] = DInitialColor;
						break;
			         default:
			            break;
			      }
			/*
			cube_data[i][j] = i; 
            temp_cube_data[i][j] = i;
            */
		}
	}
}


//destructeur
RubiksCube::~RubiksCube() {
	for (int i = 0; i < 6; i++){
		free(cube_data[i]);
		free(temp_cube_data[i]);
	}
	free(cube_data);
	free(temp_cube_data);
}

void RubiksCube::RotCubePinceDroiteAntiHoraire(){
	RotateEquatorZ();
	MoveU();
	MoveDprime();
}

void RubiksCube::RotCubePinceDroiteHoraire(){
	RotCubePinceDroiteAntiHoraire();
	RotCubePinceDroiteAntiHoraire();
	RotCubePinceDroiteAntiHoraire();
}

void RubiksCube::RotCubePinceGaucheAntiHoraire(){
	RotateEquatorY();
	MoveF();
	MoveBprime();
}

void RubiksCube::RotCubePinceGaucheHoraire(){
	RotCubePinceGaucheAntiHoraire();
	RotCubePinceGaucheAntiHoraire();
	RotCubePinceGaucheAntiHoraire();
}

void RubiksCube::affichage() const{
	
	for(int i=0;i<6;i++){
		printf("face %d: [",i);
		for(int j=0;j<9;j++){
			printf("%d ",cube_data[i][j]);
		}
		printf("]\n\r \n\r");
	}
}

void RubiksCube::CopyCube(){
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 9; j++){
            cube_data[i][j] = temp_cube_data[i][j];
        }
    }
}

void RubiksCube::RotateFace(int face){

	if(face!=D) //la face du bas est un cas particulier
	{
		temp_cube_data[face][0] = cube_data[face][6];
		temp_cube_data[face][1] = cube_data[face][3];
		temp_cube_data[face][2] = cube_data[face][0];
		temp_cube_data[face][3] = cube_data[face][7];
	    	temp_cube_data[face][4] = cube_data[face][4];
	    	temp_cube_data[face][5] = cube_data[face][1];
	    	temp_cube_data[face][6] = cube_data[face][8];
	    	temp_cube_data[face][7] = cube_data[face][5];
	    	temp_cube_data[face][8] = cube_data[face][2];
	}
	else{
		temp_cube_data[face][0] = cube_data[face][2];
		temp_cube_data[face][1] = cube_data[face][5];
		temp_cube_data[face][2] = cube_data[face][8];
		temp_cube_data[face][3] = cube_data[face][1];
		temp_cube_data[face][4] = cube_data[face][4];
		temp_cube_data[face][5] = cube_data[face][7];
		temp_cube_data[face][6] = cube_data[face][0];
		temp_cube_data[face][7] = cube_data[face][3];
		temp_cube_data[face][8] = cube_data[face][6];
	}
	CopyCube();
}

void RubiksCube::BringToTop_Front(int top,int front){
	
	int couleur_voulu = cube_data[front][4];
	BringToTop(top);
	while(cube_data[F][4] != couleur_voulu){
		
		RotateEquatorZ();
		MoveU();
		MoveDprime();	
	}
}

void RubiksCube::BringToFront(int face){
    switch(face){
        case R:
            RotateEquatorZ();
            MoveU();
            MoveDprime();
            moves--;
            moves--;
            break;
    	case B:
            BringToFront(R);
            BringToFront(R);
            moves--;
            moves--;
            break;
        case L:
                
            RotateEquatorZ();
            RotateEquatorZ();
            RotateEquatorZ();
            MoveUprime();
            MoveD();
            moves--;
            moves--;
            break;
        default:
            break;
    }
}

void RubiksCube::BringToTop(int face){
    switch(face){
        case F:
            RotateEquatorX();
            MoveR();
            MoveLprime();
            moves--;
            moves--;
            break;
        case L:
            RotateEquatorY();
            MoveF();
            MoveBprime();
            moves--;
            moves--;
            break;
	case B:
            RotateEquatorX();
            RotateEquatorX();
            RotateEquatorX();
            MoveRprime();
            MoveL();
            moves--;
            moves--;
            break;
        case R:
            RotateEquatorY();
            RotateEquatorY();
            RotateEquatorY();
            MoveFprime();
            MoveB();
            moves--;
            moves--;
            break;
	  case D:
            BringToTop(F);
            BringToTop(F);
            break;
        default:
            break;
    }
}

int RubiksCube::WhereIsColor(int initialColorFace){
	for(int i=0; i<6; i++){
		if(cube_data[i][4]==initialColorFace){
			switch(i){
				case 0:
					return 'U';
				case 1:
					return 'F';
				case 2:
					return 'L';
				case 3:
					return 'B';
				case 4:
					return 'R';
				case 5:
					return 'D';
				default:
					return -1;
			}
		}
	}
	return -1;
}

void RubiksCube::RotateEquatorY(){

    temp_cube_data[D][3] = cube_data[R][5];
    temp_cube_data[D][4] = cube_data[R][4];
    temp_cube_data[D][5] = cube_data[R][3];

    temp_cube_data[L][3] = cube_data[D][5];
    temp_cube_data[L][4] = cube_data[D][4];
    temp_cube_data[L][5] = cube_data[D][3];
    
    temp_cube_data[U][3] = cube_data[L][3];
    temp_cube_data[U][4] = cube_data[L][4];
    temp_cube_data[U][5] = cube_data[L][5];

    temp_cube_data[R][3] = cube_data[U][3];
    temp_cube_data[R][4] = cube_data[U][4];
    temp_cube_data[R][5] = cube_data[U][5];

    CopyCube();
}


void RubiksCube::RotateEquatorX(){

    temp_cube_data[U][1] = cube_data[F][1];
    temp_cube_data[U][4] = cube_data[F][4];
    temp_cube_data[U][7] = cube_data[F][7];

    temp_cube_data[B][1] = cube_data[U][1];
    temp_cube_data[B][4] = cube_data[U][4];
    temp_cube_data[B][7] = cube_data[U][7];
    
    temp_cube_data[D][1] = cube_data[B][7];
    temp_cube_data[D][4] = cube_data[B][4];
    temp_cube_data[D][7] = cube_data[B][1];

    temp_cube_data[F][1] = cube_data[D][7];
    temp_cube_data[F][4] = cube_data[D][4];
    temp_cube_data[F][7] = cube_data[D][1];

    CopyCube();
}


void RubiksCube::RotateEquatorZ(){

    temp_cube_data[L][7] = cube_data[F][5];
    temp_cube_data[L][4] = cube_data[F][4];
    temp_cube_data[L][1] = cube_data[F][3];

    temp_cube_data[B][3] = cube_data[L][7];
    temp_cube_data[B][4] = cube_data[L][4];
    temp_cube_data[B][5] = cube_data[L][1];

    temp_cube_data[R][7] = cube_data[B][5];
    temp_cube_data[R][4] = cube_data[B][4];
    temp_cube_data[R][1] = cube_data[B][3];

    temp_cube_data[F][3] = cube_data[R][7];
    temp_cube_data[F][4] = cube_data[R][4];
    temp_cube_data[F][5] = cube_data[R][1];

    CopyCube();
}


void RubiksCube::RotateUp(){

    temp_cube_data[L][2] = cube_data[F][0];
    temp_cube_data[L][5] = cube_data[F][1];
    temp_cube_data[L][8] = cube_data[F][2];
  
    temp_cube_data[B][6] = cube_data[L][8];
    temp_cube_data[B][7] = cube_data[L][5];
    temp_cube_data[B][8] = cube_data[L][2];
  
    temp_cube_data[R][6] = cube_data[B][8];
    temp_cube_data[R][3] = cube_data[B][7];
    temp_cube_data[R][0] = cube_data[B][6];
  
    temp_cube_data[F][0] = cube_data[R][6];
    temp_cube_data[F][1] = cube_data[R][3];
    temp_cube_data[F][2] = cube_data[R][0];
  
    CopyCube();
}

void RubiksCube::RotateDown(){

        temp_cube_data[R][2] = cube_data[F][8];
        temp_cube_data[R][5] = cube_data[F][7];
        temp_cube_data[R][8] = cube_data[F][6];

        temp_cube_data[B][0] = cube_data[R][2];
        temp_cube_data[B][1] = cube_data[R][5];
        temp_cube_data[B][2] = cube_data[R][8];

        temp_cube_data[L][0] = cube_data[B][2];
        temp_cube_data[L][3] = cube_data[B][1];
        temp_cube_data[L][6] = cube_data[B][0];

        temp_cube_data[F][6] = cube_data[L][0];
        temp_cube_data[F][7] = cube_data[L][3];
        temp_cube_data[F][8] = cube_data[L][6];

        CopyCube();
}

void RubiksCube::RotateBack(){

        temp_cube_data[D][0] = cube_data[L][2];
        temp_cube_data[D][1] = cube_data[L][1];
        temp_cube_data[D][2] = cube_data[L][0];

        temp_cube_data[R][0] = cube_data[D][2];
        temp_cube_data[R][1] = cube_data[D][1];
        temp_cube_data[R][2] = cube_data[D][0];

        temp_cube_data[U][0] = cube_data[R][0];
        temp_cube_data[U][1] = cube_data[R][1];
        temp_cube_data[U][2] = cube_data[R][2];

        temp_cube_data[L][0] = cube_data[U][0];
        temp_cube_data[L][1] = cube_data[U][1];
        temp_cube_data[L][2] = cube_data[U][2];

        CopyCube();
}

void RubiksCube::RotateFront(){

        temp_cube_data[L][6] = cube_data[D][8];
        temp_cube_data[L][7] = cube_data[D][7];
        temp_cube_data[L][8] = cube_data[D][6];

        temp_cube_data[D][6] = cube_data[R][8];
        temp_cube_data[D][7] = cube_data[R][7];
        temp_cube_data[D][8] = cube_data[R][6];

        temp_cube_data[U][6] = cube_data[L][6];
        temp_cube_data[U][7] = cube_data[L][7];
        temp_cube_data[U][8] = cube_data[L][8];

        temp_cube_data[R][6] = cube_data[U][6];
        temp_cube_data[R][7] = cube_data[U][7];
        temp_cube_data[R][8] = cube_data[U][8];

        CopyCube();
}

void RubiksCube::RotateLeft(){

        temp_cube_data[B][0] = cube_data[U][0];
        temp_cube_data[B][3] = cube_data[U][3];
        temp_cube_data[B][6] = cube_data[U][6];

        temp_cube_data[D][0] = cube_data[B][6];
        temp_cube_data[D][3] = cube_data[B][3];
        temp_cube_data[D][6] = cube_data[B][0];

        temp_cube_data[F][0] = cube_data[D][6];
        temp_cube_data[F][3] = cube_data[D][3];
        temp_cube_data[F][6] = cube_data[D][0];

        temp_cube_data[U][0] = cube_data[F][0];
        temp_cube_data[U][3] = cube_data[F][3];
        temp_cube_data[U][6] = cube_data[F][6];

        CopyCube();
}

void RubiksCube::RotateRight(){
        temp_cube_data[B][2] = cube_data[U][2];
        temp_cube_data[B][5] = cube_data[U][5];
        temp_cube_data[B][8] = cube_data[U][8];

        temp_cube_data[D][2] = cube_data[B][8];
        temp_cube_data[D][5] = cube_data[B][5];
        temp_cube_data[D][8] = cube_data[B][2];

        temp_cube_data[F][2] = cube_data[D][8];
        temp_cube_data[F][5] = cube_data[D][5];
        temp_cube_data[F][8] = cube_data[D][2];

        temp_cube_data[U][2] = cube_data[F][2];
        temp_cube_data[U][5] = cube_data[F][5];
        temp_cube_data[U][8] = cube_data[F][8];

        CopyCube();
}

void RubiksCube::MoveR(){

        RotateFace(R);
        RotateRight();
        moves++;
}

void RubiksCube::MoveR2(){

        MoveR();
        MoveR();
        moves--;
}

void RubiksCube::MoveRprime(){

        MoveR();
        MoveR();
        MoveR();
        moves--;
        moves--;
}

void RubiksCube::MoveL(){

        RotateFace(L);
        RotateLeft();
        RotateLeft();
        RotateLeft();
        moves++;
}

void RubiksCube::MoveL2(){

        MoveL();
        MoveL();
        moves--;
}

void RubiksCube::MoveLprime(){

        MoveL();
        MoveL();
        MoveL();
        moves--;
        moves--;
}

void RubiksCube::MoveU(){

        RotateFace(U);
        RotateUp();
        moves++;
}

void RubiksCube::MoveU2(){

        MoveU();
        MoveU();
        moves--;
}

void RubiksCube::MoveUprime(){

        MoveU();
        MoveU();
        MoveU();
        moves--;
        moves--;
}

void RubiksCube::MoveD(){

        RotateFace(D);
        RotateDown();
        moves++;
    
}

void RubiksCube::MoveD2(){

        MoveD();
        MoveD();
        moves--;
}

void RubiksCube::MoveDprime(){

        MoveD();
        MoveD();
        MoveD();
        moves--;
        moves--;
}

void RubiksCube::MoveF(){

        RotateFace(F);
        RotateFront();
        moves++;
}

void RubiksCube::MoveF2(){

        MoveF();
        MoveF();
        moves--;
}

void RubiksCube::MoveFprime(){

        MoveF();
        MoveF();
        MoveF();
        moves--;
        moves--;
}

void RubiksCube::MoveB(){

        RotateFace(B);
        RotateBack();
        moves++;
}

void RubiksCube::MoveB2(){
        MoveB();
        MoveB();
        moves--;
}

void RubiksCube::MoveBprime(){

        MoveB();
        MoveB();
        MoveB();
        moves--;
        moves--;
}
