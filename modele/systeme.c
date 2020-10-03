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

#include "systeme.h"

void systemeInitialisePendule(systemeT * systeme);
void systemeCouplage(systemeT * systeme);
void systemeInertie(systemeT * systeme);
void systemeIncremente(systemeT * systeme);
void systemeInitialiseLimiteInfini(systemeT * systeme);
void systemeChangeLimite(systemeT * systeme);
void systemeFormeDioptre(systemeT * systeme, float facteur);
float systemeMoteur(systemeT * systeme);

// normalise le premier pendule
void systemeJaugeZero(systemeT * systeme);
// normalise la moyenne du système à zéro
void systemeJauge(systemeT * systeme);
double systemeMoyenne(systemeT * systeme);


/*----------------  INITIALISATION  -------------------*/


int systemeInitialiseLibreFixe(systemeT * systeme, int libreFixe)
	{
	if(libreFixe>=0 && libreFixe<=4)
		{
		(*systeme).libreFixe = libreFixe;
		printf("(*systeme).libreFixe = %d\n", (*systeme).libreFixe);
		return 0;
		}
	else
		{
		(*systeme).libreFixe = 1;
		printf("ERREUR systemeInitialiseLibreFixe(%d) (*systeme).libreFixe = %d\n", libreFixe, (*systeme).libreFixe);
		}
	return 1;
	}

int systemeInitialiseNombre(systemeT * systeme, int nombre)
	{
	if(nombre>=NOMBRE_MIN && nombre<=NOMBRE_MAX)
		{
		(*systeme).nombre = nombre;
		printf("(*systeme).nombre = %d\n", (*systeme).nombre);
		return 0;
		}
	else
		{
		(*systeme).nombre = NOMBRE;
		printf("ERREUR systemeInitialiseNombre(%d) (*systeme).nombre = %d\n", nombre, (*systeme).nombre);
		}
	return 1;
	}

int systemeInitialiseGravitation(systemeT * systeme, float gravitation)
	{
	if(gravitation>=GRAVITATION_MIN && gravitation<=GRAVITATION_MAX)
		{
		(*systeme).gravitation = gravitation;
		printf("(*systeme).gravitation = %f\n", (*systeme).gravitation);
		return 0;
		}
	else
		{
		(*systeme).gravitation = GRAVITATION;
		printf("ERREUR systemeInitialiseGravitation(%f) (*systeme).gravitation = %f\n", gravitation, (*systeme).gravitation);
		}
	return 1;
	}

int systemeInitialiseMasseDroite(systemeT * systeme, float masse)
	{
	if(masse>=MASSE_MIN && masse<=MASSE_MAX)
		{
		(*systeme).masseDroite = masse;
		printf("(*systeme).masseDroite = %f\n", (*systeme).masseDroite);
		return 0;
		}
	else
		{
		(*systeme).masseDroite = MASSE;
		printf("ERREUR systemeInitialiseMasse(%f) ; ", masse);
		printf("(*systeme).masseDroite = %f\n", (*systeme).masseDroite);
		}

	return 1;
	}

int systemeInitialiseMasseGauche(systemeT * systeme, float masse)
	{
	if(masse>=MASSE_MIN && masse<=MASSE_MAX)
		{
		(*systeme).masseGauche = masse;
		printf("(*systeme).masseGauche = %f\n", (*systeme).masseGauche);
		return 0;
		}
	else
		{
		(*systeme).masseGauche = MASSE;
		printf("ERREUR systemeInitialiseMasse(%f) ; ", masse);
		}

	return 1;
	}

int systemeInitialiseLongueur(systemeT * systeme, float longueur)
	{
	if(longueur>=LONGUEUR_MIN && longueur<=LONGUEUR_MAX)
		{
		(*systeme).longueur = longueur;
		printf("(*systeme).longueur = %f\n", (*systeme).longueur);
		return 0;
		}
	else
		{
		(*systeme).longueur = LONGUEUR;
		printf("ERREUR systemeInitialiseLongueur(%f) (*systeme).longueur = %f\n", longueur, (*systeme).longueur);
		}
	return 1;
	}

int systemeInitialiseDissipation(systemeT * systeme, float dissipation)
	{
	if(dissipation>DISSIPATION_MIN && dissipation<DISSIPATION_MAX)
		{
		(*systeme).dissipation = dissipation;
		printf("(*systeme).dissipation = %f\n", (*systeme).dissipation);
		return 0;
		}
	else
		{
		(*systeme).dissipation = exp((log(DISSIPATION_MIN)+log(DISSIPATION_MAX))/2);
		printf("ERREUR systemeInitialiseDissipation(%f) (*systeme).dissipation = %f\n", dissipation, (*systeme).dissipation);
		}
	return 1;
	}

int systemeInitialiseModeDissipation(systemeT * systeme, int modeDissipation)
	{
	if(modeDissipation>=0 && modeDissipation<=2)
		{
		(*systeme).modeDissipation = modeDissipation;
		printf("(*systeme).modeDissipation = %d\n", (*systeme).modeDissipation);
		return 0;
		}
	else
		{
		(*systeme).modeDissipation = 0;
		printf("ERREUR systemeInitialiseModeDissipation(%d) (*systeme).modeDissipation = %d\n", modeDissipation, (*systeme).modeDissipation);
		}
	return 1;
	}

int systemeInitialiseCouplage(systemeT * systeme, float couplage)
	{
	float couplageReduit = 0;
	int nombre = (*systeme).nombre;

	if(nombre < NOMBRE_MIN || nombre > NOMBRE_MAX)
		{
		nombre = NOMBRE;
		printf("ERREUR systemeInitialise() (*systeme).nombre = %d\n", (*systeme).nombre);
		}

	couplageReduit = couplage / nombre;

	if(couplageReduit < COUPLAGE_MAX && couplageReduit > COUPLAGE_MIN)
		{
		(*systeme).couplage = couplage;
		printf("(*systeme).couplage = %f\n", (*systeme).couplage);
		return 0;
		}
	else
		{
		(*systeme).couplage = nombre * exp((log(COUPLAGE_MIN)+log(COUPLAGE_MAX))/2);
		printf("ERREUR systemeInitialiseCouplage(%f) (*systeme).couplage = %f\n", couplage, (*systeme).couplage);
		}
	return 1;
	}

int systemeInitialiseDephasage(systemeT * systeme, float dephasage)
	{
	if(dephasage>=-DEPHASAGE_MAX && dephasage<DEPHASAGE_MAX)
		{
		(*systeme).dephasage = dephasage;
		printf("(*systeme).dephasage = %f\n", (*systeme).dephasage);
		return 0;
		}
	else
		{
		(*systeme).dephasage = 0;
		printf("ERREUR systemeInitialise(%f) (*systeme).dephasage = %f\n", dephasage, (*systeme).dephasage);
		}
	return 1;
	}

int systemeInitialiseEquation(systemeT * systeme, int equation)
	{
	if(equation>=1 && equation<=4)
		{
		(*systeme).equation = equation;
		printf("(*systeme).equation = %d\n", (*systeme).equation);
		return 0;
		}
	else
		{
		(*systeme).equation = 1;
		printf("ERREUR systemeInitialiseEquation(%d) (*systeme).equation = %d\n", equation, (*systeme).equation);
		}
	return 1;
	}

int systemeInitialise(systemeT * systeme)
	{
	// Initialisation des pendules
	systemeInitialisePendule(systeme);

	// Extrémité absorbante
	systemeInitialiseLimiteInfini(systeme);

	return 0;
	}

int systemeInitialisePosition(systemeT * systeme, int forme)
	{
	int i;

		switch(forme)	//	
			{
			case 0: // Initialise
				for(i=0;i<(*systeme).nombre;i++)
					{
					penduleInitialisePosition(&(*systeme).pendule[i], 0.0, 0.0);
					};break;
			case 1: // Initialise
				for(i=0;i<(*systeme).nombre;i++)
					{
					penduleInitialisePosition(&(*systeme).pendule[i], 0.3*sin(i*0.1), 0.301*sin(i*0.1));
					};break;
			default:
				;
			}
	return 0;
	}

void systemeInitialisePendule(systemeT * systeme)
	{
	float m=(*systeme).masseGauche;
	float l=(*systeme).longueur;
	float d=(*systeme).dissipation;
	float c=(*systeme).couplage;
	float g=(*systeme).gravitation;
	float t=(*systeme).moteurs.dt;

	int i;

	for(i=0;i<(*systeme).nombre;i++)
		{
		penduleInitialiseParametre(&(*systeme).pendule[i], m, l, d);
		penduleInitialiseExterieur(&(*systeme).pendule[i], c, g, t);
		penduleInitialisePosition(&(*systeme).pendule[i], 0.0, 0.0);
		penduleInitialiseDephasage(&(*systeme).pendule[i], 0.0);
		}

	penduleInitialiseDephasage(&(*systeme).pendule[0], (*systeme).dephasage);

	return;
	}

void systemeInitialiseLimiteInfini(systemeT * systeme)
	{
	int i;

	for(i=0;i<(*systeme).nombre;i++)
		{
		(*systeme).pendule[i].absorbance = 0.0;
		}

	for(i=1;i<(*systeme).nombre/6;i++)
		{
		(*systeme).pendule[(*systeme).nombre-i].absorbance = 1.0-(float)i/((float)(*systeme).nombre/6.0);
		}

	return;
	}


/*----------------JAUGE ET NORMALISATION-------------------*/

// normalise le premier pendule
void systemeJaugeZero(systemeT * systeme)
	{
	float position = (*systeme).pendule[0].nouveau;
	float jauge;

	//fprintf(stderr, "\nEntrée systemeJaugeZero, position = %f\n", position);
	//fprintf(stderr, "\nEntrée systemeJaugeZero, position/DEUXPI = %f\n", position/DEUXPI);

	jauge = -DEUXPI*(int)(position/DEUXPI);
	if(jauge>PI || jauge<PI)
		{
		int i;
		for(i=0;i<(*systeme).nombre;i++)
			{
			penduleJauge(&(*systeme).pendule[i], jauge);
			}
		}


	//fprintf(stderr, "Moyenne = %f\n", systemeMoyenne(systeme));
	//fprintf(stderr, "systemeJaugeZero, sortie\n\n");
	return;
	}


// normalise la moyenne du système à zéro
void systemeJauge(systemeT * systeme)
	{
	double moyenne = systemeMoyenne(systeme);
	if(moyenne>(MOYENNE_MAX))
		{
		int i;
		for(i=0;i<(*systeme).nombre;i++)
			{
			penduleJauge(&(*systeme).pendule[i], -MOYENNE_MAX);
			}
		fprintf(stderr, "Moyenne = %f\n", moyenne);
		}
	if(moyenne<(-MOYENNE_MAX))
		{
		int i;
		for(i=0;i<(*systeme).nombre;i++)
			{
			penduleJauge(&(*systeme).pendule[i], MOYENNE_MAX);
			}
		fprintf(stderr, "Moyenne = %f\n", moyenne);
		}
	return;
	}

double systemeMoyenne(systemeT * systeme)
	{
	double moyenne = 0.0;

	int i;
	for(i=0;i<(*systeme).nombre;i++)
		{
		moyenne = moyenne + (*systeme).pendule[i].nouveau;
		}

	return ( moyenne / (*systeme).nombre );
	}

/*------------------------  ÉVOLUTION TEMPORELLE  -------------------------*/

int systemeEvolution(systemeT * systeme, int duree)
	{
	int i;

	//	Fait évoluer le système pendant duree*dt
	for(i=0;i<duree;i++)
		{
		//	Évolution élémentaire
		systemeCouplage(systeme);
		systemeInertie(systeme);
		systemeIncremente(systeme);
		}

	//	Limite la valeur des paramètres croissants
	if((*systeme).moteurs.generateur==0)
		{
		//	Rapproche la position du premier pendule de zéro
		systemeJaugeZero(systeme);
		}
	else
		{
		//	Rapproche les compteurs des moteurs de zéro
		moteurJaugeZero(&(*systeme).moteurs);
		}
	return i;
	}

/*
int systemeEvolution(systemeT * systeme, int duree)
	{//	Fait évoluer le système pendant duree * dt
	int i;
	for(i=0;i<duree;i++)
		{
		systemeCouplage(systeme);
		systemeInertie(systeme);
		systemeIncremente(systeme);
		}
	systemeJaugeZero(systeme);
	return 0;
	}
*/

void systemeCouplage(systemeT * systeme)
	{//	Calcul des forces de couplage

  // SiCF-1.0 inaugure penduleCouplage(m0, m0, m1)
  // nécessitant un dephasage nul et traitant l'extrémité libre
	int libreFixe = (*systeme).libreFixe;

	int i;
	for(i=1;i<((*systeme).nombre-1);i++)
		{
		penduleCouplage(&(*systeme).pendule[i-1], &(*systeme).pendule[i], &(*systeme).pendule[i+1]);
		}

  if(libreFixe!=0)
    {
    //penduleInitialiseDephasage(&(*systeme).pendule[1], 0.0);
  	penduleCouplage(&(*systeme).pendule[0], &(*systeme).pendule[0], &(*systeme).pendule[1]);
	  penduleCouplage(&(*systeme).pendule[(*systeme).nombre-2], &(*systeme).pendule[(*systeme).nombre-1], &(*systeme).pendule[(*systeme).nombre-1]);
	  }
  else // Limites périodiques
    {
  	penduleCouplage(&(*systeme).pendule[(*systeme).nombre-1], &(*systeme).pendule[0], &(*systeme).pendule[1]);
	  penduleCouplage(&(*systeme).pendule[(*systeme).nombre-2], &(*systeme).pendule[(*systeme).nombre-1], &(*systeme).pendule[0]);
	  }

	return;
	}

void systemeInertie(systemeT * systeme)
	{//	Principe d'inertie applique au système

  // Version SiCF-1.0, extrémité moteurs fixe.

	int equation = (*systeme).equation;
	int libreFixe = (*systeme).libreFixe;
	int etatMoteur = (*systeme).moteurs.generateur;
	float courantJosephson = (*systeme).moteurs.courantJosephson * (*systeme).moteurs.dt * (*systeme).moteurs.dt * (*systeme).moteurs.etatJosephson;

	float moteurs = moteursGenerateur(&(*systeme).moteurs);

				// Cas du premier et du dernier pendule

			//  0 : periodiques 1 : libres, 2 : fixes, 3 libre-fixe, 4 fixe-libre

	if (libreFixe==0 || libreFixe==1 || libreFixe==3)
		{
		penduleInertie(&(*systeme).pendule[0], equation, courantJosephson);
		}
	else
		{
		penduleInitialisePosition(&(*systeme).pendule[0], 0.0, 0.0);
		}
	if (libreFixe==0 || libreFixe==1 || libreFixe==4)
		{
		penduleInertie(&(*systeme).pendule[(*systeme).nombre-1], equation, courantJosephson);
		}
	else
		{
		penduleInitialisePosition(&(*systeme).pendule[(*systeme).nombre-1], (*systeme).pendule[(*systeme).nombre-1].dephasage, (*systeme).pendule[(*systeme).nombre-1].dephasage);
		}

	if(etatMoteur!=0) // moteurs allumé
		{
		penduleInitialisePosition(&(*systeme).pendule[0], moteurs, moteurs);
		}
	/*else // SiCF-1.0 : extrémité moteurs fixe
		{
		penduleInitialisePosition(&(*systeme).pendule[0], 0, 0);
		}*/

						// Cas des autres pendules
	int i;
	for(i=1;i<((*systeme).nombre-1);i++)
		{
		penduleInertie(&((*systeme).pendule[i]), (*systeme).equation, courantJosephson);
		}
	return;
	}

void systemeIncremente(systemeT * systeme)
	{//	incremente l'horloge, l'ancien et l'actuel etat du système

	//(*systeme).moteurs.horloge = (*systeme).moteurs.horloge + (*systeme).moteurs.dt;
	(*systeme).moteurs.chrono = (*systeme).moteurs.chrono + (*systeme).moteurs.dt;

	int i;
	for(i=0;i<(*systeme).nombre;i++)
		{
		penduleIncremente(&((*systeme).pendule[i]));
		}

	return;
	}

int systemeAffiche(systemeT * systeme)
	{// Affichage de la position et des parametres
	printf("\nParamètres système\n");
	printf("	Couplage entre les pendules	%4.3f\n", (*systeme).couplage);
	printf("	Longueur des pendules		%4.3f\n",(*systeme).longueur);
	printf("	Intensité de la gravitation	%4.3f\n",(*systeme).gravitation);
	printf("	Masse des pendules à droite : %4.3f, à gauche : %4.3f\n",(*systeme).masseDroite,(*systeme).masseGauche);
	printf("	Masse des pendules \n");
	printf("	Nombre de pendules	%d\n", (*systeme).nombre);
	/*	int equation;		//	Pendule=1, Harmonique=2, Corde=3, Dioptre=4
		float dephasage;	//	déphasage entre les limites
		int libreFixe;		// 0 : périodiques 1 : libres, 2 : fixes, 
	*/					//		3 libre-fixe, 4 fixe-libre
	return 0;
	}

//////////////////////////////////////////////////////////////////////
