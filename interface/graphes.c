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

#include "graphes.h"

int grapheInitialiseAxeX(grapheT * graphe);

int graphesInitialiseLongueur(graphesT * graphes, int largeur, int hauteur)
	{
		//		Initialisation des longueurs des graphes

			//fprintf(stderr, "Réinitialisation de la taille des graphes\n");

			//	CORDE
	(*graphes).corde.xZero=0.052632*largeur;	// X0
	(*graphes).corde.yZero = 0.250000*hauteur; // Positon de l'origine
	(*graphes).corde.largeur=0.74*largeur;	// axe x
	(*graphes).corde.hauteur=0.430233*hauteur;	// axe y
	grapheInitialiseAxeX(&(*graphes).corde);


			//	SPECTRE COMPLET
	(*graphes).spectre.xZero=0.088565*largeur;	// Positon de l'origine
	(*graphes).spectre.yZero =0.681686*hauteur;
	(*graphes).spectre.largeur=0.325112*largeur;	// axe x
	(*graphes).spectre.hauteur=0.19*hauteur;	// axe y
	grapheInitialiseAxeX(&(*graphes).spectre);

			//	SPECTRE GAUCHE
	(*graphes).gauche.xZero=0.457399*largeur;	// X0
	(*graphes).gauche.yZero= 0.681686 * hauteur;	// Y0
	(*graphes).gauche.largeur=0.325*largeur;	// axe x
	(*graphes).gauche.hauteur=0.213*hauteur;	// axe y
	grapheInitialiseAxeX(&(*graphes).gauche);

			//	SPECTRE DROIT
	(*graphes).droite.xZero=0.457399*largeur;	// X0
	(*graphes).droite.yZero= 0.681686 * hauteur;	// Y0
	(*graphes).droite.largeur=0.325*largeur;	// axe x
	(*graphes).droite.hauteur=0.213*hauteur;	// axe y
	grapheInitialiseAxeX(&(*graphes).droite);

	return 0;
	}

int graphesInitialiseNombre(graphesT * graphes, int nombre)
	{
		//fprintf(stderr, " Initialisation du nombre de points\n");

	(*graphes).corde.nombre = nombre;
	(*graphes).spectre.nombre = nombre;
	(*graphes).gauche.nombre = nombre/2;
	(*graphes).droite.nombre = nombre/2;

	grapheInitialiseAxeX(&(*graphes).corde);
	grapheInitialiseAxeX(&(*graphes).spectre);
	grapheInitialiseAxeX(&(*graphes).gauche);
	grapheInitialiseAxeX(&(*graphes).droite);

	return 0;
	}



int grapheInitialiseAxeX(grapheT * graphe)
	{
		//		Initialisation de l'axe x du graphe


	int i;
	float dx=(float)(*graphe).largeur/(float)(*graphe).nombre;
	for(i=0;i<(*graphe).nombre;i++)
		{
		(*graphe).point[i].x=(*graphe).xZero + (int)(i*dx);
		}

	return 0;
	}

int grapheInitialise(grapheT * graphe, int nombre, int graisse, int r, int g, int b)
	{
		//		Initialisation du graphe

		//fprintf(stderr, " Initialisation des couleurs et du nombre de points\n");
	//grapheInitialiseTaille(graphe, 0, 0, FENETRE_X, FENETRE_Y);

	int i;

	for(i=0;i<NOMBRE_MAX;i++)
		{
		(*graphe).point[i].x=0;
		(*graphe).point[i].y=0;
		}

		//fprintf(stderr, " Initialisation des couleurs\n");
	(*graphe).couleur.r = r;
	(*graphe).couleur.g = g;
	(*graphe).couleur.b = b;
	(*graphe).couleur.a = 255;

	(*graphe).nombre = nombre; // Nombre de point
	(*graphe).graisse = graisse; // Epaisseur du trait

	return 0;
	}

//////////////////////////////////////////////////////////////////
