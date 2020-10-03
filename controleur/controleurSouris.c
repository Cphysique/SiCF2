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

#include "controleurSouris.h"

int controleurSourisDefilePointDeVue(controleurT * controleur);
int controleurSourisDefileCommandes(controleurT * controleur, int zone);

int controleurSourisCommandes(controleurT * controleur, int zone);


int controleurSouris(controleurT * controleur);
int controleurDefile(controleurT * controleur);
int controleurDefilePointDeVue(controleurT * controleur);
int controleurDefileCommandes(controleurT * controleur, int zone);
void controleurBoutonSouris(controleurT * controleur, int appui);

int controleurSouris(controleurT * controleur)
	{
				// Action des mouvements de la souris
/*
	float x, y;
	if((*controleur).appui==1)
		{
		if( (*controleur).commandes.sourisX < (*controleur).commandes.rotatifs && (*controleur).commandes.sourisY < (*controleur).commandes.bas )
			{
			//fprintf(stderr, "controleurSouris xrel = %d\n", (*controleur).interface.evenement.motion.xrel);
			x=-0.0031*(float)((*controleur).interface.evenement.motion.xrel);
			y=0.0031*(float)((*controleur).interface.evenement.motion.yrel);
				//fprintf(stderr, "controleurSouris yrel = %d\n", (*controleur).interface.evenement.motion.yrel);
				//fprintf(stderr, "controleurSouris yrel = %d\n", (*controleur).interface.evenement.motion.yrel);
			projectionChangePsi(&(*controleur).projection, x);
			projectionChangePhi(&(*controleur).projection, y);
			}
		}
*/
	return (*controleur).sortie;
	}

int controleurDefile(controleurT * controleur)
	{
				// Action des mouvements de la mollette

	if((*controleur).commandes.sourisX>(*controleur).commandes.rotatifs)
		{
		controleurDefileCommandes(controleur, 1);
		}
	else
		{
		if((*controleur).commandes.sourisY>(*controleur).commandes.bas)
			{
			controleurDefileCommandes(controleur, 3);
			}
		else
			{
			controleurDefilePointDeVue(controleur);
			}
		}
	return 0;
	}

int controleurDefilePointDeVue(controleurT * controleur)
	{
    (void)controleur;
				// Action des mouvements de la mollette dans la zone 1
/*
	if((*controleur).interface.evenement.wheel.y > 0) // scroll up
		{
		//projectionChangeDistance(&(*controleur).projection, 1.1);
		projectionChangeTaille(&(*controleur).projection, 1.03);
		//fprintf(stderr, "evenement.wheel.y = %d\n", (*controleur).interface.evenement.wheel.y);
		//fprintf(stderr, "Distance = %f\n", (*controleur).projection.pointDeVue.r);
		}
	else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
		{
		//projectionChangeDistance(&(*controleur).projection, 0.9);
		projectionChangeTaille(&(*controleur).projection, 0.97);
		//fprintf(stderr, "evenement.wheel.y = %d\n", (*controleur).interface.evenement.wheel.y);
		//fprintf(stderr, "Distance = %f\n", (*controleur).projection.pointDeVue.r);
		}
*/
	//if(event.wheel.x > 0) // scroll right{}
	//else if(event.wheel.x < 0) // scroll left{}

	return 0;
	}

void controleurBoutonSouris(controleurT * controleur, int appui)
	{
				// Action du bouton gauche de la souris

	(*controleur).appui=appui;
	
	if(appui==1)
		{
		if((*controleur).commandes.sourisX>(*controleur).commandes.rotatifs)
			{
			if((*controleur).commandes.sourisX>(*controleur).commandes.boutons)
				{
				controleurCommandes(controleur, 2);
				}
			else
				{
				controleurCommandes(controleur, 1);
				}
			}
		else
			{
			if((*controleur).commandes.sourisY>(*controleur).commandes.bas)
				{
				controleurCommandes(controleur, 3);
				}
			else
				{
				controleurCommandes(controleur, 0);
				}
			}
		}
	return;
	}

int controleurCommandes(controleurT * controleur, int zone)
	{
				// Action du bouton gauche de la souris
				// dans les zones 2 et 3

	int commande;
	if(zone==2)
		{
		commande = commandeBoutons(&(*controleur).commandes);
		switch(commande)	//	
			{
			case 0: // Périodique
				changeConditionsLimites(&(*controleur).systeme, 0);break;
			case 1: // Libre
				changeConditionsLimites(&(*controleur).systeme, 1);break;
			case 2: // Fixe
				changeConditionsLimites(&(*controleur).systeme, 2);break;
			case 3: // Mixte
				changeConditionsLimites(&(*controleur).systeme, 4);break;
			case 4: // Symétrique
				//changeFormeDissipation(&(*controleur).systeme, 1);
				break;
			case 5: // Uniforme
				changeFormeDissipation(&(*controleur).systeme, 1);break;
			case 6: // Nulle
				changeFormeDissipation(&(*controleur).systeme, 0);break;
			case 7: // Extrémité
				changeFormeDissipation(&(*controleur).systeme, 2);break;
			case 8: // Arrêt
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 0);break;
			case 9: // Sinus
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 1);break;
			case 10: // Carré
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 2);break;
			case 11: // Impulsion
				moteursChangeGenerateur(&(*controleur).systeme.moteurs, 3);break;
			case 12: // Pause
				controleurChangeMode(controleur);break;
			case 13: // Min
				controleurInitialiseVitesse(controleur, 1);break;
			case 14: // Max
				controleurInitialiseVitesse(controleur, DUREE_MAX);break;
			case 15: // Initialise
				systemeInitialisePosition(&(*controleur).systeme, 0);break;
			default:
				;
			}
		}
	if(zone==3)
		{
		commande = commandeTriangles(&(*controleur).commandes);
		switch(commande)	//	
			{
/*
			case 0:
				(*controleur).projection.rotation=3;break;
			case 1:
				(*controleur).projection.rotation=1;break;
			case 2:
				(*controleur).projection.rotation=0;break;
			case 3:
				(*controleur).projection.rotation=-1;break;
			case 4:
				(*controleur).projection.rotation=-3;break;
*/
			case 5:
				controleurChangeVitesse(controleur, 0.32);break;
			case 6:
				controleurChangeVitesse(controleur, 0.91);break;
			case 7:
				controleurChangeMode(controleur);break;
			case 8:
				controleurChangeVitesse(controleur, -1.0);break;
			case 9:
				controleurChangeVitesse(controleur, 1.1);break;
			case 10:
				controleurChangeVitesse(controleur, 3.1);break;
			case 11:
				systemeInitialisePosition(&(*controleur).systeme, 1);break;
			case 12:
				systemeInitialisePosition(&(*controleur).systeme, 2);break;
			case 13:
				systemeInitialisePosition(&(*controleur).systeme, 3);break;
			case 14:
				systemeInitialisePosition(&(*controleur).systeme, 4);break;
			case 15:
				systemeInitialisePosition(&(*controleur).systeme, 5);break;
			case 16:
				systemeInitialisePosition(&(*controleur).systeme, 6);break;
			case 17:
			    fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "aaa");break;
				//controleurInitialiseNombre(controleur, 1);break;
			case 18:
			    fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "bbb");break;
				//controleurInitialiseNombre(controleur, 2);break;
			case 19:
			    fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "ccc");break;
				//controleurInitialiseNombre(controleur, 3);break;
			case 20:
			    fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "ddd");break;
				//controleurInitialiseNombre(controleur, 4);break;
			default:
				;
			}
		}
	return 0;
	}

int controleurDefileCommandes(controleurT * controleur, int zone)
	{
	int commande = -1;
	if(zone==1)
		{
		commande = commandeRotatifs(&(*controleur).commandes);
		if((*controleur).interface.evenement.wheel.y > 0) // scroll up
			{
			switch(commande)
				{
				case 0:
					changeCouplage(&(*controleur).systeme, 1.1);break;
				case 1:
					changeMasse(&(*controleur).systeme, 1.1);break;
				case 2:
					changeDissipation(&(*controleur).systeme, 1.1);break;
				case 3:
					moteursChangeAmplitude(&(*controleur).systeme.moteurs, 1.1);break;
				case 4:
					moteursChangeFrequence(&(*controleur).systeme.moteurs, 1.1);break;
				case 5:
					controleurChangeVitesse(controleur, 1.1);break;
				default:
					;
				}
			}
		else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
			{
			switch(commande)	
				{
				case 0:
					changeCouplage(&(*controleur).systeme, 0.91);break;
				case 1:
					changeMasse(&(*controleur).systeme, 0.91);break;
				case 2:
					changeDissipation(&(*controleur).systeme, 0.91);break;
				case 3:
					moteursChangeAmplitude(&(*controleur).systeme.moteurs, 0.91);break;
				case 4:
					moteursChangeFrequence(&(*controleur).systeme.moteurs, 0.91);break;
				case 5:
					controleurChangeVitesse(controleur, 0.91);break;
				default:
					;
				}
			}
		}

	if(zone==3)
		{
		commande = commandeLineaires(&(*controleur).commandes);
		if((*controleur).interface.evenement.wheel.y > 0) // scroll up
			{
			switch(commande)
				{
				case 0:
					controleurDefilePointDeVue(controleur);break;
				case 1:
					controleurDefilePointDeVue(controleur);break;
				case 2:
					controleurChangeVitesse(controleur, 1.1);break;
				case 3:
					controleurChangeVitesse(controleur, 1.1);break;
				default:
					;
				}
			}
		else if((*controleur).interface.evenement.wheel.y < 0) // scroll down
			{
			switch(commande)	
				{
				case 0:
					controleurDefilePointDeVue(controleur);break;
				case 1:
					controleurDefilePointDeVue(controleur);break;
				case 2:
					controleurChangeVitesse(controleur, 0.91);break;
				case 3:
					controleurChangeVitesse(controleur, 0.91);break;
				default:
					;
				}
			}
		}
	return 0;
	}

int controleurSourisAffiche(controleurT * controleur)
	{
	fprintf(stderr, "(*controleur).graphique.fenetreY = %d\n", (*controleur).graphique.fenetreY);
	fprintf(stderr, "(*controleur).commandes.sourisY = %d\n", (*controleur).commandes.sourisY);
	fprintf(stderr, "RAPPORT = %f\n", (float)(*controleur).commandes.sourisY / (*controleur).graphique.fenetreY);
	fprintf(stderr, "(*controleur).graphique.fenetreX = %d\n", (*controleur).graphique.fenetreX);
	fprintf(stderr, "(*controleur).commandes.sourisX = %d\n", (*controleur).commandes.sourisX);
	fprintf(stderr, "RAPPORT = %f\n", (float)(*controleur).commandes.sourisX / (*controleur).graphique.fenetreX);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////////////////
