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

#include "moteurs.h"

void moteursAffiche(moteursT * moteurs);
void moteursInverseGenerateur(moteursT * moteurs);
void moteursImpulsion(moteursT * moteurs);
int moteurInitialiseFluxon(moteursT * m, int fluxon);

/*----------------  INITIALISATION  -------------------*/


/*----------------  INITIALISATION  -------------------*/

int moteursInitialiseDt(moteursT * moteurs, float dt)
	{
	if(dt>=DT_MIN && dt<=DT_MAX)
		{
		(*moteurs).dt = dt;
		printf("(*moteurs).dt = %f\n", (*moteurs).dt);
		return 0;
		}
	else
		{
		(*moteurs).dt = DT;
		printf("ERREUR moteursInitialiseDt(%f) (*moteurs).dt = %f\n", dt, (*moteurs).dt);
		}
	return 1;
	}


int moteursInitialiseChrono(moteursT * moteurs, float chrono)
	{
	(*moteurs).chrono = chrono;
	printf("(*moteurs).chrono = %f\n", (*moteurs).chrono);
	return 0;
	}


int moteursInitialiseCourantJosephson(moteursT * moteurs, float courantJosephson)
	{
	float courant=courantJosephson;
	
	if(courant<0)
		{
		courant = -courant;
		}
	if(courant>=JOSEPHSON_MIN && courant<=JOSEPHSON_MAX)
		{
		(*moteurs).courantJosephson = courantJosephson;
		printf("(*moteurs).courantJosephson = %f\n", (*moteurs).courantJosephson);
		return 0;
		}
	else
		{
		(*moteurs).courantJosephson = exp((log(JOSEPHSON_MIN)+log(JOSEPHSON_MAX))/2);
		printf("ERREUR moteursInitialiseCourant(%f) (*moteurs).courantJosephson = %f\n", courantJosephson, (*moteurs).courantJosephson);
		}
	return 1;
	}

/*
int moteursInitialiseEtatJosephson(moteursT * moteurs, int etatJosephson)
	{
	if( etatJosephson>=JOSEPHSON_MIN &&  etatJosephson<=JOSEPHSON_MAX)
		{
		(*moteurs).etatJosephson =  etatJosephson;
		printf("(*moteurs).etatJosephson = %d\n", (*moteurs).etatJosephson);
		return 0;
		}
	else
		{
		(*moteurs).courantJosephson = exp((log(JOSEPHSON_MIN)+log(JOSEPHSON_MAX))/2);
		printf("ERREUR moteursInitialiseJosephson(%d) (*moteurs).etatJosephson = %d\n", etatJosephson, (*moteurs).etatJosephson);
		}
	return 1;
	}
*/

int moteursInitialiseGenerateur(moteursT * moteurs, int generateur)
	{
	if(generateur>=0 && generateur<=3)
		{
		(*moteurs).generateur = generateur;
		printf("(*moteurs).generateur = %d\n", (*moteurs).generateur);
		return 0;
		}
	else
		{
		(*moteurs).generateur = 0;
		printf("ERREUR moteursInitialiseGenerateur(%d) (*moteurs).generateur = %d\n", generateur, (*moteurs).generateur);
		}
	return 1;
	}


int moteursInitialiseAmplitude(moteursT * moteurs, float amplitude)
	{
	if(amplitude>=AMPLITUDE_MIN && amplitude<=AMPLITUDE_MAX)
		{
		(*moteurs).amplitude = amplitude;
		printf("(*moteurs).amplitude = %f\n", (*moteurs).amplitude);
		return 0;
		}
	else
		{
		(*moteurs).amplitude = exp((log(AMPLITUDE_MIN)+log(AMPLITUDE_MAX))/2);
		printf("ERREUR moteursInitialiseAmplitude(%f) (*moteurs).amplitude = %f\n", amplitude, (*moteurs).amplitude);
		}
	return 1;
	}

int moteursInitialiseFrequence(moteursT * moteurs, float frequence)
	{
	if(frequence>=FREQUENCE_MIN && frequence<=FREQUENCE_MAX)
		{
		(*moteurs).frequence = frequence;
		printf("(*moteurs).frequence = %f\n", (*moteurs).frequence);
		return 0;
		}
	else
		{
		(*moteurs).frequence = exp((log(FREQUENCE_MIN)+log(FREQUENCE_MAX))/2);
		printf("ERREUR (*moteurs).frequence = %f\n", (*moteurs).frequence);
		}
	return 1;
	}

int moteursInitialisePhi(moteursT * moteurs, float phi)
	{
	if(phi>=-DEPHASAGE_MAX && phi<=DEPHASAGE_MAX)
		{
		(*moteurs).phi = phi;
		printf("(*moteurs).phi = %f\n", (*moteurs).phi);
		return 0;
		}
	else
		{
		(*moteurs).amplitude = 0.0;
		printf("ERREUR moteursInitialise(%f) (*moteurs).phi = %f\n", phi, (*moteurs).phi);
		}
	return 1;
	}
int moteursInitialiseDeltaDephasage(moteursT * moteurs, float deltaDephasage)
	{
	if(deltaDephasage>=-DEUXPI && deltaDephasage<=DEUXPI)
		{
		(*moteurs).deltaDephasage = deltaDephasage;
		printf("(*moteurs).deltaDephasage = %f\n", (*moteurs).deltaDephasage);
		return 0;
		}
	else
		{
		(*moteurs).deltaDephasage = 0;
		printf("ERREUR moteursInitialiseDeltaDephasage(%f) (*moteurs).deltaDephasage = %f\n", deltaDephasage, (*moteurs).deltaDephasage);
		}
	return 1;
	}
int moteursInitialiseFluxon(moteursT * moteurs, int fluxon)
	{
	if(fluxon>=0 && fluxon<=1)
		{
		(*moteurs).fluxon = fluxon;
		printf("(*moteurs).fluxon = %d\n", (*moteurs).fluxon);
		return 0;
		}
	else
		{
		(*moteurs).fluxon = 0;
		printf("ERREUR moteursInitialiseFluxon(%d) (*moteurs).fluxon = %d\n", fluxon, (*moteurs).fluxon);
		}
	return 1;
	}

int moteursInitialiseDephasage(moteursT * moteurs, float dephasage)
	{
	if(dephasage>-DEUXPI*2 && dephasage<DEUXPI*2)
		{
		(*moteurs).dephasage = dephasage;
		printf("(*moteurs).dephasage = %f\n", (*moteurs).dephasage);
		return 0;
		}
	else
		{
		(*moteurs).dephasage = 0;
		printf("ERREUR moteursInitialiseDephasage(%f) (*moteurs).dephasage = %f\n", dephasage, (*moteurs).dephasage);
		}
	return 1;
	}
/*
int moteursInitialise(moteursT * moteurs, float int )
	{
	if(>_MIN && <_MAX)
		{
		printf("Option dt valide, dt = %f\n", (*options).dt);
		return 0;
		}
	else
		{
		}
	return 1;
	}
int moteursInitialise(moteursT * moteurs, float int )
	{
	if(dt>DT_MIN && dt<DT_MAX)
		{
		printf("Option dt valide, dt = %f\n", (*options).dt);
		return 0;
		}
	else
		{
		}
	return 1;
	}
		// Initialisation du moteurs
		fscanf(fichier, "%f\n", &parametre);
		fscanf(fichier, "%f\n", &parametre);
		fscanf(fichier, "%f\n", &parametre);
		fscanf(fichier, "%f\n", &parametre);
		fscanf(fichier, "%f\n", &parametre);
		fscanf(fichier, "%f\n", &parametre);
		fscanf(fichier, "%f\n", &parametre);
		fscanf(fichier, "%f\n", &parametre);
		fscanf(fichier, "%f\n", &parametre);
		fscanf(fichier, "%f\n", &parametre);
		fscanf(fichier, "%f\n", &parametre);



		// Moteurs
		parametre = (*moteurs) .dt;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*moteurs) .chrono;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*moteurs) .courantJosephson;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*moteurs) .etatJosephson;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*moteurs) .generateur;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*moteurs) .amplitude;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*moteurs) .frequence;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*moteurs) .phi;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*moteurs) .deltaDephasage;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*moteurs) .fluxon;
			fprintf(fichier, "%f\n", parametre);
		parametre = (*moteurs) .dephasage;
			fprintf(fichier, "%f\n", parametre);


*/


int moteurChangeFluxon(moteursT * moteurs, int fluxon)
	{
	if(fluxon!=0)
		{
		moteurInitialiseFluxon(moteurs, fluxon);
		printf("moteurInitialiseFluxon(moteurs, fluxon)\n");
		}
	return 0;
	}

int moteurInitialiseFluxon(moteursT * moteurs, int fluxon)
	{
	(*moteurs).deltaDephasage = fluxon*DEUXPI * (*moteurs).dt * (*moteurs).frequence;
	(*moteurs).fluxon=1;
	(*moteurs).dephasage=0;
	return 0;
	}

int moteurFinFluxon(moteursT * moteurs)
	{
	(*moteurs).dephasage=0;
	(*moteurs).fluxon=0;
	return 0;
	}

int moteurFluxon(moteursT * moteurs)
	{
	if((*moteurs).fluxon==0)
		{
		return 0;
		}
	else
		{
		return 1;
		}
	return 0;
	}

float moteursGenerateur(moteursT * moteurs)
	{
			// retourne la position du générateur de signaux

	float amplitude;
	float phase;

	phase = (*moteurs).phi + DEUXPI * (*moteurs).frequence * (*moteurs).chrono;
	amplitude = (*moteurs).amplitude * sin(phase);

	if((*moteurs).generateur==3)
		{
		if(phase>2*PI) (*moteurs).generateur=0;
		}

	if((*moteurs).generateur==2)
		{
		if(amplitude>0) amplitude = (*moteurs).amplitude;
		else amplitude = - (*moteurs).amplitude;
		}

	return amplitude;
	}

float moteurJaugeZero(moteursT * moteurs)
	{
			// Normalise la phase et le chrono
	if((*moteurs).phi > DEUXPI)
		{
		do
			{
			//printf("(*moteurs).phi = %f\n",(*moteurs).phi);
			//(*moteurs).phi = (*moteurs).phi - ((int)((*moteurs).phi/DEUXPI))*DEUXPI;
			(*moteurs).phi = (*moteurs).phi - DEUXPI;
			}
		while((*moteurs).phi > DEUXPI);
		}
	else 
		{
			if((*moteurs).phi < - DEUXPI)
			{
			do
				{
				//printf("(*moteurs).phi = %f\n",(*moteurs).phi);
				//(*moteurs).phi = (*moteurs).phi - ((int)((*moteurs).phi/DEUXPI))*DEUXPI;
				(*moteurs).phi = (*moteurs).phi + DEUXPI;
				}
			while((*moteurs).phi < - DEUXPI);
			}
		}

	float phase = DEUXPI * (*moteurs).frequence * (*moteurs).chrono;
	if(phase > DEUXPI)
		{
		do
			{
			//printf("(*moteurs).frequence * (*moteurs).chrono = %f\n",phase);
			(*moteurs).chrono = (*moteurs).chrono - ( (int)(phase/DEUXPI) ) * 1.0/(*moteurs).frequence;
			}
		while((*moteurs).frequence * (*moteurs).chrono > 1.0);
		}
	else 
		{
		if(phase < - DEUXPI)
			{
			do
				{
				//printf("(*moteurs).frequence * (*moteurs).chrono = %f\n",phase);
				(*moteurs).chrono = (*moteurs).chrono - ( (int)(phase/DEUXPI) ) * 1.0/(*moteurs).frequence;
				}
			while((*moteurs).frequence * (*moteurs).chrono < - 1.0);
			}
		}

	return 0;
	}

void moteursChangeGenerateur(moteursT * moteurs, int i)

			// Change la forme du signal
			// 0 : éteint, -1 : allume-éteint, 1 : allume, 3 : impulsion
	{

	// Réinitialisation
	(*moteurs).chrono = 0.0;
	(*moteurs).phi = 0.0;

	switch(i)
		{
		case 0:	// désactive le moteurs
			(*moteurs).generateur=0;break;

		case 1:	// active le moteurs
			(*moteurs).generateur=1;break;

		case -1:	// active/désactive le moteurs
			moteursInverseGenerateur(moteurs);break;

		case 2:	// active le signal carré
			(*moteurs).generateur=2;break;

		case 3:	// Lance une impulsion
			moteursImpulsion(moteurs);break;

		default:
			;
		}

	printf("etat générateur %d\n", (*moteurs).generateur);

	return;
	}

void moteursImpulsion(moteursT * moteurs)

			// Initialise l'état impulsion
	{
	(*moteurs).generateur=3;
	(*moteurs).chrono=0.0;
	(*moteurs).phi=0.0;

	printf("impulsion\n");
	return;
	}

void moteursChangeFrequence(moteursT * moteurs, float facteur)

			//	Change la fréquence du signal
	{
	float phase;

	if((*moteurs).frequence * facteur < FREQUENCE_MAX && (*moteurs).frequence * facteur > FREQUENCE_MIN)
		{
		phase = (*moteurs).phi + DEUXPI * (*moteurs).frequence * (*moteurs).chrono;

		(*moteurs).frequence = (*moteurs).frequence * facteur;

		(*moteurs).phi = phase - DEUXPI * (*moteurs).frequence * (*moteurs).chrono;

		}
	else
		{
		printf("Fréquence limite atteinte. ");
		}
	printf("Fréquence générateur = %6.3f\n", (*moteurs).frequence);

	return;
	}

void moteursChangeAmplitude(moteursT * moteurs, float facteur)

			//	Change l'amplitude du signal
	{
	float amplitude = (*moteurs).amplitude * facteur;
	if(amplitude < AMPLITUDE_MAX && amplitude > AMPLITUDE_MIN)
		{
		(*moteurs).amplitude = (*moteurs).amplitude * facteur;
		}
	else
		{
		printf("Amplitude limite atteinte. ");
		}
	printf("Amplitude générateur = %6.3f\n", (*moteurs).amplitude);
	return;
	}

int moteursInitialiseEtatJosephson(moteursT * moteurs, int etat)
	{
	if(etat == 1) // Allume le courantJosephson Josephson
		{
		(*moteurs).etatJosephson = 1;
		}
	else // Eteint le courantJosephson Josephson
		{
		(*moteurs).etatJosephson = 0;
		}
	printf("(*moteurs).etatJosephson = %d\n", (*moteurs).etatJosephson);
	return 0;
	}

void moteursSensJosephson(moteursT * moteurs, int signe)
	{
	if((*moteurs).courantJosephson<0)
		{
		(*moteurs).courantJosephson=-(*moteurs).courantJosephson;
		}

	if(signe>0)
		{
		(*moteurs).courantJosephson = (*moteurs).courantJosephson;
		}
	else
		{
		(*moteurs).courantJosephson = - (*moteurs).courantJosephson;
		}

	return;
	}

int moteursChangeJosephson(moteursT * moteurs, float facteur)
	{
				// Règle la valeur du courantJosephson Josephson

	float courantJosephson = (*moteurs).courantJosephson * facteur;

	if(courantJosephson < 0) courantJosephson = -courantJosephson;

	if(courantJosephson <= JOSEPHSON_MAX && courantJosephson >= JOSEPHSON_MIN)
		{
		(*moteurs).courantJosephson = (*moteurs).courantJosephson * facteur;
		}
	else
		{
		printf("Courant Josephson limite atteint. ");
		}

	printf("Courant Josephson = %6.3f\n", (*moteurs).courantJosephson);

	return 0;
	}

int moteursChangeJosephsonMoyenne(moteursT * moteurs)
	{	// Réglage du moteurs etatJosephson à une amplitude moyenne
	moteursInitialiseCourantJosephson(moteurs, sqrt(JOSEPHSON_MAX * JOSEPHSON_MIN ));
	return 0;
	}

void moteursAfficheHorloge(moteursT * m)

			// 	Affiche les paramètres de l'horloge
	{
	//printf("(*moteurs).horloge = %6.3f\n", (*m).horloge);		//	Somme des dt
	printf("(*moteurs).chrono = %6.3f\n", (*m).chrono);		//	Remis à zéro

	return;
	}

void moteursAffiche(moteursT * moteurs)

			// 	Affiche la valeur des paramètres du moteurs
	{
	printf("courantJosephson Josephson = %6.3f\n", (*moteurs).etatJosephson / (*moteurs).dt / (*moteurs).dt);
	//printf("(*moteurs).horloge = %6.3f\n", (*moteurs).horloge);		//	Somme des dt
	printf("(*moteurs).chrono = %6.3f\n", (*moteurs).chrono);		//	Remis à zéro

	printf("(*moteurs).generateur = %d", (*moteurs).generateur);
	printf("  ( 0:eteint, 1:sinus, 2:carre, 3:impulsion )\n");
	printf("(*moteurs).amplitude = %6.3f\n", (*moteurs).amplitude);	//	Amplitude du moteurs
	printf("(*moteurs).frequence = %6.3f\n", (*moteurs).frequence);	//	Fréquence du moteurs
	printf("(*moteurs).phi = %6.3f\n", (*moteurs).phi);			//	Dephasage

	return;
	}

void moteursInverseGenerateur(moteursT * moteurs)
	{
	/*	Allume le générateur s'il est éteint,
			Éteint le générateur sinon		*/

	switch((*moteurs).generateur)
		{
		case 0:	// désactive le moteurs
			(*moteurs).generateur=1;break;

		case 1:	// active le moteurs
			(*moteurs).generateur=0;break;

		default:
			(*moteurs).generateur=0;
		} 
	return;
	}
//////////////////////////////////////////////////////////////////////////
