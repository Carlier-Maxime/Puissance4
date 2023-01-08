# Puissance 4

Ceci est un programme en C permettant de jouer au puissance 4, de version sont disponibles en une. <br>
une version terminal permettant de jouer depuis votre terminal préféré. <br>
une version graphique réalisé avec la SDL vous permettant ainsi de jouer à une version plus ergonomique.

## But du jeu

le but est d'aligner une suite de 4 pions de même couleur sur une grille comptant 6 rangées et 7 colonnes. <br>
Chaque joueur dispose de 21 pions d'une couleur (généralement sang et or). <br>
Tour à tour, les deux joueurs placent un pion dans une colonne libre de leur choix. <br>
Le pion "descend" jusqu'à la position la plus basse possible dans la dite colonne à la suite de quoi c'est à l'adversaire de jouer. <br>
Le vainqueur est le joueur qui réalise le premier un alignement (horizontal, vertical ou diagonal) consécutif d'au moins quatre pions de sa couleur. <br>
Si toutes les cases de la grille de jeu sont remplies, aucun des deux joueurs n'a réalisé un tel alignement, la partie est déclarée nulle. <br>

## Installation

Pour installer ce programme en suivant ces instruction vous devez avoir d'installer :
* git (pour récupérer le code. pour l'installer sur ubuntu : ```sudo apt install git```)
* gcc (pour compiler le programme. pour l'installer sur ubuntu : ```sudo apt install gcc```)
* SDL (la librairie utiliser pour le GUI. pour l'installer sur ubuntu : ```sudo apt install libsdl2-dev``` )
* CUnit (si vous souhaitez efféctuer les test unitaire. pour installer sur ubuntu : ```sudo apt install libcunit1-dev```)
* make (pour éxécuter le makefile. pour l'installer sur ubuntu : ```sudo apt install make```)

Une fois tout ces prérequis correctement installer vous devriez pouvoir installer le programme en effectuant les commandes suivantes :
```bash
git clone https://github.com/Carlier-Maxime/Puissance4
cd Puissance4
make
```

Pour compiler les test : ```make test``` <br>
Pour clean les object file C : ```make clean``` <br>
Pour clean complétement : ```make mrproper``` <br>

## Exécution du programme

Pour éxécuter le programme, une fois dans le répertoire Puissance4 et avoir compiler le programme éxécuter :
```./out/puissance4``` <br>
pour jouer en version terminal éxécuter : ```./out/puissance4 terminal``` <br>
Pour lancer les test unitaire : ```./out/test```

## Informations

Les messages indiquant le gagnant et à qui c'est de jouer dans la vue graphique sont sur le titre de la fenêtre. <br>
(cela sera changer dans une future mise à jour)

Au lancement du jeu en interface graphique pour séléctionner quelle est le type des 2 joueur qui s'affronte : <br>
cliquer sur les 2 icone correspondante, les icone de gauche vers la droite : <br>
Human / IA Facile / IA Normal / IA Difficile <br>
(Il est conseiller d'attendre une petite seconde avant de choisir)