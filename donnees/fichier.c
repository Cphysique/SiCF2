/*
Copyright octobre 2020, Stephan Runigo
runigo@free.fr
SiCF 2.2  simulateur de corde vibrante et spectre
Ce logiciel est un programme informatique servant à simuler l'équation
d'une corde vibrante, à calculer sa transformée de fourier, et à donner
une représentation graphique de ces fonctions.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée. Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard l'attention de l'utilisateur est attirée sur les risques
associés au chargement, à l'utilisation, à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant des connaissances informatiques approfondies. Les
utilisateurs sont donc invités à charger et tester l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "fichier.h"

int fichierEcritureParametre(systemeT * systeme, char * nom);
int fichierLectureParametre(systemeT * systeme, char * nom);


int fichierInitialiseSysteme(systemeT * systeme, fourierT * fourier, graphesT * graphes);

int fichierEcriturePosition(systemeT * systeme, char * nom);
int fichierLecturePosition(systemeT * systeme, char * nom);

int fichierFonctionNulle(systemeT * systeme);
int fichierFonctionTriangle(systemeT * systeme, int numero);
int fichierFonctionCarre(systemeT * systeme, int numero);
int fichierFonctionSinus(systemeT * systeme, int numero);


int fichierEcriture(systemeT * systeme, char * nom)
	{
	fprintf(stderr, "Ecriture des paramètres %s\n", nom);
	fichierEcritureParametre(systeme, nom);
	fprintf(stderr, "Ecriture des positions %s\n", nom);
	fichierEcriturePosition(systeme, nom);

	return 0;
	}

int fichierLecture(systemeT * systeme, fourierT * fourier, graphesT * graphes, char * nom)
	{
			fprintf(stderr, "Réinitialisation du système\n");

		fprintf(stderr, "Initialisation des paramètres %s\n", nom);
	fichierLectureParametre(systeme, nom);

		fprintf(stderr, "Initialisation du système \n");
	fichierInitialiseSysteme(systeme, fourier, graphes);

		fprintf(stderr, "Initialisation des positions %s\n", nom);
	fichierLecturePosition(systeme, nom);

	return 0;
	}

int fichierInitialiseSysteme(systemeT * systeme, fourierT * fourier, graphesT * graphes)
	{
            	// Réinitialisation du système

	systemeInitialise(systeme);

	changeFormeDissipation(systeme, (*systeme).modeDissipation);

	changeConditionsLimites(systeme, (*systeme).libreFixe);

	graphesInitialiseNombre(graphes, (*systeme).nombre);

	fourierInitialise(fourier, (*systeme).nombre);

	return 0;
	}


int fichierEcritureParametre(systemeT * systeme, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */
	float reel;
	int entier;

	char chemin[120] = "./donnees/enregistrement/parametre_";

	char * extension = ".sicf";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "w");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
		{
		// Moteurs
			// Paramètres d'horloge
		reel = (*systeme).moteurs.dt;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.chrono;
			fprintf(fichier, "%f\n", reel);

			// Moteur périodique sur le premier pendule
		entier = (*systeme).moteurs.generateur;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).moteurs.amplitude;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.frequence;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.phi;
			fprintf(fichier, "%f\n", reel);

			// Moteur courant Josephson
		entier = (*systeme).moteurs.etatJosephson;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).moteurs.courantJosephson;
			fprintf(fichier, "%f\n", reel);

			// Moteur créateur de Fluxon
		entier = (*systeme).moteurs.fluxon;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).moteurs.deltaDephasage;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).moteurs.dephasage;
			fprintf(fichier, "%f\n", reel);

		// Caractéristique de la chaîne
		entier = (*systeme).nombre;
			fprintf(fichier, "%d\n", entier);
		entier = (*systeme).equation;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).dephasage;
			fprintf(fichier, "%f\n", reel);
		entier = (*systeme).libreFixe;
			fprintf(fichier, "%d\n", entier);

		// Paramètres physiques
		reel = (*systeme).masseDroite;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).masseGauche;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).longueur;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).couplage;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).gravitation;
			fprintf(fichier, "%f\n", reel);

		entier = (*systeme).modeDissipation;
			fprintf(fichier, "%d\n", entier);
		reel = (*systeme).dissipation;
			fprintf(fichier, "%f\n", reel);
		reel = (*systeme).pendule[0].dephasage;
			fprintf(fichier, "%f\n", reel);

		fclose(fichier);
		}

	return 0;
	}

int fichierLectureParametre(systemeT * systeme, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */
	float reel = 0;
	int entier = 0;
	//(void)graphe;

	char chemin[120] = "./donnees/enregistrement/parametre_";

	char * extension = ".sicf";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "r");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	le fichier donnees/enregistrement/parametre_%s.sicf est absent\n", nom);
		}
	else
		{
		// Initialisation du moteurs
			// Paramètres d'horloge
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseDt(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseChrono(&(*systeme).moteurs, reel);

			// Moteur périodique sur le premier pendule
		fscanf(fichier, "%d\n", &entier);
		moteursInitialiseGenerateur(&(*systeme).moteurs, entier);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseAmplitude(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseFrequence(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialisePhi(&(*systeme).moteurs, reel);

			// Moteur courant Josephson
		fscanf(fichier, "%d\n", &entier);
		moteursInitialiseEtatJosephson(&(*systeme).moteurs, entier);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseCourantJosephson(&(*systeme).moteurs, reel);

			// Moteur créateur de Fluxon
		fscanf(fichier, "%d\n", &entier);
		moteursInitialiseFluxon(&(*systeme).moteurs, entier);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseDeltaDephasage(&(*systeme).moteurs, reel);
		fscanf(fichier, "%f\n", &reel);
		moteursInitialiseDephasage(&(*systeme).moteurs, reel);


		// Initialisation de la chaîne
			// Caractéristiques
		fscanf(fichier, "%d\n", &entier);
		systemeInitialiseNombre(systeme, entier);
		fscanf(fichier, "%d\n", &entier);
		systemeInitialiseEquation(systeme, entier);

		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseDephasage(systeme, reel);
		fscanf(fichier, "%d\n", &entier);
		systemeInitialiseLibreFixe(systeme, entier);

			// Paramètres physiques
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseMasseDroite(systeme, reel);
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseMasseGauche(systeme, reel);
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseLongueur(systeme, reel);
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseCouplage(systeme, reel);
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseGravitation(systeme, reel);
		fscanf(fichier, "%d\n", &entier);
		systemeInitialiseModeDissipation(systeme, entier);
		fscanf(fichier, "%f\n", &reel);
		systemeInitialiseDissipation(systeme, reel);

		fscanf(fichier, "%f\n", &reel); // Déphasage du premier pendule
		(*systeme).pendule[0].dephasage = reel;

		fclose(fichier);

		}

	return 0;
	}

int fichierEcriturePosition(systemeT * systeme, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */

	char chemin[120] = "./donnees/enregistrement/position_";

	char * extension = ".sicf";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "w");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	Vérifier le répertoire donnees/enregistrement\n");
		}
	else
	   	{
	    double ancien, actuel;
    	int i;

	    for(i=0;i<(*systeme).nombre;i++)
	    	{
	    	//penduleInitialisePosition(&(*systeme).pendule[i], 0.0, 0.0);
	    	ancien = (*systeme).pendule[i].ancien;
	    	actuel =(*systeme).pendule[i].nouveau;
	    	fprintf(fichier, "%f %f\n", ancien, actuel);
	    	}
	    fclose(fichier);
		}

	return 0;
	}

int fichierLecturePosition(systemeT * systeme, char * nom)
	{
	FILE *fichier; /* pointeur sur FILE */

	char chemin[120] = "./donnees/enregistrement/position_";

	char * extension = ".sicf";

	strncat(chemin, nom, 20);

	strncat(chemin, extension, 40);

	fichier = fopen(chemin, "r");

	if(fichier == NULL)
		{
		printf("Erreur d'ouverture du fichier d'enregistrement\n");
		printf("	le fichier donnees/enregistrement/position_%s.sicf est absent\n", nom);
		}
	else
		{
		float ancien, actuel;
	    int i;
		for(i=0;i<(*systeme).nombre;i++)
			{
			ancien = 0;
			actuel = 0;
			fscanf(fichier, "%f %f\n", &ancien, &actuel);
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			}
		fclose(fichier);
		}

	return 0;
	}

void fichierFonction(systemeT * systeme, int numero)
	{
	switch (numero)
		{
		case 0: // Touche A
			fichierFonctionNulle(systeme);break;
		case 1: // Touche Z
			fichierFonctionSinus(systeme, 1);break;
		case 2: // Touche E
			fichierFonctionTriangle(systeme, 2);break;
		case 3: // Touche R
			fichierFonctionTriangle(systeme, 3);break;
		case 4: // Touche T
			fichierFonctionTriangle(systeme, 4);break;
		case 5: // Touche Y
			fichierFonctionTriangle(systeme, 5);break;
		case 6: // Touche U
			fichierFonctionTriangle(systeme, 6);break;
		case 7: // Touche I
			fichierFonctionSinus(systeme, 7);break;
		case 8: // Touche O
			fichierFonctionSinus(systeme, 8);break;
		case 9: // Touche P
			fichierFonctionCarre(systeme, 9);break;
		case 10: // Touche Q
			fichierFonctionSinus(systeme, 1);break;
		case 11: // Touche S
			fichierFonctionSinus(systeme, 2);break;
		case 12: // Touche D
			fichierFonctionSinus(systeme, 3);break;
		case 13: // Touche F
			fichierFonctionSinus(systeme, 4);break;
		case 14: // Touche G
			fichierFonctionSinus(systeme, 5);break;
		case 15: // Touche H
			fichierFonctionCarre(systeme, 1);break;
		case 16: // Touche J
			fichierFonctionCarre(systeme, 2);break;
		case 17: // Touche K
			fichierFonctionCarre(systeme, 3);break;
		case 18: // Touche L
			fichierFonctionCarre(systeme, 4);break;
		case 19: // Touche M
			fichierFonctionCarre(systeme, 5);break;
		default:
			;
		}
	return;
	}

int fichierFonctionNulle(systemeT * systeme)
	{
	float ancien, actuel;
	int i;
	for(i=0;i<(*systeme).nombre;i++)
		{
		ancien = 0.0;
		actuel = 0.0;
		penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
		}

	return 0;
	}

int fichierFonctionTriangle(systemeT * systeme, int numero)
	{
	float ancien, actuel;
	int i;
	fichierFonctionNulle(systeme);
	switch (numero)
		{
		case 1:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/2;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
				}break;
		case 2:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/4;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/2-1-i], ancien, actuel);
				}break;
		case 3:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/8;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/4-1-i], ancien, actuel);
				}break;
		case 4:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/16;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/8-1-i], ancien, actuel);
				}break;
		case 5:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/32;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/16-1-i], ancien, actuel);
				}break;
		case 6:
			printf("Réinitialisation du système, numero = %d\n", numero);
			for(i=0;i<(*systeme).nombre/64;i++)
				{
				ancien = (float)(i*numero)/(float)(*systeme).nombre;
				actuel = ancien;
				penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
				penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre/64-1-i], ancien, actuel);
				}break;
		}

	return 0;
	}

int fichierFonctionCarre(systemeT * systeme, int numero)
	{
	float ancien, actuel;
	int i;
	fichierFonctionNulle(systeme);
	if(numero == 1)
		{
		printf("Réinitialisation du système, numero = 1\n");
		}
	else
		{
		printf("Réinitialisation du système, numero != 1\n");
		for(i=0;i<(*systeme).nombre/2;i++)
			{
			ancien = i*numero/(*systeme).nombre;
			actuel = ancien;
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
			}
		}

	return 0;
	}

int fichierFonctionSinus(systemeT * systeme, int numero)
	{
	float ancien, actuel;
	int i;
	fichierFonctionNulle(systeme);
	if(numero == 1)
		{
		printf("Réinitialisation du système, numero = 1\n");
		}
	else
		{
		printf("Réinitialisation du système, numero != 1\n");
		for(i=0;i<(*systeme).nombre/2;i++)
			{
			ancien = i*numero/(*systeme).nombre;
			actuel = ancien;
			penduleInitialisePosition(&(*systeme).pendule[i], ancien, actuel);
			penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1-i], ancien, actuel);
			}
		}

	return 0;
	}


///////////////////////////////////////////////////////////////////////////////////////////////
