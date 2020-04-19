#include <stdio.h>
#include <stdlib.h>

#define TAILLE 9

int M[TAILLE][TAILLE];
int SM[TAILLE][TAILLE];
int SAVE[TAILLE][TAILLE];

int nb_case_vide = 45;

int main()
{
    initGrid();
    drawGrids();
    return 0;
}

void drawGrids(void)
{
    printf("Resolveur de Sudoku par Raphael \nGrille: \n");
    randomGrid();
    printf("Solution: \n");
    printf("Chargement en cours...");
}

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

	generateGrid();
}

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
				printf("%c",219);
			}
		}
		else
		{
			printf("%c",219);
			for(k=1;k<37;k++)
			{
				printf("%c",219);
			}
		}

		printf("\n\t%d%c",i+1,219);

		for(j=0;j<TAILLE;j++)
		{
			if(M[i][j] == 0)
			{
				printf("   ");
			}
			else
			{
				printf(" %d ",M[i][j]);
			}

			printf("%c",219);
		}
	}
	printf("\n\t ");
	for(k=0;k<37;k++)
	{
		printf("%c",219);
	}
	printf("\n");
}
