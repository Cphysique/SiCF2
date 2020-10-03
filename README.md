# SiCF2

Corde vibrante et transformation de Fourier

Ce logiciel est régi par la licence CeCILL

NOM
	SiCF2 - Simulateur de corde vibrante et spectre de fréquence

SYNOPSIS
	./SiCF2 [ OPTION VALEUR ]...

OPTION

	dt
		Discrétisation du temps	( 0.00003 < dt < 0.003 )
		( Discrétisation implicite du temps : dt = 0.0011 )

	nombre
		Discrétisation spatiale ( 8 <= nombre <= 1024 et nombre est une puissance de 2 )
		( Discrétisation spatiale implicite : nombre = 256 )

AUTEUR
		Écrit par Stephan Runigo

SIGNALER DES BOGUES
		runigo@free.fr

INSTALLATION
Pour installer ce programme sur votre ordinateur, vous devez avoir
installé la librairie graphique SDL ainsi que les outils permettant
la compilation :
Par exemple, avec une distribution basée sur debian, dans un terminal avec les
droits de l'administrateur :

	# apt-get install gcc make libsdl2-dev

Placez-vous dans le répertoire des sources, effectuez la compilation,

	$ make

Lancer l'exécutable créé :

	$ ./SiCF2

Lancer l'exécutable avec d'éventuelles options :

	$ ./SiCF2 dt 0.0022 nombre 16

UTILISATION

Le terminal dans lequel est lancé l'exécutable affiche les informations
lors de l'exécution.

La sélection et le réglage des paramètres paramètres peuvent être effectués
à l'aide de la souris ou à l'aide du clavier.

La touches Maj donne accès à la réinitialisation de la position.
La touches Ctrl permet l'enregistrement de la position.

FONCTION DU CLAVIER

Entrée : change le mode temporelle

+, - : augmente, diminue la vitesse de la simulation


a, q : augmenter, diminuer le couplage
z, s : augmenter, diminuer la masse

e, d : diminuer, augmenter la dissipation
r, f : retire, forme la dissipation
v : forme l'extremité absorbante

t, g : augmenter, diminuer la gravitation
y, h : ajoute, enlève un déphasage de 2 pi

w : conditions aux limites périodique
x : extrémités libres
c : extrémités fixe
b, n : fixe une extrémité, libère l'autre

u, j : augmenter, diminuer l'amplitude du générateur
i : démarre une impulsion
o : démarre, éteint le générateur
l : démarre le signal carrée
p, m : augmenter, diminuer la fréquence

F5 : affiche les énergies
F6 : affiche les paramètres physiques

flêche droite : allume, éteint le courant Josephson
flêches haut, bas : augmente, diminue l'intensité
flêche gauche : change le sens du courant

FONCTION DU CLAVIER CTRL
q..m et w..n : enregistre la position

FONCTION DU CLAVIER MAJ
a..p : initialise la position de la corde
q..m et w..n : initialise les positions enregistrées.

LICENCE

Copyright août 2019, Stephan Runigo
runigo@free.fr
SiCF 2.1  simulateur de corde vibrante et spectre
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
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies. Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.

MEMO

r vient de e qui vient de z qui vient de j
y vient de t qui vient de k
i vient de u qui vient de m
p vient de o qui vient de d ou f ou s ou q


