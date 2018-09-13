#include"header.h"

/**!\brief Fonction lectrice de fichier file.
 *
 * Elle servira majoritairement voir uniquement à la lecture des
 * règles car les logs seront lus par une autre fonction.
 */
void read(char* nom){
  FILE* texte = NULL;//!texte: Pointeur sur fichier.
  texte = fopen(nom,"r");
  int caractere= 0;//!caractere: Permet la collecte de caractères.
  if(texte==NULL){
    fprintf(stderr,"Il vous manque le fichier %s , vérifiez vos fichiers \n",nom);
    return;
  }
  while((caractere=fgetc(texte)) != EOF)
    fprintf(stderr,"%c",caractere);
  return;
}

/**!\brief Fonction lectrice de fichier file en format log.
 *
 * Elle lit les fichiers file sous un format "log", c'est à dire
 * qu'elle ira lire un certain nombre de lignes à la fin d'un 
 * fichier au fur et à mesure que l'on écrit dedans.
 * Le nombre de lignes correspond au nombre de lignes voulu,
 * affiché de type format log.(Affiche les x dernières du file).
 */
void read_log(char* nom,int nombre_de_lignes){
  FILE* log = fopen(nom,"r");//!log: Pointeur sur fichier.
  int caractere=0;//!caractere: Permet la collecte de caractères.
  int compteur1;//!compteur1: Itérateur.
  if((caractere=(fgetc(log)))==EOF)
    return;  
  fseek(log,-1,SEEK_END);
  for(compteur1=0 ; compteur1<=nombre_de_lignes && (caractere=fgetc(log))!=EOF ; fseek(log,-2,SEEK_CUR) ){
    if(caractere=='\n')
      compteur1++;
    if(ftell(log)-1==SEEK_SET){
      fseek(log,0,SEEK_SET);
      break;
    }
  }
  if(ftell(log)!=SEEK_SET)
    fseek(log,2,SEEK_CUR);
  printf("-----------------------------------------------\n");
  while((caractere=fgetc(log))!=EOF)
    printf("%c",caractere);
  printf("-----------------------------------------------\n");
  return;
}

/**!\brief Fonction du Menu.
 * 
 * Fonction apparaissant dans le main affichant le menu et
 * renvoyant un int servant à paramétrer le type de partie voulu.
 * return 1 = Joueur contre Joueur.
 * return 2 = Joueur versus IA.
 * return 3 = IA versus IA.
 * return 4 = Affiche les règles.
 * return 5 = Sort du programme.
 * Dans le prototype:
 * clear    = Détermine si l'on veut clrscr et afficher la bannière.
 .
 * boucle   = Évite de boucler dans la fonction menu(niveau récursif).
 */

int menu(int clear,int boucle){
  char choix='0';//!choix: Permet la saisie sécurisée des choix.
  if(clear)
    clrscr();
  couleur(JAUNE);
  if(clear)
    banniere();
  choices();
  couleur(ROUGE);
  printf("Que voulez-vous faire à présent?\n");
  couleur("0");
  if(boucle==-1)
    return 0;
  while(choix=='0'){
    scanf("%c",&choix);
    switch(choix){
    case '1':
      //JvsJ
      return 1;
    case '2':
      //JvsIA
      return 2;
    case '4':
      read("Regles.txt");
      choix='0';
      menu(0,-1);
      break;
    case '5':
      credits();
      choix='0';
      menu(0,-1);
      break;
    case '6':
      exit(0);
      break;
    case '3':
      //IA VS IA
      return 3;
    default:
      couleur("0");
      choix='0';
      break;
    }
  }
  return 0;
}

/**!\brief Fonction de type prédicat binaire purement graphique.
 * 
 * Purement graphique car la fonction est un void et aucune
 * valeur n'est retournée. Elle s'aide du tableau de points de vie.
 * Le résultat est affiché dans la composition.
 * X (rouge) = Représente un bateau totalement détruit.
 * V (vert)  = Représente un bateau ayant au moins une case non détruite.
 */

void alive(char health[5],int type){
  couleur("0");
  if(health[type]=='0'){
    couleur(GRAS);
    couleur(ROUGE);
    printf("X");
    couleur("0");
  }else{
    couleur(GRAS);
    couleur(VERT);
    printf("V");
    couleur("0");
  }
  return;
}

/**!\brief Fonction d'affichage de la barre de vie.
 * 
 * Fonction utilisant un calcul du total de points de vie à l'aide
 * du tableau de vie d'un joueur pour afficher une barre de vie
 * dynamique.
 */

void health_bar(char health[5]){
  int total_hp=0;//!total_hp: Variable servant à stocker le total de points de vie.
  int compteur1;//!compteur1: Itérateur.
  couleur("0");
  couleur(GRAS);
  for(compteur1=0 ; compteur1<5 ; compteur1++)
    total_hp+=health[compteur1]-48;
  couleur(VERT);
  for(compteur1=0 ; compteur1<total_hp ; compteur1++)
    printf("o");
  couleur(ROUGE);
  for(compteur1=0 ; compteur1<17-total_hp ; compteur1++)
    printf("x");
  couleur("0");
}

/**!\brief Fonction d'affichage de la composition.
 * 
 * La composition contient le nom et la couleur des joueurs ainsi
 * que les bateaux de leur équipe et leurs états (détruit ou non).
 */

void affiche_composition(char j1 [5],char j2 [5]){ // Fonction qui affiche la composition
  //Player + health
  couleur(BLEU);
  couleur(GRAS);
  printf("\tJoueur 1\t");
  couleur("0");
  couleur(BLANC);
  printf("|");
  couleur(MAGENTA);
  couleur(GRAS);
  printf("\t Joueur2\n   ");
  health_bar(j1);
  printf("\t|   ");
  health_bar(j2);
  printf("\n");
  //Team
  //Porte avion
  couleur(BLANC);
  printf("Porte-avion:");
  alive(j1,4);
  printf("\t\t");
  couleur(BLANC);
  printf("|Porte-avion:");
  alive(j2,4);
  printf("\n");
  //Croiseur
  couleur(BLANC);
  printf("Croiseur:");
  alive(j1,3);
  printf("\t\t");
  couleur(BLANC);
  printf("|Croiseur:");
  alive(j2,3);
  printf("\n");
  //Contre Torpilleur
  couleur(BLANC);
  printf("Contre-Torpilleur:");
  alive(j1,2);
  printf("\t");
  couleur(BLANC);
  printf("|Contre-Torpilleur:");
  alive(j2,2);
  printf("\n");
  //Sous-marin
  couleur(BLANC);
  printf("Sous-marin:");
  alive(j1,1);
  printf("\t\t");
  couleur(BLANC);
  printf("|Sous-marin:");
  alive(j2,1);
  printf("\n");
  //Torpilleur
  couleur(BLANC);
  printf("Torpilleur:");
  alive(j1,0);
  printf("\t\t");
  couleur(BLANC);
  printf("|Torpilleur:");
  alive(j2,0);
  printf("\n");
}
 
/**!\brief Fonction d'affichage de la grille.
 * 
 * Affiche la grille à l'aide de trois boucles, la première sert
 * à décompter le nombre de lignes tandis que les deux autres gèrent
 * les lignes des deux tableaux séparément.
 * C'est aussi ici que se fait l'affichage des différents pouvoirs 
 * et de ce qui doit etre montré ou caché.
 * C'est la fonction coeur de l'affichage.
 */

void grille(char tab1[10][10],char tab2[10][10]){
  int compteur1;//!Compteur1: Itérateur.
  int compteur2;//!Compteur2: Itérateur.
  couleur(JAUNE);
  couleur(GRAS);
  printf("   1 2 3 4 5 6 7 8 9 10\t");
  couleur("0");
  printf("|");
  couleur(JAUNE);
  couleur(GRAS);
  printf("   1 2 3 4 5 6 7 8 9 10\n");
  couleur("0");  
  for(compteur1=0;compteur1<10;compteur1++){// Boucle ligne
    couleur(GRAS);
    couleur(JAUNE);
    if(compteur1<9)
      printf("%d ",compteur1 + 1);
    else
      printf("%d",compteur1 + 1);
    couleur("0");
    for(compteur2=0;compteur2<10;compteur2++){//Boucle colonne du premier tableau
      //Tir dans l'eau
      if(tab1[compteur1][compteur2]==-9){
	couleur(ROUGE);
	printf("%2c",'O');
	continue;
      }
      //Élements cachés
      if( ( tab1[compteur1][compteur2]== '*' || tab1[compteur1][compteur2]==0) || ((tab1[compteur1][compteur2]>'0') && (tab1[compteur1][compteur2]<'7'))){
	couleur(CYAN);	
	printf("%2c",'0');
       	continue;
      }
      //Mouette dans l'eau
      if((tab1[compteur1][compteur2]-20) ==0){
	couleur(BLANC);	
	printf("%2c",'O');
	continue;
      }
      //Mouette sur un bateau
      if((tab1[compteur1][compteur2]-20)>'0' && (tab1[compteur1][compteur2]-20)<'7'){
	couleur(BLANC);	
	printf("%2c",'B');
	continue;
      }
      //Mouette sur une mine
      if((tab1[compteur1][compteur2]-20)=='*'){
	couleur(BLANC);
	printf("%2c",'*');
	continue;
      }
      //Bateau touché
      if(tab1[compteur1][compteur2]<0 && tab1[compteur1][compteur2]!=8 && tab1[compteur1][compteur2]!=-9){
	couleur(ROUGE);
	printf("%2c",'X');
	continue;
      }
      //Mine touchée
      if(tab1[compteur1][compteur2]==8){
	couleur(ROUGE);
	printf("%2c",'*');
	continue;
      }
    }
    couleur("0");
    printf("\t|");
    couleur(GRAS);
    couleur(JAUNE);
    if(compteur1<9)
      printf("%d ",compteur1 + 1);
    else
      printf("%d",compteur1 + 1);
    couleur("0");
    for(compteur2=0;compteur2<10;compteur2++){ // Boucle colonne du deuxieme tableau
      //Idem J2
      if(tab2[compteur1][compteur2]==-9){
	couleur(ROUGE);
	printf("%2c",'O');
	continue;
      }
      if( ( tab2[compteur1][compteur2]== '*' || tab2[compteur1][compteur2]==0) || ((tab2[compteur1][compteur2]>'0') && (tab2[compteur1][compteur2]<'7'))){
	couleur(CYAN);	
	printf("%2c",'0');
	continue;
      }
      if((tab2[compteur1][compteur2]-20)==0){
	couleur(BLANC);	
	printf("%2c",'O');
	continue;
      }
      if((tab2[compteur1][compteur2]-20)>'0' && (tab2[compteur1][compteur2]-20)<'7'){
	couleur(BLANC);	
	printf("%2c",'B');
	continue;
      }
      if((tab2[compteur1][compteur2]-20)==8){
	couleur(BLANC);	
	printf("%2c",'*');
	continue;
      }
      if(tab2[compteur1][compteur2]<0 && tab2[compteur1][compteur2]!=8 && tab2[compteur1][compteur2]!=-9){
	couleur(ROUGE);
	printf("%2c",'X');
	continue;
      }

      if(tab2[compteur1][compteur2]==8){
	couleur(ROUGE);
	printf("%2c",'*');
	continue;
      }
    }
    printf("\n");
  }
  couleur("0");
}

/*!\brief Fonction d'affichage de la bannière.
 * 
 * Ouai enfin... Voila tout est dit.
 */

void banniere(){
  couleur(JAUNE);
  printf("\t\t\tCrazy Battle\n");
  couleur(CYAN);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
  
  couleur(JAUNE);
  printf(" Bienvenue dans notre bataille navale, attention ça va couler!\n");
  couleur(CYAN);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  couleur("0");
}

/**!\brief Fonction d'affichage des choix du menu.
 * 
 * Affichage simple à l'aide de printf et de codes couleurs 
 * représentant les choix du menu. 
 */

void choices(){ // Affiche les choix donnés au joueur lors du menu
  //1. Jouer en mode Joueur vs Joueur
  couleur(CYAN);
  printf("1. Jouer en mode ");
  couleur(BLEU);
  printf("Joueur");
  couleur(JAUNE);
  printf(" vs ");
  couleur(BLEU);
  printf("Joueur\n");
  //2. Jouer en mode Joueur vs IA
  couleur(CYAN);
  printf("2. Jouer en mode ");
  couleur(BLEU);
  printf("Joueur");
  couleur(JAUNE);
  printf(" vs ");
  couleur(ROUGE);
  printf("IA\n");
  //3. Jouer en mode IA vs IA
  couleur(CYAN);
  printf("3. Jouer en mode ");
  couleur(ROUGE);
  printf("IA");
  couleur(JAUNE);
  printf(" vs ");
  couleur(ROUGE);
  printf("IA\n");
  //4.Voir les règles
  couleur(CYAN);
  printf("4.");
  couleur(JAUNE);
  printf(" Voir les règles\n");
  //5.Credits
  couleur(CYAN);
  printf("5. ");
  couleur(ROUGE);
  printf("C");
  couleur(JAUNE);
  printf("r");
  couleur(BLANC);
  printf("e");
  couleur(MAGENTA);
  printf("d");
  couleur(VERT);
  printf("i");
  couleur(ROUGE);
  printf("t");
  couleur(MAGENTA);
  printf("s\n");
  couleur("0");
  //6. Quitter
  couleur(CYAN);
  printf("6. ");
  couleur(ROUGE);
  printf("Quitter\n");
  couleur("0");
}

/**!\brief Fonction d'affichage des crédits.
 * 
 * Affichage simple à l'aide de printf et de codes couleurs 
 * représentant les créateurs de ce magnifique programme
 * ainsi que leurs roles dans sa réalisation.
 */

void credits(){
  //RÉALISATEUR 1
  couleur(ROUGE);
  printf("\n\nRÉALISATION\t");
  couleur(VERT);
  printf("NICOLAS\t");
  couleur(JAUNE);
  printf("LOEW\t");
  couleur(MAGENTA);
  printf("\t13406903\n");
  //RÉALISATEUR 2
  couleur(ROUGE);
  printf("RÉALISATION\t");
  couleur(VERT);
  printf("VINCENT\t");
  couleur(JAUNE);
  printf("MUNOZ\t");
  couleur(MAGENTA);
  printf("\t13401747\n");
  //INITIALISATION
  couleur(BLANC);
  printf("INITIALISATION\t");
  couleur(VERT);
  printf("MICHEL\t");
  couleur(JAUNE);
  printf("SROUJI\t");
  couleur(MAGENTA);
  printf("\t13401881\n");
  //GRAPHIQUE
  couleur(CYAN);
  printf("G");
  couleur(ROUGE);
  printf("R");
  couleur(JAUNE);
  printf("A");
  couleur(BLANC);
  printf("P");
  couleur(MAGENTA);
  printf("H");
  couleur(VERT);
  printf("I");
  couleur(ROUGE);
  printf("Q");
  couleur(MAGENTA);
  printf("U");
  couleur(BLANC);
  printf("E\t");
  couleur(VERT);
  printf("GAETAN\t");
  couleur(JAUNE);
  printf("GOUSSEAUD\t");
  couleur(MAGENTA);
  printf("13402498\n\n\n");
  couleur("0");
}

/**!\brief Fonction d'affichage de jeu "globale".
 * 
 * Elle englobe les fonctions nécessaires à l'affichage en partie.
 * C'est un peu "l'interface de jeu".
 */

void affiche(joueur *j1,joueur *j2){
  clrscr();
  banniere();
  couleur(JAUNE);
  affiche_composition(j1->tab_vie,j2->tab_vie);
  grille(j1->tab_Bateau,j2->tab_Bateau);
  read_log("log.txt",5);
}

