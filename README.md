# Candy Crush en C
Un clone minimaliste de Candy Crush réalisé en C avec ncurses

## Comment jouer 
1. Sélectionner un bonbon
Utilisez les touches z, q, s, d pour déplacer le curseur jusqu'au bonbon que vous voulez échanger.

2. Appuyez sur ESPACE pour sélectionner le bonbon courant, puis :

Appuyez sur ENTRÉE pour activer le mode échange
Choisissez une direction (flèches directionnelles) pour échanger avec le bonbon adjacent :

- z : échange vers le haut
- s : échange vers le bas
- q : échange vers la gauche
- d : échange vers la droite

Alignez 3 bonbons ou plus du même type horizontalement ou verticalement pour les faire exploser et gagner des points ! 💥
# Les bonbons 
- `0` : Bonbon classique
- `=` : Bonbon zèbre, explose les bonbons sur la même ligne que lui.
- `#` : Bonbon carré, explose les bonbons autour de lui, même ceux en diagonales.
- `@` : Bonbon disco, explose les bonbons de la même couleur que celui avec lequel il est échangé.

# Compiler
> gcc *.c ./implementation/*.c  -lncurses -Wall