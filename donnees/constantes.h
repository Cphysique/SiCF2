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

#ifndef _CONSTANTES_
#define _CONSTANTES_

//#include "unistd.h"

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <time.h>

//#define PI 3.14159265358979323846264338327950288419716939937510582
//#define PI 3.1415926535897932384626433832795
#define PI 3.14159265359
#define DEUXPI 6.28318530718



			//	PARAMÈTRES GRAPHIQUES


	//  TAILLE IMPLICITE DE LA FENÊTRE
#define FENETRE_X 938
#define FENETRE_Y 680

	//	PARAMÈTRES DES CAPTEURS
#define GRAPHES 2 // Nombres de graphes

	//  NOMBRE DE COMMANDES
#define BOUTON_COMMANDES 16		// Nombres de petits boutons
#define ROTATIF_COMMANDES 7		// Nombre de boutons rotatifs

	//	PARAMÈTRES DES CAPTEURS

#define OBSERVABLES 4 // Nombres d'observables
#define CAPTEURS 6 // Nombres de capteurs
#define DUREE_CAPTEURS 128 // Nombre de points en mémoire

			//	PARAMÈTRES DE DISCRÉTISATION TEMPORELLE DU SYSTÈME

	//	DT * DUREE = TEMPS_AFFICHAGE => temps réel

#define TEMPS_AFFICHAGE 110	// Durée entre les affichages en ms

#define DUREE 100			// Nombre implicite d'incrémentation du système entre deux affichages.
#define DUREE_MAX 599		// Nombre maximal d'incrémentation du système entre deux affichages.

#define DT_MIN 0.00003		// Discrétisation minimale du temps
#define DT 0.0011			// Discrétisation implicite du temps
#define DT_MAX 0.003		// Discrétisation maximale du temps


	//	PARAMÈTRES DE LA CHAINE

#define NOMBRE_MIN 8 // Nombre minimal de pendules
//#define NOMBRE 64 // Nombre implicite de pendules
#define NOMBRE 256 // Nombre implicite de pendules
#define NOMBRE_MAX 1024 // Nombre maximal de pendules

#define ABSORPTION 2.1 // Facteur de l'extrémité absorbante

//#define SOLITON_MAX 19 // Nombre maximal de soliton
#define DEPHASAGE_MAX 49*DEUXPI // Déphasage maximal


	//	PARAMÈTRES CHAINE ET CORDE

#define MOYENNE_MAX 2.3 // Moyenne maximale
	// Utilisé dans systemeJauge(systeme * system)
	// normalise la moyenne du système à zéro

#define COUPLAGE_MAX 99 // Couplage maximal / nombre de pendule
#define COUPLAGE_MIN 0.099

#define GRAVITATION_MAX 77.7	// Gravitation maximale
#define GRAVITATION 9.81		// Gravitation implicite
#define GRAVITATION_MIN 0.07	// Gravitation minimale

#define MASSE_MAX 77.7	//	Masse maximale
#define MASSE 1.0		//	Masse implicite
#define MASSE_MIN 0.7	//	Masse minimale

#define LONGUEUR_MAX 1.0	//	Longueur maximale
#define LONGUEUR 1.0		//	Longueur implicite
#define LONGUEUR_MIN 1.0	//	Longueur minimale

#define DISSIPATION_MAX 333	//	Coeficient de frottement visqueux maximal
#define DISSIPATION_MIN 0.033	//	Valeur minimale

#define FREQUENCE_MAX 77	//	Valeur maximale de la fréquence du moteur
#define FREQUENCE_MIN 0.077	//	Valeur minimale de la fréquence du moteur

#define AMPLITUDE_MAX 7.7	//	Valeur maximale de l'amplitude du moteur
#define AMPLITUDE_MIN 0.0077	//	Valeur minimale de l'amplitude du moteur

#define JOSEPHSON_MAX 77.7	//	Valeur maximale de l'amplitude du courant josephson
#define JOSEPHSON_MIN 0.077	//	Valeur minimale de l'amplitude du courant josephson

#endif
