#include <stdio.h>
#include <stdlib.h>

#define TAILLE 9

//On déclare les variables de tableau
int M[TAILLE][TAILLE];
int SM[TAILLE][TAILLE];
int SAVE[TAILLE][TAILLE];

int nb_case_vide = 45;

int main()
{
    //On initialise ici nos grilles (exercice/solutions)
    initGrid();

    //On affiche les deux grilles
    drawGrids();
    return 0;
}

//Fonction qui affiche les deux grilles
void drawGrids(void)
{
    printf("Resolveur de Sudoku par Raphael \nGrille: \n");
    randomGrid();

    printf("Solution: \n");
    solutionGrid();
}

//Fonction qui initialise le tableau de grille en mettant les lignes et les collonnes a zéro par défaut.
void initGrid(void)
{
	int i,j;

	for(i=0; i<TAILLE; i++ )
	{
		for( j=0; j<TAILLE; j++ )
		{
			M[i][j] = 0;
		}
	}

	//Ici on génére la grille en respectant des règles de bases.
	generateGrid();
}


//Dans cette fonction on remplis le tableau en vérifiant que la grille respecte les règles de base.
void generateGrid(void)
{
	int i,j,n;
	srand((unsigned int)time(NULL));
	for(i=0;i<TAILLE;i++)
	{
		while(1)
		{
			n = rand()%TAILLE + 1;
			if(VerifierLigne(0,n))
			{
				M[0][i] = n;
				break;
			}
		}
	}

	for(i=1;i<TAILLE;i++)
	{
		if(SetValue(1,0,i))
		{
			break;
		}
	}

	for(i=0;i<TAILLE;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			SM[i][j] = M[i][j];
		}
	}

	for(i=0;i<TAILLE;i = i+3)
	{
		for(j=0;j<TAILLE;j = j+3)
		{
			eraseValue(i,j);
		}
	}

	for(i=0;i<TAILLE;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			SAVE[i][j] = M[i][j];
		}
	}
}

void eraseValue(int ligne, int colonne)
{
	int i,j,n;

	n=0;

	while(n<6)
	{
		for(i=ligne;i<ligne+3;i++)
		{
			for(j=colonne;j<colonne+3;j++)
			{
				if(M[i][j] != 0)
				{
					if(rand()%2 == 0)
					{
						n++;
						M[i][j] = 0;
						if(n==5) return;
					}
				}
			}
		}
	}
}

int SetValue(int ligne,int colonne,int value)
{
	int L=ligne,C=colonne,i;
	int ret = 0;
	if(VerifierLigne(ligne,value) && VerifierColonne(colonne,value) && VerifierCarreau(ligne,colonne,value))
	{
		M[ligne][colonne] = value;

		C=C+1;
		if(C == TAILLE)
		{
			C = 0;
			L = L+1;
			if(L == TAILLE) return 1;
		}

		for(i=0;i<TAILLE;i++)
		{
			if(SetValue(L,C,i+1))
			{
				return 1;
			}
		}
	}

	M[ligne][colonne] = 0;
	return 0;
}

//Cette fonction sert a vérifier qu'il n'y a pas deux fois la même valeur dans une ligne
int VerifierLigne(int ligne, int valeur)
{
	int i;
	for(i=0;i<TAILLE;i++)
	{
		if(M[ligne][i] == valeur)
		{
			return 0;
		}
	}
	return 1;
}

//Cette fonction sert a vérifier qu'il n'y a pas deux fois la même valeur dans une colonne
int VerifierColonne(int colonne,int valeur)
{
	int i;
	for(i=0;i<TAILLE;i++)
	{
		if(M[i][colonne] == valeur)
		{
			return 0;
		}
	}
	return 1;
}

int VerifierCarreau(int ligne,int colonne,int valeur)
{
	int i,j,L,C;

	L = (int)(ligne/3) * 3;
	C = (int)(colonne/3) * 3;

	for(i=L;i<L+3;i++)
	{
		for(j=C;j<C+3;j++)
		{
			if(M[i][j] == valeur)
			{
				return 0;
			}
		}
	}

	return 1;
}
void randomGrid(void)
{
	int i,j,k;

	for(i=0;i<TAILLE;i++)
	{
		printf("\n\t ");
		if(i%3==0)
		{
			for(k=0;k<37;k++)
			{
				printf("*",219);
			}
		}
		else
		{
			for(k=0;k<37;k++)
			{
			    if (k == 36) {
                    printf("*", 219);
			    }


			    if (k == 0) {
                    printf("*", 219);
			    }

			    if (k != 36 && k != 0 ) {
                    printf("-", 219);
			    }

			}
		}

		//Ici on affiche les traits latéraux gauche
		printf("\n\t *",i+1,219);

		for(j=0;j<TAILLE;j++)
		{
			if(M[i][j] == 0) //Si la case vaut zéro on affixe un vide
			{
				printf("   ");
			}
			else //La case ne vaut pas zéro, donc on affiche ici les valeurs des cases
			{
				printf(" %d ",M[i][j]);
			}


			if (j == 2){
                printf("*",219);
			}

			if (j == 5){
                printf("*",219);
			}

			if (j == 8){
                printf("*",219);
			}

			if (j != 2 && j != 5 && j != 8){
                printf("|",219);
			}



		}
	}
	printf("\n\t ");
	for(k=0;k<37;k++)
	{
		printf("*",219);
	}
	printf("\n");
}


void solutionGrid(void)
{
	int i,j,k;

	for(i=0;i<TAILLE;i++)
	{
		printf("\n\t ");
		if(i%3==0)
		{
			for(k=0;k<37;k++)
			{
				printf("*",219);
			}
		}
		else
		{
			for(k=0;k<37;k++)
			{
			    if (k == 36) {
                    printf("*", 219);
			    }


			    if (k == 0) {
                    printf("*", 219);
			    }

			    if (k != 36 && k != 0 ) {
                    printf("-", 219);
			    }

			}
		}

		//Ici on affiche les traits latéraux gauche
		printf("\n\t *",i+1,219);

		for(j=0;j<TAILLE;j++)
		{
			if(M[i][j] == 0) //Si la case vaut zéro on affixe un vide
			{
				printf(" %d ",SM[i][j]);
			}
			else //La case ne vaut pas zéro, donc on affiche ici les valeurs des cases
			{
				printf(" %d ",M[i][j]);
			}


			if (j == 2){
                printf("*",219);
			}

			if (j == 5){
                printf("*",219);
			}

			if (j == 8){
                printf("*",219);
			}

			if (j != 2 && j != 5 && j != 8){
                printf("|",219);
			}



		}
	}
	printf("\n\t ");
	for(k=0;k<37;k++)
	{
		printf("*",219);
	}
	printf("\n");
}


