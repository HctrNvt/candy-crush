Pour les cases 
Stocker : 
- 4 pointeurs pour les cases en haut bas droite gauche 
- coordonnées de la case 
- le bonbon sur la case

Plusieurs parties:
- Structuration des données 
- Affichage & interface
- Interaction mécaniques en jeu

# TODO
- Structure pour : bonbon (spécial ou non), niveau, curseur, manager de bonbon

Bonbon : 
- 4 pointeurs pour les bonbons sur les côtés, NULL si rien 
- Couleur
- Aucune fonction

Spécialité de bonbon : 
- symbole
- fonction sur le niveau

Niveau : 
- Une matrice de bonbon
- Nombre de coup max

Manager de bonbon :
Propriétés
- Liste de tout les types de bonbon qui existe
- Liste des spécialités

Fonctions :
- Générateur de bonbon aléatoire
- Remplisseur de niveaux (met des bonbons dans les cases vides en faisant descendre les trucs)
- Fonction pour faire descendre les bonbons
- Réactions aux actions du curseur.

Niveau :
Propriétés
- Matrice de bonbon (avec taille)
- Nombre de coup max

Fonctions : 
- Affichage du niveau

Curseur : 
Propriétés :
- i j : position dans la matrice de bonbon
Fonctions : 
- Aller en haut à droite gauche bas
- Affichage du curseur
- Réaction aux touches (appel à manager de bonbons)
