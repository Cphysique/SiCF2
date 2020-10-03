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

#ifndef _GRAPHES_
#define _GRAPHES_

#include "../donnees/constantes.h"
#include <SDL2/SDL.h>

typedef struct GrapheT grapheT;
	struct GrapheT
		{
		SDL_Point point[NOMBRE_MAX];

		SDL_Color couleur;

		int graisse;	// Epaisseur du trait

		int nombre;	// Nombre de point

		int yZero;	// Positon de l'origine
		int xZero;	// Positon de l'origine

		int largeur;	// axe x
		int hauteur;	// axe y
		};

typedef struct GraphesT graphesT;
	struct GraphesT
		{
		grapheT corde;
		grapheT spectre;
		grapheT gauche;
		grapheT droite;
		};

		//fprintf(stderr, " Initialisation des couleurs et du nombre de points\n");
int grapheInitialise(grapheT * graphe, int nombre, int graisse, int r, int g, int b);

		//fprintf(stderr, " Initialisation des longueurs\n");
int graphesInitialiseLongueur(graphesT * graphes, int largeur, int hauteur);

		//fprintf(stderr, " Initialisation du nombre de points\n");
int graphesInitialiseNombre(graphesT * graphes, int nombre);

#endif
