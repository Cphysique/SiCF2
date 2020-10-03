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

#include "controleurClavier.h"
/*
int controleurClavier(controleurT * controleur);
int controleurClavierMaj(controleurT * controleur);
int controleurClavierCtrl(controleurT * controleur);
int controleurClavierCtrlMaj(controleurT * controleur);
*/


int controleurClavier(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
	// Mode : évolution du système en pause
		case SDLK_RETURN:
			controleurChangeMode(controleur);break;
		case SDLK_BACKSPACE:
			controleurChangeMode(controleur);break;
		case SDLK_SPACE:
			controleurEvolutionSysteme(controleur);break;

	// Vitesse de la simulation
		case SDLK_KP_PLUS:
			controleurChangeVitesse(controleur, 1.1);break;
		case SDLK_KP_MINUS:
			controleurChangeVitesse(controleur, 0.91);break;
		case SDLK_F9:
			controleurChangeVitesse(controleur, 0.32);break;
		case SDLK_F10:
			controleurChangeVitesse(controleur, 0.91);break;
		case SDLK_F11:
			controleurChangeVitesse(controleur, 1.1);break;
		case SDLK_F12:
			controleurChangeVitesse(controleur, 3.1);break;

	// Conditions aux limites
		case SDLK_y:
			changeDephasage(&(*controleur).systeme, 1);break;
		case SDLK_h:
			changeDephasage(&(*controleur).systeme, -1);break;
		case SDLK_w:
			changeConditionsLimites(&(*controleur).systeme, 0); // periodiques
			break;
		case SDLK_x:
			changeConditionsLimites(&(*controleur).systeme, 1); // libres
			break;
		case SDLK_c:
			changeConditionsLimites(&(*controleur).systeme, 2); // fixes
			break;
		case SDLK_b:
			fprintf(stderr, "Commande désactivée depuis SiCP 1.4.1");
			//changeConditionsLimites(&(*controleur).systeme, 3); // libre fixe
			break;
		case SDLK_n:
			changeConditionsLimites(&(*controleur).systeme, 3); // fixe libre
			break;


	// Dissipation
		case SDLK_e:
			changeDissipation(&(*controleur).systeme, 0.77);break;
		case SDLK_d:
			changeDissipation(&(*controleur).systeme, 1.3);break;
		case SDLK_r:
			changeFormeDissipation(&(*controleur).systeme, 0);break;
		case SDLK_f:
			changeFormeDissipation(&(*controleur).systeme, 1);break;
		case SDLK_v:
			changeFormeDissipation(&(*controleur).systeme, 2);break;

	// Couplage
		case SDLK_a:
			changeCouplage(&(*controleur).systeme, 1.1);break;
		case SDLK_q:
			changeCouplage(&(*controleur).systeme, 0.91);break;

	// Masse
		case SDLK_z:
			changeMasse(&(*controleur).systeme, 1.7);break;
		case SDLK_s:
			changeMasse(&(*controleur).systeme, 0.59);break;

	// Gravitation
		case SDLK_t:
			changeGravitation(&(*controleur).systeme, 1.3);break;
		case SDLK_g:
			changeGravitation(&(*controleur).systeme, 0.77);break;

	// Moteur jonction Josephson
		case SDLK_UP:
			moteursChangeJosephson(&(*controleur).systeme.moteurs,1.1);break;
		case SDLK_DOWN:
			moteursChangeJosephson(&(*controleur).systeme.moteurs,0.91);break;
		case SDLK_LEFT:
			moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs,-1);break;
			//moteursChangeJosephson(&(*controleur).systeme.moteurs,-1.0);break; SiCF 2.1
		case SDLK_RIGHT:
			moteursInitialiseEtatJosephson(&(*controleur).systeme.moteurs,1);break;
			//moteursChangeJosephson(&(*controleur).systeme.moteurs,0.0);break; SiCF 2.1

	// Moteur générateur de signaux
		case SDLK_p:
			moteursChangeFrequence(&(*controleur).systeme.moteurs,1.1);break;
		case SDLK_m:
			moteursChangeFrequence(&(*controleur).systeme.moteurs,0.91);break;
		case SDLK_u:
			moteursChangeAmplitude(&(*controleur).systeme.moteurs,1.1);break;
		case SDLK_j:
			moteursChangeAmplitude(&(*controleur).systeme.moteurs,0.91);break;
		case SDLK_o:
			moteursChangeGenerateur(&(*controleur).systeme.moteurs, -1);break;
		case SDLK_i:
			moteursChangeGenerateur(&(*controleur).systeme.moteurs, 3);break;
		case SDLK_l:
			moteursChangeGenerateur(&(*controleur).systeme.moteurs, 2);break;


	// Choix de la simulation
/*
		case SDLK_F1: // Pendules
			(*controleur).systeme.equation = 1;break;
		case SDLK_F2: // Harmoniques
			(*controleur).systeme.equation = 2;break;
		case SDLK_F3: // Corde
			(*controleur).systeme.equation = 3;break;
		case SDLK_F1:
			projectionAffiche(&(*controleur).projection);break;
*/
  // Afficher les observables

		case SDLK_F4:
			controleurSourisAffiche(controleur);
			break;
		case SDLK_F5:
			observablesAfficheEnergie(&(*controleur).systeme);
			//observablesAffiche(&(*controleur).observables); SiCF 2.1
			break;
		case SDLK_F6:
			moteursAfficheHorloge(&(*controleur).systeme.moteurs);
			break;
		case SDLK_F7:
			//projectionAffiche(&(*controleur).projection);
			systemeAffiche(&(*controleur).systeme); // SiCF 2.1
			break;
	// Support SiCP 2.4.4
		case SDLK_F8:
			//grapheChangeSupport(&(*controleur).graphe);break;
			penduleAffiche(&(*controleur).systeme.pendule[(*controleur).systeme.nombre/4]);


		default:
			;
		}
	return (*controleur).sortie;
	}

int controleurClavierMaj(controleurT * controleur)
	{
        //      Réinitialisation du système
        //          Fichiers utilisateur

	int reinitialisation = 1;

	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
		case SDLK_a:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "a");break;
		case SDLK_z:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "z");break;
		case SDLK_e:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "e");break;
		case SDLK_r:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "r");break;
		case SDLK_t:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "t");break;
		case SDLK_y:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "y");break;
		case SDLK_u:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "u");break;
		case SDLK_i:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "i");break;
		case SDLK_o:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "o");break;
		case SDLK_p:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "p");break;
		case SDLK_q:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "q");break;
		case SDLK_s:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "s");break;
		case SDLK_d:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "d");break;
		case SDLK_f:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "f");break;
		case SDLK_g:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "g");break;
		case SDLK_h:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "h");break;
		case SDLK_j:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "j");break;
		case SDLK_k:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "k");break;
		case SDLK_l:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "l");break;
		case SDLK_m:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "m");break;
		case SDLK_w:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "w");break;
		case SDLK_x:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "x");break;
		case SDLK_c:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "c");break;
		case SDLK_v:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "v");break;
		case SDLK_b:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "b");break;
		case SDLK_n:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "n");break;
		default:
			{
			reinitialisation = 0;
			}break;
		}

	return reinitialisation;
	}

int controleurClavierCtrl(controleurT * controleur)
	{
        //      Réinitialisation du système 
        //          Fichiers original
	int reinitialisation = 1;

	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
		case SDLK_a:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "aa");break;
		case SDLK_z:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "zz");break;
		case SDLK_e:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "ee");break;
		case SDLK_r:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "rr");break;
		case SDLK_t:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "tt");break;
		case SDLK_y:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "yy");break;
		case SDLK_u:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "uu");break;
		case SDLK_i:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "ii");break;
		case SDLK_o:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "oo");break;
		case SDLK_p:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "pp");break;
		case SDLK_q:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "qq");break;
		case SDLK_s:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "ss");break;
		case SDLK_d:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "dd");break;
		case SDLK_f:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "ff");break;
		case SDLK_g:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "gg");break;
		case SDLK_h:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "hh");break;
		case SDLK_j:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "jj");break;
		case SDLK_k:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "kk");break;
		case SDLK_l:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "ll");break;
		case SDLK_m:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "mm");break;
		case SDLK_w:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "ww");break;
		case SDLK_x:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "xx");break;
		case SDLK_c:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "cc");break;
		case SDLK_v:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "vv");break;
		case SDLK_b:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "bb");break;
		case SDLK_n:
			fichierLecture(&(*controleur).systeme, &(*controleur).fourier, &(*controleur).graphes, "nn");break;
		default:
			{
			reinitialisation = 0;
			}break;
		}

	return reinitialisation;
	}

int controleurClavierCtrlMaj(controleurT * controleur)
	{
	switch ((*controleur).interface.evenement.key.keysym.sym)
		{
		    // Sauvegarde du système

		case SDLK_a:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "a");break;
		case SDLK_z:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "z");break;
		case SDLK_e:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "e");break;
		case SDLK_r:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "r");break;
		case SDLK_t:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "t");break;
		case SDLK_y:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "y");break;
		case SDLK_u:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "u");break;
		case SDLK_i:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "i");break;
		case SDLK_o:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "o");break;
		case SDLK_p:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "p");break;
		case SDLK_q:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "q");break;
		case SDLK_s:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "s");break;
		case SDLK_d:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "d");break;
		case SDLK_f:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "f");break;
		case SDLK_g:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "g");break;
		case SDLK_h:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "h");break;
		case SDLK_j:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "j");break;
		case SDLK_k:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "k");break;
		case SDLK_l:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "l");break;
		case SDLK_m:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "m");break;
		case SDLK_w:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "w");break;
		case SDLK_x:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "x");break;
		case SDLK_c:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "c");break;
		case SDLK_v:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "v");break;
		case SDLK_b:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "b");break;
		case SDLK_n:
			fprintf(stderr, "Sauvegarde du système\n");
			fichierEcriture(&(*controleur).systeme, "n");break;
		default:
			;
		}
	return (*controleur).sortie;
	}

//////////////////////////////////////////////////////////////////////////////////////
