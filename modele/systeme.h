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

#ifndef _SYSTEME_
#define _SYSTEME_

#include "pendule.h"
#include "moteurs.h"

typedef struct SystemeT systemeT;
	struct SystemeT
		{
		penduleT pendule[NOMBRE_MAX];	//	Le système est un tableau de pendule

		int nombre;						// Nombre de pendules

		moteursT moteurs;				// Moteur périodique et courant josephson

		int equation;		//	Pendule=1, Harmonique=2, Corde=3, Dioptre=4

		float dephasage;	//	Déphasage entre les limites
		int libreFixe;		//	 0 : périodiques 1 : libres, 2 : fixes, 
							//	 3 libre-fixe, 4 fixe-libre

		float masseDroite;		//	Masse des pendules à droite
		float masseGauche;		//	Masse des pendules à gauche

		float longueur;		//	Longueur des pendules
		float couplage;		//	Masse des pendules

		float dissipation;	//	Valeur de la dissipation (mémorisation)
		int modeDissipation;	//	0 : nulle 1 : uniforme, 2 : extrémité absorbante.

		float gravitation;	//	Valeur de la gravitation

		};

	//	Initialisation des paramètres
int systemeInitialiseNombre(systemeT * systeme, int nombre);
int systemeInitialiseEquation(systemeT * systeme, int equation);

int systemeInitialiseDephasage(systemeT * systeme, float dephasage);
int systemeInitialiseLibreFixe(systemeT * systeme, int libreFixe);

int systemeInitialiseMasseDroite(systemeT * systeme, float masse);
int systemeInitialiseMasseGauche(systemeT * systeme, float masse);
int systemeInitialiseLongueur(systemeT * systeme, float longueur);

int systemeInitialiseCouplage(systemeT * systeme, float couplage);
int systemeInitialiseDissipation(systemeT * systeme, float dissipation);
int systemeInitialiseModeDissipation(systemeT * systeme, int modeDissipation);

int systemeInitialiseGravitation(systemeT * systeme, float gravitation);

int systemeInitialise(systemeT * systeme);

	// Réinitialise la position des pendules
int systemeInitialisePosition(systemeT * systeme, int forme);

	// Evolution temporelle du système, "duree" cycle d'évolution
int systemeEvolution(systemeT * systeme, int duree);

	// Affiche les paramètres du système
int systemeAffiche(systemeT * systeme);

#endif
