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

#include "donnees.h"

	//		Valeurs initiales des données physiques du simulateur,
	//						et création du système

	//		Valeur initiale et création du graphe

	//		Initialisation de la SDL


int donneesSysteme(systemeT * systeme, optionsT * options);
int donneesFourier(fourierT * fourier, optionsT * options);
int donneesGraphes(graphesT * graphes, optionsT * options);

int donneesControleur(controleurT * controleur)
	{

	(*controleur).sortie = 0;	// Sortie de SiCP si <> 0
	(*controleur).appui = 0;	// Appuie sur la souris

		//fprintf(stderr, " Initialisation du système\n");
	donneesSysteme(&(*controleur).systeme, &(*controleur).options);

		//fprintf(stderr, " Initialisation de fourier\n");
	donneesFourier(&(*controleur).fourier, &(*controleur).options);

		//fprintf(stderr, " Initialisation des graphes\n");
	donneesGraphes(&(*controleur).graphes, &(*controleur).options);

		//fprintf(stderr, " Initialisation des capteurs\n");
	capteursInitialise(&(*controleur).capteurs);
	capteursMiseAJourLongueur(&(*controleur).capteurs, FENETRE_X, FENETRE_Y);

		//fprintf(stderr, " Initialisation de la projection\n");
	projectionInitialise(&(*controleur).projection);
		//fprintf(stderr, "projectionInitialiseLongueurs\n");

		fprintf(stderr, " Initialisation SDL\n");
	interfaceInitialisationSDL();
		//fprintf(stderr, " Création de l'interface SDL\n");
	interfaceInitialisation(&(*controleur).interface);
		//fprintf(stderr, " Création du rendu\n");
	graphiqueCreation(&(*controleur).graphique, &(*controleur).interface);

		fprintf(stderr, " Initialisation des longueur\n");
	int largeur;
	int hauteur;
	int x, y;
	SDL_GetWindowSize((*controleur).interface.fenetre, &largeur, &hauteur);

	(*controleur).graphique.fenetreX=largeur;
	(*controleur).graphique.fenetreY=hauteur;

	commandesInitialiseBoutons(&(*controleur).commandes, largeur, hauteur);
	capteursMiseAJourLongueur(&(*controleur).capteurs, largeur, hauteur);
	projectionInitialiseLongueurs(&(*controleur).projection, largeur, hauteur);// hauteur, largeur, ratio de distance

	SDL_PumpEvents();
	SDL_GetMouseState(&x,&y);
	commandesInitialiseSouris(&(*controleur).commandes, x, y);

		fprintf(stderr, " Initialisation horloge SDL\n");
	horlogeCreation(&(*controleur).horloge);

	return 0;
	}

int donneesOptions(optionsT * options)
	{
		// Préréglage des valeurs optionnelles

	(*options).modeDemo = 1;		// 0 : SiCP, 1 Graphique démo, 2 Commande démo
	(*options).modeClavier = 1;		// 0 : SiCP, 1 Graphique démo, 2 Commande démo
	(*options).modeMenu = 0;		// 0 : SiCP, 1 Graphique démo, 2 Commande démo

	(*options).modePause = 1;		// avec ou sans attente
	(*options).duree = DUREE;		// 100 : temps réèl.
	(*options).fond=240;		// couleur du fond de l'affichage

			// OPTIONS SiCP
	(*options).dt=DT;		// discrétisation du temps
							// 
							// dt*duree = 0.004
	(*options).soliton=0;
	(*options).support=-1;		// Support de la chaîne
	(*options).nombre=NOMBRE;		// Nombre implicite de pendule
	(*options).equation=3;		// 1 : pendule, 2 : linéarisation,
							//	 3 : corde, 4 : dioptre

	return 0;
	}

int donneesSysteme(systemeT * systeme, optionsT * options)
	{

		// Initialisation du moteurs

	(*systeme).moteurs.dt = (*options).dt;	// discrétisation du temps

	(*systeme).moteurs.chrono = 0.0;

	(*systeme).moteurs.etatJosephson = 0;			//	-1, 0, 1
	(*systeme).moteurs.courantJosephson = sqrt(JOSEPHSON_MAX*JOSEPHSON_MIN);
/*
	(*systeme).moteurs.courant=3.0;		// Mémoire courant Josephson si = 0
	(*systeme).moteurs.josephson=0;//-3*(*options).dt*(*options).dt;
*/
	(*systeme).moteurs.generateur = 1;	// éteint, sinus, carre, impulsion
	(*systeme).moteurs.amplitude=sqrt(AMPLITUDE_MAX * AMPLITUDE_MIN);		// Amplitude du générateur de signaux
	(*systeme).moteurs.frequence=sqrt(FREQUENCE_MAX * FREQUENCE_MIN);	// Fréquence du générateur de signaux
	(*systeme).moteurs.phi=0;

		// Caractéristique de la chaîne

	(*systeme).libreFixe = 2;	// 0 periodique, 1 libre, 2 fixe
	(*systeme).nombre = (*options).nombre;		// nombre de pendule
	(*systeme).equation = (*options).equation;	// 1 : pendule pesant, 2 : linéarisation
												// 3 : corde, 4 : dioptre

		// Paramètres physiques

	(*systeme).gravitation = 9.81; // 4*PI*PI
	//(*systeme).gravitation = 0.0; // 4*PI*PI
	(*systeme).masseDroite = 1.0;
	(*systeme).masseGauche = 1.0;
	(*systeme).longueur = 1.0;// 9.81/4/PI/PI = 25 cm => période = 1 s. Met en évidence une erreur dans le calcul de l'énergie de couplage.
	(*systeme).dissipation = sqrt(DISSIPATION_MAX * DISSIPATION_MIN * 3);
	(*systeme).modeDissipation = 2;	//	0 : nulle 1 : uniforme, 2 : extrémité absorbante.
	(*systeme).couplage = sqrt(COUPLAGE_MAX * COUPLAGE_MIN) * (*systeme).nombre;
	(*systeme).dephasage = (*options).soliton * 2 * PI;

		//fprintf(stderr, " Initialisation du système\n");
	systemeInitialise(systeme);
	changeFormeDissipation(systeme, 1);
	changeFormeDissipation(systeme, 2);
	changeConditionsLimites(systeme, (*systeme).libreFixe);
	systemeInitialisePosition(systeme, 0);

	return 0;
	}

int donneesFourier(fourierT * fourier, optionsT * options)
	{
		//fprintf(stderr, " Initialisation de fourier\n");
	fourierInitialise(fourier, (*options).nombre);

	return 0;
	}

int donneesGraphes(graphesT * graphes, optionsT * options)
	{
		//fprintf(stderr, " Initialisation des couleurs et du nombre de points\n");
	grapheInitialise(&(*graphes).corde,(*options).nombre, 5, 6, 6, 255);
	grapheInitialise(&(*graphes).spectre,(*options).nombre, 3, 255, 6, 6);
	grapheInitialise(&(*graphes).gauche,(*options).nombre/2, 1, 127, 63, 127);
	grapheInitialise(&(*graphes).droite,(*options).nombre/2, 1, 127, 127, 63);

		//fprintf(stderr, " Initialisation des longueurs\n");
	graphesInitialiseLongueur(graphes, FENETRE_X, FENETRE_Y);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////
