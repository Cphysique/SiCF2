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

#include "controleur.h"
#include "controleurClavier.h"
#include "controleurSouris.h"

int controleurEvolution(controleurT * controleur);

int controleurProjection(controleurT * controleur);

int controleurConstructionGraphique(controleurT * controleur);

int controleurTraiteEvenement(controleurT * controleur);

int controleurKEYDOWN(controleurT * controleur);
void controleurReinitialisationFichiers(controleurT * controleur);

int controleurInitialiseParametres(controleurT * controleur, int forme);
int controleurInitialiseFluxons(controleurT * controleur);
int controleurInitialiseNulle(controleurT * controleur);

int controleurSouris(controleurT * controleur);
int controleurDefile(controleurT * controleur);
int controleurDefilePointDeVue(controleurT * controleur);
int controleurDefileCommandes(controleurT * controleur, int zone);
void controleurBoutonSouris(controleurT * controleur, int appui);
void controleurAfficheSouris(controleurT * controleur);

void controleurChangeMode(controleurT * controleur);
void controleurChangeVitesse(controleurT * controleur, float facteur);
int controleurChangeNombre(controleurT * controleur, int sens);

int controleurDestruction(controleurT * control)
	{

	fprintf(stderr, "Suppression de l'horloge\n");
	horlogeSuppression(&(*control).horloge);

	fprintf(stderr, "Suppression du rendu\n");
	graphiqueDestruction(&(*control).graphique);

	fprintf(stderr, "Suppression de la fenêtre\n");
	interfaceDestruction(&(*control).interface);

	fprintf(stderr, "Sortie de la SDL\n");
	interfaceQuitteSDL();

	return 0;
	}

int controleurSimulationGraphique(controleurT * controleur)
	{
	do	{
		if (SDL_WaitEvent(&(*controleur).interface.evenement))
			{
			controleurTraiteEvenement(controleur);
			}
		}
	while((*controleur).sortie == 0);

	return 0;
	}

int controleurEvolution(controleurT * controleur)
	{
	//horlogeChronoDepart(&(*controleur).horloge);

		//fprintf(stderr, "Projection du système sur la représentation graphique\n");
	controleurProjection(controleur);

	if((*controleur).options.modePause > 0)
		{
		//horlogeChronoDepart(&(*controleur).horloge);
		controleurEvolutionSysteme(controleur);
		}

	//horlogeChronoDepart(&(*controleur).horloge);

		//fprintf(stderr, "Mise à jour de la fenêtre graphique\n");
	controleurConstructionGraphique(controleur);

	return (*controleur).sortie;
	}

int controleurProjection(controleurT * controleur)
	{
	int largeur;
	int hauteur;
	int x, y;

		// Récupération de la taille de la fenêtre
	SDL_GetWindowSize((*controleur).interface.fenetre, &largeur, &hauteur);

		// Réinitialisation des longueurs si la fenêtre a changé de taille
	if((*controleur).graphique.fenetreX!=largeur || (*controleur).graphique.fenetreY!=hauteur)
		{
		(*controleur).graphique.fenetreX=largeur;
		(*controleur).graphique.fenetreY=hauteur;
		graphesInitialiseLongueur(&(*controleur).graphes, largeur, hauteur);
		commandesInitialiseBoutons(&(*controleur).commandes, largeur, hauteur);
		capteursMiseAJourLongueur(&(*controleur).capteurs, largeur, hauteur);
		projectionInitialiseLongueurs(&(*controleur).projection, hauteur, largeur);
		}

			// Récupération de la position de la souris
	SDL_PumpEvents();
	SDL_GetMouseState(&x,&y);
			// Réinitialisation des commandes de la souris
	commandesInitialiseSouris(&(*controleur).commandes, x, y);

		//fprintf(stderr, "projection de la corde et des spectres\n");
	projectionSystemeGraphe(&(*controleur).systeme, &(*controleur).projection, &(*controleur).graphes);
	projectionFourierGraphe(&(*controleur).fourier, &(*controleur).projection, &(*controleur).graphes);

	projectionObservablesCapteurs(&(*controleur).observables, &(*controleur).projection, &(*controleur).capteurs);
		//fprintf(stderr, "projection du système sur les commandes\n");
	projectionSystemeCommandes(&(*controleur).systeme, &(*controleur).projection, &(*controleur).commandes, (*controleur).options.duree, (*controleur).options.modePause);

	return (*controleur).sortie;
	}

int controleurEvolutionSysteme(controleurT * controleur)
	{
		//fprintf(stderr, "Evolution temporelle du système\n");
	systemeEvolution(&(*controleur).systeme, (*controleur).options.duree);

		//fprintf(stderr, "Projection du système sur les spectres\n");
	projectionSystemeFourier(&(*controleur).systeme, &(*controleur).fourier);

		//fprintf(stderr, "Calcul des spectres\n");
	fourierCalcule(&(*controleur).fourier);

		//fprintf(stderr, "Mise à jour des observables\n");
	observablesMiseAJour(&(*controleur).observables, &(*controleur).systeme);

	return 0;
	}

int controleurConstructionGraphique(controleurT * controleur)
	{

		//fprintf(stderr, "Nettoyage de l'affichage\n");
	//graphiqueNettoyage(&(*controleur).graphique);

		//fprintf(stderr, "Dessin des Commandes\n");
	graphiqueCommandes(&(*controleur).graphique, &(*controleur).commandes);

		//fprintf(stderr, "Dessin des capteurs\n");
	graphiqueCapteurs(&(*controleur).graphique, &(*controleur).capteurs);

		//fprintf(stderr, "Dessin des graphes\n");
	graphiqueCorde(&(*controleur).graphique, &(*controleur).graphes.corde);
	graphiqueSpectre(&(*controleur).graphique, &(*controleur).graphes.spectre);
	graphiqueSpectre(&(*controleur).graphique, &(*controleur).graphes.gauche);
	graphiqueSpectre(&(*controleur).graphique, &(*controleur).graphes.droite);

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	graphiqueMiseAJour(&(*controleur).graphique);

	return (*controleur).sortie;
	}

int controleurTraiteEvenement(controleurT * controleur)
	{
	int sortie = 0;
	switch((*controleur).interface.evenement.type)
		{
		case SDL_QUIT:
			(*controleur).sortie = 1;break;
		case SDL_MOUSEWHEEL:
			controleurDefile(controleur);break;
		case SDL_MOUSEMOTION:
			controleurSouris(controleur);break;
		case SDL_MOUSEBUTTONDOWN:
			controleurBoutonSouris(controleur, 1);break;
		case SDL_MOUSEBUTTONUP:
			controleurBoutonSouris(controleur, 0);break;
		case SDL_USEREVENT:
			controleurEvolution(controleur);break;
		case SDL_KEYDOWN:
			controleurKEYDOWN(controleur);break;
		default:
			;
		}
	if(sortie!=0) (*controleur).sortie = 1;
	return (*controleur).sortie;
	}

int controleurKEYDOWN(controleurT * controleur)
	{
	int Maj = 0;
	int ctrl = 0;
	//int reinitialisation = 0; // Pour dessiner les spectres 

	if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
	|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT))
		{
		Maj = 1;
		}
	if ((((*controleur).interface.evenement.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL)
	|| (((*controleur).interface.evenement.key.keysym.mod & KMOD_RCTRL) == KMOD_RCTRL))
		{
		ctrl = 1;
		}
	if(Maj == 0 && ctrl == 0)
		{
		return controleurClavier(controleur);
		}
	else
		{
		if(Maj == 1 && ctrl == 1)
			{
			return controleurClavierCtrlMaj(controleur);
			}
		else
			{
			if(Maj == 1 )
				{
				if (controleurClavierMaj(controleur) == 1)
					{
					controleurReinitialisationFichiers(controleur);
					}
				}
			else
				{
				if (controleurClavierCtrl(controleur) == 1)
					{
					controleurReinitialisationFichiers(controleur);
					}
				}
			}
		}

	return (*controleur).sortie;
	}

void controleurReinitialisationFichiers(controleurT * controleur)
	{
		fprintf(stderr, "Projection du système sur les spectres\n");
	projectionSystemeFourier(&(*controleur).systeme, &(*controleur).fourier);
		fprintf(stderr, "Calcul des spectres\n");
	fourierCalcule(&(*controleur).fourier);
		//fprintf(stderr, "Mise à jour des observables\n");
	//observablesMiseAJour(&(*controleur).observables, &(*controleur).systeme);
		fprintf(stderr, "Remise à zéro des observables temporelles\n");
	observablesInitialise(&(*controleur).observables);

	return;
	}


void controleurChangeMode(controleurT * controleur)
	{
	(*controleur).options.modePause=-(*controleur).options.modePause;

	return;
	}

void controleurChangeVitesse(controleurT * controleur, float facteur)
	{
	if(facteur < 0.0)
		{
		(*controleur).options.duree = DUREE;
		}
	else
		{
		if( (*controleur).options.duree > 11 )
			{
			(*controleur).options.duree = (*controleur).options.duree * facteur;
			}
		else
			{
			if( facteur > 1)
				{
				(*controleur).options.duree ++;
				}
			else
				{
				if( (*controleur).options.duree > 1 )
					{
					(*controleur).options.duree --;
					}
				else
					{
					fprintf(stderr, "duree minimale atteinte, ");
					}
				}
			}

		if( (*controleur).options.duree > DUREE_MAX)
			{
			fprintf(stderr, "duree maximale atteinte, ");
			(*controleur).options.duree = DUREE_MAX;
			}
		}
	fprintf(stderr, "duree = %d\n", (*controleur).options.duree);
	return;
	}

void controleurInitialiseVitesse(controleurT * controleur, int duree)
	{
	if(duree < 0)
		{
		(*controleur).options.duree = DUREE;
		}
	else
		{
		if(duree > 0 &&  duree < DUREE_MAX)
			{
			(*controleur).options.duree = duree;
			}
		else
			{
			(*controleur).options.duree = DUREE_MAX;
			}
		}
	fprintf(stderr, "duree = %d\n", (*controleur).options.duree);
	return;
	}

int controleurChangeNombre(controleurT * controleur, int sens)
	{
	(void)controleur;
	(void)sens;

	//fprintf(stderr, "controleurChangeNombre(controleurT * controleur, int sens)");

	return 0;
	}

int controleurInitialiseParametres(controleurT * controleur, int forme)
	{

	switch(forme)
		{
		case 0:
			controleurInitialiseNulle(controleur);break;
		case 1:
			controleurInitialiseNulle(controleur);break;
		case 2:
			controleurInitialiseNulle(controleur);
			moteursChangeGenerateur(&(*controleur).systeme.moteurs, 1);
			changeFormeDissipation(&(*controleur).systeme, 2);break;
		case 3:
			controleurInitialiseFluxons(controleur);
			changeDissipation(&(*controleur).systeme, 0.33);break;
		case 4:
			controleurInitialiseFluxons(controleur);
			changeFormeDissipation(&(*controleur).systeme, 2);	// Extrémitée absorbante
			break;
		default:
			controleurInitialiseNulle(controleur);break;
		}
	return 0;
	}

int controleurInitialiseNulle(controleurT * controleur)
	{
	moteursChangeGenerateur(&(*controleur).systeme.moteurs, 0);
	//(*controleur).systeme.premier->pendule.dephasage = 0; // Supprime les fluxons

		// Condition au limites libres
	changeConditionsLimites(&(*controleur).systeme, 1);

		// Réglage du couplage
	changeCouplageMoyenne(&(*controleur).systeme);

		// Réglage de la dissipation
	changeDissipationMoyenne(&(*controleur).systeme);
	changeFormeDissipation(&(*controleur).systeme, 0);

		// Réglage du moteur josephson
    moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs,0);
	//moteursChangeEtatJosephson(&(*controleur).systeme.moteurs, 0);
	//moteursChangeJosephsonMoyenne(&(*controleur).systeme.moteurs);

		// Réglage du moteur périodique
	//moteursChangeGenerateur(&(*controleur).systeme.moteurs, 0);
    moteursInitialiseGenerateur(&(*controleur).systeme.moteurs, 0);

	return 0;
	}

int controleurInitialiseFluxons(controleurT * controleur)
	{
			controleurInitialiseNulle(controleur);

	changeDephasage(&(*controleur).systeme, -6*PI); // Ajoute 3 fluxons

		// Condition au limites périodique
	changeConditionsLimites(&(*controleur).systeme, 0);

		// Réglage du couplage
	changeCouplageMoyenne(&(*controleur).systeme);

		// Réglage de la dissipation
	changeDissipationMoyenne(&(*controleur).systeme);
	changeFormeDissipation(&(*controleur).systeme, 1);

		// Réglage du moteur josephson
	//moteursChangeEtatJosephson(&(*controleur).systeme.moteurs, 1);
    moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs,1);
	moteursChangeJosephsonMoyenne(&(*controleur).systeme.moteurs);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////
