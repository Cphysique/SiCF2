/*
Copyright septembre 2019, Stephan Runigo
runigo@free.fr
SiCP 2.4 simulateur de chaîne de pendules
Ce logiciel est un programme informatique servant à simuler l'équation
d'une chaîne de pendules et à en donner une représentation graphique.
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

#ifndef _MOTEURS_
#define _MOTEURS_

#include "../donnees/constantes.h"

typedef struct MoteursT moteursT;
	struct MoteursT
		{
			// Paramètres d'horloge
		float dt;			//	discrétisation du temps
		float chrono;		//	Somme des dt remis à zéro dans moteurs

			// Moteur périodique sur le premier pendule
		int generateur;		//	0:eteint, 1:sinus, 2:carre, 3:impulsion
		float amplitude;	//	Amplitude du moteur
		float frequence;	//	Fréquence du moteur
		float phi;			//	Phase

			// Moteur courant Josephson
		int etatJosephson;	//	État du moteur Josephson, 0 ou 1
		float courantJosephson;		//	Amplitude du courant josephson

			// Moteur créateur de Fluxon
		int fluxon;		// Activité du moteur fluxon
		float deltaDephasage;	// Valeur du dephasage à ajouter
		float dephasage;		// Valeur du dephasage ateint
		};

	//	Initialisation

int moteursInitialiseDt(moteursT * moteurs, float dt);
int moteursInitialiseChrono(moteursT * moteurs, float chrono);

int moteursInitialiseGenerateur(moteursT * moteurs, int generateur);
int moteursInitialiseAmplitude(moteursT * moteurs, float amplitude);
int moteursInitialiseFrequence(moteursT * moteurs, float frequence);
int moteursInitialisePhi(moteursT * moteurs, float phi);

int moteursInitialiseEtatJosephson(moteursT * moteurs, int etat);
int moteursInitialiseCourantJosephson(moteursT * moteurs, float courant);

int moteursInitialiseFluxon(moteursT * moteurs, int fluxon);
int moteursInitialiseDeltaDephasage(moteursT * moteurs, float deltaDephasage);
int moteursInitialiseDephasage(moteursT * moteurs, float dephasage);


	//	Évolution des moteurs

float moteursGenerateur(moteursT * m);
float moteurJaugeZero(moteursT * m);

	//	Réglage des paramètres

//void moteursChangeEtatJosephson(moteursT * moteurs, int etat);

void moteursSensJosephson(moteursT * moteurs, int signe);
int moteursChangeJosephson(moteursT * m, float facteur);
int moteursChangeJosephsonMoyenne(moteursT * m);	// Réglage du moteur josephson

void moteursChangeFrequence(moteursT * m, float facteur);
void moteursChangeAmplitude(moteursT * m, float facteur);
void moteursChangeGenerateur(moteursT * m, int i);

int moteurChangeFluxon(moteursT * m, int fluxon);
int moteurFinFluxon(moteursT * moteurs);
int moteurFluxon(moteursT * moteurs);

void moteursAfficheHorloge(moteursT * m);


#endif
