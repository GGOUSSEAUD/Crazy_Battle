/**
\mainpage Bienvenue sur la documentation de Crazy Battle!

Les règles:\n
La bataille navale est un jeu à deux joueurs (ordinateur ou humains) consistant à bombardé les bateaux adverses, la carte est tamponné d'un « brouillard » cachant les bateaux. Les joueurs doivent donc tiré à « l'aveugle ». Le joueur choisis les coordonnées du tir sur une case non découverte de la grille (non joué) dans l'espoir de touché un bateau adverse, si l'adversaire est touché, le joueur rejoue. La composition des bateaux est la même pour les deux joueurs, ils sont placés au début de la partie par ces derniers. On ne peut pas coller des bateaux donc si un bateau est coulé cela libère les cases aux alentours. 

Les classes:\n
-Nécromant\n
-Pirate\n
-Canonnier\n
-Capitaine\n

Les réalisateurs:

RÉALISATION	NICOLAS	LOEW		13406903\n
RÉALISATION	VINCENT	MUNOZ		13401747\n
INITIALISATION	MICHEL	SROUJI		13401881\n
GRAPHIQUE	GAETAN	GOUSSEAUD	13402498\n

*/
#include <stdio.h> // inclus pour l'affichage
#include <stdlib.h> // inclus pour l'IA (utilsation de rand/srand)
#include <time.h> // inclus pour la gestion du temps
#define MAX(a,b) a>b ? a : b //macro qui renvoie la plus grande des deux valeur
#define MIN(a,b) a<b ? a : b //macro qui renvoie la plus petite des deux valeur
#define clrscr() printf("\033[H\033[2J") // Definition de la fonction de nettoyage d'écran
#define couleur(param) printf("\033[%sm", param) //Fonction servant à afficher des couleurs dans le terminal
//Codes couleur
#define GRAS "1"
#define INVERSE "7"
#define NOIR "30"
#define ROUGE "31"
#define VERT "32"
#define JAUNE "33"
#define BLEU "34"
#define MAGENTA "35"
#define CYAN "36"
#define BLANC "37"
// Structure joueur, comporte tout les éléments qui modélise la partie d'un joueur
typedef struct joueur
{
  char tab_Bateau[10][10]; // Tableau Représentant la grille contenant les bateaux
  char tab_vie[5];	// Tableau comportant les points de vies restants des bateaux
  char type_personnage;	// Variable indiquant le type du personnage choisis
  char capacite;	// Variable indiquant si la capacité est disponible
  char nbr_bateau_restant;	// Variable indiquant le nombre bateau restant
  char nbr_tir_reussit;	// Variable indiquant le nombre de tirs réussis
  char nbr_tir_manquer;	// Variable indiquant le nombre de tirs manqués
  char human;	// variable indiquant si le joueur est un humain ou une IA
  int num; //numéro du joueur
  char passe; //indique le nombre de tours que le joueur ne peut pas joué

}joueur;

//Initialisation
joueur initialiser_Joueur_Vide(void);//renvoie un joueur vide
int initialiser_Test_Coord(char[10][10],int,int,int,int,int,int); //test les coordonnées pour savoir si le placement de bateau est respecté
void affichage(char[10][10]); //affiche la grille
int rand_n(int); //fonction qui génère de l'aléatoire
int mon_scanf(void); //fonction qui teste les entrées de scanf
int initialisation_Classe_Choix(void); //dit les différentes possibilité pour les classes et renvoie celui choisit 
void efface(char [10][10]);  //met toute les valeurs de la grille a 0
void initialisation_Classe_Mine(joueur *);  //initialise les mines d'un joueur (classe pirate)
void initialisation_Classe_Total(joueur *);   //initialise totalement la classe du joueur
void initialiser_Bateau_Joueur(joueur*,int); //initialiser les bateau des joueurs
void initialisation_Total(joueur*,joueur*,int,int);  //effectue toute l'initialisation 

//Affichage
void read(char*); // Fonction qui lit les .txt
void read_log(char*,int);//Fonction servant à lire les log
int menu(int,int);// Fonction du menu principale
void alive(char [5],int); //Affiche si un bateau est en vie ou nom
void health_bar(char [5]);// Creer une barre de vie
void affiche_composition(char [5],char [5]);// Affiche les noms et composition des équipes
void grille(char [10][10],char [10][10]);//Affiche la grille de jeu
void banniere(void);// Affiche la banniere
void choices(void);// Affichage des Choix du menu
void credits(void);// Affichage des credits
void affiche(joueur*,joueur*);// Affichage en jeux




//Déroulement
typedef struct Case{
  int case_ligne;// ligne
  int case_colonne;// colonne
}Case;
Case tir_ia(joueur *);//Tir de l'ia
void devoile_case(joueur *, Case );//Si on détruit un bateau on montre les cases à coté
Case tir(joueur*);//Tir d'un humain
int death(joueur*);//Le joueur est-il vivant ?
int cible(joueur*,Case );//Qu'y a-t-il sous la case dont on a tiré dessus
void capitaine_Decouverte(joueur *);//Pouvoir du Capitaine
int deroulement(joueur *,joueur *);//Déroulement du jeu
