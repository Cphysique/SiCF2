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

#include "commandes.h"

int commandesInitialiseBoutons(commandesT * commandes, int largeur, int hauteur)
	{
		 // Zone des boutons rotatifs
	(*commandes).rotatifs=(int)(0.84*largeur); //		Zone des boutons rotatifs
		// BOUTONS ROTATIFS SUIVANT X
	(*commandes).rotatifX=(int)(0.021*largeur); //		Rayon suivant X
	(*commandes).rotatifsCentre=(int)(0.892632*largeur); // Positon X des boutons rotatifs
		// BOUTONS ROTATIFS SUIVANT Y
	(*commandes).rotatifY=(int)(0.032*hauteur); //	Rayon suivant Y
	(*commandes).rotatifCentre[0]=(int)(0.111919*hauteur); //		Couplage
	(*commandes).rotatifCentre[1]=(int)(0.226744*hauteur); //		Masse droite
	(*commandes).rotatifCentre[2]=(int)(0.376453*hauteur); //		Dissipation
	(*commandes).rotatifCentre[3]=(int)(0.536337*hauteur); //		Amplitude
	(*commandes).rotatifCentre[4]=(int)(0.671512*hauteur); //		Fréquence
	(*commandes).rotatifCentre[5]=(int)(0.829942*hauteur); //		Simulation
	(*commandes).rotatifCentre[6]=(int)(0.937500*hauteur); //		Nombre

		 // Zone des petits boutons
	(*commandes).boutons=(int)(0.946459412781*largeur); // Zone des petits boutons
		// PETITS BOUTONS SUIVANT X
	(*commandes).boutonX=(int)(0.012*largeur); // Rayon suivant X
	(*commandes).boutonsCentre=(int)(0.964*largeur); // 1117 // Positon X des petits boutons
		// PETITS BOUTONS SUIVANT Y
	(*commandes).boutonY=(int)(0.016*largeur); // Rayon suivant Y
	(*commandes).boutonCentre[0]=(int)(0.0535*hauteur); //		Périodique
	(*commandes).boutonCentre[1]=(int)(0.0915*hauteur); //		Libre
	(*commandes).boutonCentre[2]=(int)(0.1325*hauteur); //		Fixe
	(*commandes).boutonCentre[3]=(int)(0.1725*hauteur); //		Mixte
	(*commandes).boutonCentre[4]=(int)(0.236919*hauteur); //		Symétrique
	(*commandes).boutonCentre[5]=(int)(0.329942*hauteur); //		Uniforme
	(*commandes).boutonCentre[6]=(int)(0.372093*hauteur); //		Nulle
	(*commandes).boutonCentre[7]=(int)(0.4145*hauteur); //		Extrémité
	(*commandes).boutonCentre[8]=(int)(0.534884*hauteur); //		Marche/Arrêt
	(*commandes).boutonCentre[9]=(int)(0.582849*hauteur); //		Sinus
	(*commandes).boutonCentre[10]=(int)(0.629360*hauteur); //		Carré
	(*commandes).boutonCentre[11]=(int)(0.6731*hauteur); //		Impulsion
	(*commandes).boutonCentre[12]=(int)(0.795058*hauteur); //		Pause
	(*commandes).boutonCentre[13]=(int)(0.833*hauteur); //		min
	(*commandes).boutonCentre[14]=(int)(0.875000*hauteur); //		max
	(*commandes).boutonCentre[15]=(int)(0.933140*hauteur); //		Initialise

	//	PANNEAU BAS
	(*commandes).bas=(int)(0.447674*hauteur); // Zone du panneau

	return 0;
	}

int commandesInitialiseSouris(commandesT * commandes, int sourisX, int sourisY)
	{
		 // Rayon des petits boutons
	int rayonX=(*commandes).boutonX;
	int rayonY=(*commandes).boutonY;

		 
	if(sourisX>(*commandes).rotatifs)
		{
		if(sourisX<(*commandes).boutons)// Zone des boutons rotatifs
			{
			rayonX=(*commandes).rotatifX;
			rayonY=(*commandes).rotatifY;
			}
		}

		// POSITION DE LA SOURIS
	(*commandes).sourisX = sourisX; // position X de la souris
	(*commandes).sourisY = sourisY; // position Y de la souris

	(*commandes).sourisGauche = sourisX-rayonX; // position X de la souris - RayonBoutonX
	(*commandes).sourisDroite = sourisX+rayonX; // position X de la souris + RayonBoutonX
	(*commandes).sourisHaut = sourisY-rayonY; // position Y de la souris - RayonBoutonY
	(*commandes).sourisBas = sourisY+rayonY; // position Y de la souris + RayonBoutonY

	return 0;
	}

int commandeBoutons(commandesT * commandes)
	{
	int i;
	if((*commandes).boutonsCentre>(*commandes).sourisGauche && (*commandes).boutonsCentre<(*commandes).sourisDroite)
		{
		for(i=0;i<BOUTON_COMMANDES;i++)
			{
			if((*commandes).boutonCentre[i]>(*commandes).sourisHaut && (*commandes).boutonCentre[i]<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}

int commandeRotatifs(commandesT * commandes)
	{
	int i;
	if((*commandes).rotatifsCentre>(*commandes).sourisGauche && (*commandes).rotatifsCentre<(*commandes).sourisDroite)
		{
		for(i=0;i<ROTATIF_COMMANDES;i++)
			{
			if((*commandes).rotatifCentre[i]>(*commandes).sourisHaut && (*commandes).rotatifCentre[i]<(*commandes).sourisBas)
				return i;
			}
		}
	return -1;
	}

int commandeTriangles(commandesT * commandes)
	{
    (void)commandes;
/*
	int i;
	if((*commandes).trianglesCentre>(*commandes).sourisHaut && (*commandes).trianglesCentre<(*commandes).sourisBas)
		{
		for(i=0;i<TRIANGLE_COMMANDES;i++)
			{
			if((*commandes).triangleCentre[i]>(*commandes).sourisGauche && (*commandes).triangleCentre[i]<(*commandes).sourisDroite)
				return i;
			}
		}
*/
	return -1;
	}

int commandeLineaires(commandesT * commandes)
	{
    (void)commandes;
/*
	int i;
	if((*commandes).lineairesCentre>(*commandes).sourisHaut && (*commandes).lineairesCentre<(*commandes).sourisBas)
		{
		for(i=0;i<LINEAIRE_COMMANDES;i++)
			{
			if((*commandes).lineaireCentre[i]>(*commandes).sourisGauche && (*commandes).lineaireCentre[i]<(*commandes).sourisDroite)
				return i;
			}
		}
*/
	return -1;
	}

//////////////////////////////////////////////////////////////////
