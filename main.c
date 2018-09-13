#include "header.h"

int main(void){
  int choix,game,ia;
  choix = 0;
  joueur *j1 = malloc(sizeof(joueur));
  joueur *j2 = malloc(sizeof(joueur));
  while(1){ //boucle infinie qui break dans le menu
  ia = 0;
  choix=menu(1,0);// on appelle le menu pour nous proposer des choix
  printf("Bonjour\n"); 
  do{
    printf("Voulez vous jouer a: \nla bataille navale 1/normale ou 2/avec des classes \n"); //on demande si les joueurs veulent jouer a la bataille navale normal ou avec des classes
    game=mon_scanf();
    clrscr();
  }while(game != 1 && game != 2); //tant que la saisie n'est pas correcte on recommence
  if(choix == 2)//si on choisit joueur vs ia 
    ia=1; //on signale qu'il y a une ia 
  if(choix == 3)//si on choisit ia vs ia 
    ia=2; //on signale qu'il y a deux ia
  initialisation_Total(j1,j2,game,ia); //on fait l'initialisation des deux joueurs 
  deroulement(j1,j2); //on applique le deroulement
}
  return 0; 
}
