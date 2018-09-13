#include "header.h"

/**Cette fonction renvoie un joueur vide .
  *C'est à dire une structure joueur dans laquelle on a placé des 0 dans toutes les cases du tableau des bateaux et du tableau des vies 
  *Les autres champs de cette sructure sont mis à 0.
  *Cette fonction est utilisée pour s'assurer que la structure joueur créée est bien remplie de 0 
*/
joueur initialiser_Joueur_Vide(void){ 
  int ligne,colonne;
  joueur res;
  for(ligne=0;ligne<10;ligne++)
    for(colonne=0;colonne<10;colonne++){
      res.tab_Bateau[ligne][colonne] = 0; //remplit les cases du tableau avec du vide 
      if(colonne%2 == 0)
	res.tab_vie[colonne] = 0; //remplit les cases de vie avec que des 0
    }
  res.type_personnage = 0;//toutes les autres variables à zero
  res.capacite = 0;
  res.nbr_bateau_restant = 0;
  res.nbr_tir_reussit = 0;
  res.nbr_tir_manquer = 0;
  res.human = 0;
  res.passe = 0;
  return res;
}

/**Cette fonction verifie si les coordonées rentrées pour definir le debut et la fin d'un bateau sont correctes.
  *C'est à dire qu'ils respectent plusieurs conditions.
  *Ces conditions sont : le nombre de cases entre les premières et les dernières coordonnées doit être séparé par le bon nombre de cases,
  *                      le futur bateau ne doit pas être collé à un autre bateau,
  *                      l'emplacement du futur bateau doit être vide c'est à dire que toutes ses cases doivent être remplies avec des 0,
  *                      les coordonnées rentrées doivent être dans le tableau.
  *Si ces conditions ne sont pas respectées la fonction renvoie 0;
  *La fonction teste également si le bateau sera à l'horizontal ou à la vertical.
  *Si le bateau est à la vertical la fonction renvoie 1 et si il est à l'horizontal la fonction renvoie 2.
*/
int initialiser_Test_Coord(char t[10][10],int ligne,int colonne,int ligne2,int colonne2,int nbr_cases,int human){
  int indice,min,max;
  if(ligne>=10 || ligne<0 || colonne>=10 || colonne<0 || ligne2>=10 || ligne2<0 || colonne2>=10 || colonne2<0){ //verifie que les coordonnées sont dans le tableau
    if(human == 2) //si le placement n'est pas automatique
      printf("ces coordonnées ne sont pas dans le tableau \n"); //dire l'erreur
    return 0;
  }
  if(abs(ligne-ligne2) == (nbr_cases-1)){ //verifie si la distance entre les deux coordonnées est bien egale au nombre de cases du bateau - 1(distance point à point) de plus si c'est placé à l'horizontal ou à la verticale.
    min = MIN(ligne,ligne2); 
    max = MAX(ligne,ligne2);
    if(min-1>=0){//si il y a une ligne avant dans le tableau
      if(t[min-1][colonne] != 0){ //test si il y a un bateau collé sur la ligne avant
	if(human == 2)
	  printf("votre bateau est collé à un autre bateau\n");
	return 0; //si oui le test n'est pas concluant
      }
      if(colonne+1<10) //si y+1 est dans le tableau
	if(t[min-1][colonne+1] != 0){ //test sur la ligne avant du coté droit
	  if(human == 2)
	    printf("votre bateau est collé à un autre bateau\n");
	  return 0; //idem
	}
      if(colonne-1>=0) //idem mais du coté gauche
	if(t[min-1][colonne-1] != 0){
	  if(human == 2)
	    printf("votre bateau est collé à un autre bateau\n");
	  return 0;
	}
    }
    if(max+1<10){//idem mais avec la ligne après
      if(t[max+1][colonne] != 0){
	if(human == 2)
	  printf("votre bateau est collé à un autre bateau \n");
	return 0;
      }
      if(colonne+1<10)
	if(t[max+1][colonne+1] != 0){
	  if(human == 2)
	    printf("votre bateau est collé a un autre bateau\n");
	  return 0;
	}
      if(colonne-1>=0)
	if(t[max+1][colonne-1] != 0){
	  if(human == 2)
	    printf("votre bateau est collé à un autre bateau\n");
	  return 0;
	}
    }
    for(indice=max;indice>=min;indice--){ //verifie si toute les coordonnées sont vide
      if(t[indice][colonne] != 0){ //si non renvoie 0
        if(human == 2)
	       printf("Les coordonnées rentrées ne sont pas libres \n");
	     return 0;
      }
      if(colonne-1>=0)//si il y a une case a gauche
	if(t[indice][colonne-1] != 0){ //test sur le coté gauche de la case du tableau testé
	   if(human == 2)
	    printf("votre bateau est collé à un autre bateau\n");
	  return 0;
	}
      if(colonne+1<10)//si il y a une case a droite
	if(t[indice][colonne+1] != 0){//test sur le coté droit de la case du tableau testé
	  if(human == 2)
	    printf("votre bateau est collé à un autre bateau\n");
	  return 0;
	}
    }
    return 1;  //renvoie 1 donc le test est à la vertical  
  }
  else
    if(abs(colonne-colonne2) == (nbr_cases-1)){ //meme test mais dans l'autre position
      min = MIN(colonne,colonne2);
      max = MAX(colonne,colonne2);
      if(min-1>=0){
	if(t[ligne][min-1] != 0){
	  if(human == 2)
	    printf("votre bateau est collé à un autre bateau\n");
	  return 0;
	}
	if(ligne+1<10)
	  if(t[ligne+1][min-1] != 0){
	    if(human == 2)
	      printf("votre bateau est collé à un autre bateau\n");
	    return 0;
	  }
	if(ligne-1>=0)
	  if(t[ligne-1][min-1] != 0){
	    if(human == 2)
	      printf("votre bateau est collé à un autre bateau\n");
	    return 0;
	  }
      }
      if(max+1<10){
	if(t[ligne][max+1] != 0){
	  if(human == 2)
	    printf("votre bateau est collé à un autre bateau\n");
	  return 0;
	}
	if(ligne+1<10)
	  if(t[ligne+1][max+1] != 0){
	    if(human == 2)
	      printf("votre bateau est collé à un autre bateau\n");
	    return 0;
	  }
	if(ligne-1>=0)
	  if(t[ligne-1][max+1] != 0){
	    if(human == 2)
	      printf("votre bateau est collé à un autre bateau\n");
	    return 0;
	  }
      }
      for(indice=max;indice>=min;indice--){
	if(t[ligne][indice] != 0){
	  if(human == 2)
	    printf("Les coordonnées rentrées ne sont pas libres \n");
	  return 0;
	}
	if(ligne-1>=0)
	  if(t[ligne-1][indice] != 0){
	    if(human == 2)
	      printf("votre bateau est collé à un autre bateau\n");
	    return 0;
	  }
	if(ligne+1<10)
	  if(t[ligne+1][indice] != 0){
	    if(human == 2)
	      printf("votre bateau est collé à un autre bateau\n");
	    return 0;
	  }
      }
      return 2;//renvoie 2 donc le test est à l'horizontal
    }
    else
      if(human == 2)//si c'est placé automatiquent pas nécessaire de le préciser
	printf("les coordonnées ne sont pas séparées par le bon nombre de cases \n"); //si le mouvenment n'est ni horizontal ni vertical 
  return 0; //renvoie 0 (test non concluant)
  
}

/**Cette fonction affiche le tableau en remplacant les cases vides par des 0 et le reste des cases par leurs valeurs en ASCII.
  *Elle est surtout utilisée pour afficher le tableau de bateaux en cas de modifications ou de validation par l'utilisateur. 
*/
void affichage(char t [10][10]){ 
  int ligne,colonne;
  for(ligne=0;ligne<10;ligne++){//parcourt le tableau
    for(colonne=0;colonne<10;colonne++){
      if(t[ligne][colonne] == 0) //si c'est vide 
        printf("0");//on affiche un 0
      printf("%c ",t[ligne][colonne]);//sinon on affiche le caractère
    }
    printf("\n");
  }
}

/**Cette fonction renvoie un nombre aléatoire non généré entre 0 et n.
  *Cette fonction doit être précédée de srand((unsigned)time(NULL)); pour générer des nombres aléatoires non identique à chaque utilisation.
   */
int rand_n(int n) { 
    int partSize   = 1 + (n == RAND_MAX ? 0 : (RAND_MAX - n) / (n + 1)); 
    int maxUsefull = partSize * n + (partSize - 1); 
    int draw; 
    
    do { 
        draw = rand(); 
    } while (draw > maxUsefull); 
  
    return draw / partSize; 
}

/**Fonction utilisée pour utiliser correctement le scanf notamment évité un buffer overflow.
  *Cette fonction ne prend que deux caractères(signifiés par %2s) et les transforme en entier avec la fonction srtol.
  *Elle effectue différents tests pour vérifier scanf.
  *Ces tests sont : verifier le nombre de caracère lu par scanf qui doit être de 2,
  *                 on verifie si les caractères entrées sont bien des entiers avec la verification du deuxième argument de strtol,
  *                 l'entier ne doit pas être négatif.
  *Si ces tests ne sont pas concluants la fonction renvoie -1 sinon elle renvoie l'entier lu
*/
int mon_scanf(){  
  int entier,test;
  char caract[3];
  char *reste;
  test=scanf("%2s",caract); //test reçoit le nombre de caractere lu par scanf
  if(test>2){ //si y en a plus de 2 
    scanf ("%*[^\n]"); //vide le buffer
    getchar ();
    return -1; //renvoie -1 pour signaler que l'allocation s'est mal déroulée
  }
  entier = strtol(caract,&reste,10); //entier reçoit le premier entier et reste pointe sur la suite
  if(reste == caract){//si la suite de l'entier est au début cela veut dire que ce n'est pas un entier qui a été rentré
    scanf ("%*[^\n]");//vide le buffer
    getchar ();
    printf("vous n'avez pas rentré un entier\n"); //le signale à l'utilisateur 
    return -1;//renvoie -1 pour signifier que l'allocation s'est mal déroulée
  }
  if(entier < 0)
    printf("Vous avez rentré une valeur négative  \n"); 
  scanf ("%*[^\n]");//vide le buffer
  getchar ();
  return entier;//renvoie l'entier
  
}
  
  
/**Cette fonction initialise les bateaux des joueurs en utilisant les fonctions précédentes pour tester si les placements sont correctes.
  *Elle demande à l'utilisateur les coordonéées des bateaux si le choix n'est pas automatique(valeur de auto_bateau).
  *Si les tests sont tous concluant place les bateaux avec leurs valeurs dans tab_Bateau.
  */
void initialiser_Bateau_Joueur(joueur *j,int auto_bateau){
  int indice,cases,ligne,colonne,ligne2,colonne2,min,indice2,test;
  cases = 5;//le 1er bateau est composé de 5 cases
  ligne = 0;
  colonne = 0;
  srand((unsigned)time(NULL)); //srand pour générer des nombres différents à chaque fois 
  printf("Bonjour nous allons initialiser vos bateaux \n");
  if(j->type_personnage == 4){ //si c'est un nécromant
    printf("Puisque que vous etes un necromant votre bateau de 5 cases perd une case et vous gagnez une mine sur votre grille qui est placée aléatoirement \n"); 
    cases--; //son bateau de 5 perd 1 vie
    while(1){ 
      ligne=rand_n(9); //place aléatoirement une mine
      colonne=rand_n(9);
      //printf(" x= %d y == %d \n",x,y);
      if(j->tab_Bateau[ligne][colonne] == 0){ //si la position du tableau est libre
	j->tab_Bateau[ligne][colonne] = '*'; //place une mine
	ligne=0;
	colonne=0;
	break;
      }
    }
  }
  for(indice=1;indice<6;indice++){ //fait tout les test pour 5 bateaux
    if (auto_bateau == 2){ //si le placement n'est pas automatique
      affichage(j->tab_Bateau);
      do{
	printf("veuillez rentrer les première coordonnées du bateau numero %d de %d cases \nligne=",indice,cases);
	ligne = mon_scanf(); //demander au joueur les coordonnées du début du bateau
      }
      while(ligne < 0); //tant que la saisie est incorrecte
      do{
	printf("\ncolonne=");
	colonne = mon_scanf();
      }
      while(colonne < 0);
      printf("\n");
      do{
	printf("veuillez rentrer les coordonnées de fin du bateau numero %d de %d cases \nligne=",indice,cases);
	ligne2 = mon_scanf(); //et les coordonnées de fin du bateau
      }
      while(ligne2 < 0); //tant que la saisie est incorrecte
      printf("\ncolonne=");
      do
	colonne2 = mon_scanf();
      while(colonne2 < 0);//tant que la saisie est incorrecte
      printf("\n");
      ligne--;//on soustraie 1 pour avoir les indices du tableau
      colonne--;
      ligne2--;
      colonne2--;
    }
    else{ //si le placement est automatique
      ligne = rand_n(9);//on obtient un chiffre au hasard entre 0 a 9 pour les coordonnées du bateau
      colonne = rand_n(9);
      if(ligne%2 == 0){ //si la coordonnée ligne est pair
        if(colonne%2 == 0) //si la coordonnée y est pair
          if(initialiser_Test_Coord(j->tab_Bateau,ligne,colonne,ligne+(cases-1),colonne,cases,auto_bateau)){ //si c'est possible
            ligne2 = ligne+(cases-1); //place un bateau à la vertical vers le bas
            colonne2 = colonne;
          }
          else{ //sinon vers le haut
	    ligne2 = ligne-(cases-1);
	    colonne2 = colonne; 
          } 
        else{ //sinon 
          if(initialiser_Test_Coord(j->tab_Bateau,ligne,colonne,ligne-(cases-1),colonne,cases,auto_bateau)){ //si c'est possible
            ligne2 = ligne-(cases-1);//place un bateau à la vertical vers le haut
            colonne2 = colonne;
          }
          else{ //sinon vers le bas
	    ligne2 = ligne+(cases-1);
	    colonne2 = colonne; 
          } 
        }
      }
      else{//sinon 
	if(colonne%2 == 0)
	  if(initialiser_Test_Coord(j->tab_Bateau,ligne,colonne,ligne,colonne+(cases-1),cases,auto_bateau)){ //si c'est possible
            ligne2 = ligne; 
            colonne2 = colonne+(cases-1); //place un bateau à l'horizontal vers la droite
          }
          else{ // sinon
	    ligne2 = ligne;
	    colonne2 = colonne-(cases-1);  //place un bateau à l'horizontal vers la gauche
          } 
        else{//sinon
          if(initialiser_Test_Coord(j->tab_Bateau,ligne,colonne,ligne,colonne-(cases-1),cases,auto_bateau)){//si c'est possible
            ligne2 = ligne;
            colonne2 = colonne-(cases-1); //place un bateau à l'horizontal vers la gauche
          }
          else{//sinon
	    ligne2 = ligne;
	    colonne2 = colonne+(cases-1);//place un bateau à l'horizontal vers la droite
          } 
        } 
      }
    }
    test = initialiser_Test_Coord(j->tab_Bateau,ligne,colonne,ligne2,colonne2,cases,auto_bateau); //test si les coordonnées sont correctes (plus connaitre type de mouvements)
    if(test == 1){ //mouvement à la vertical
      min = MIN(ligne,ligne2);
      for(indice2=(MAX(ligne,ligne2));indice2>=min;indice2--){ 
	j->tab_Bateau[indice2][colonne] = indice+48; //remplit les cases du tableau pour symboliser le tableau 
      }
    }
    else
      if(test == 2){ //mouvement à l'horizontal
	min = MIN(colonne,colonne2);
	for(indice2=MAX(colonne,colonne2);indice2>=min;indice2--){
	  j->tab_Bateau[ligne][indice2] = indice+48; //remplit les cases du tableau pour symboliser le tableau 
	}
      }
      else //si test non concluant on recommence avec le meme numero de bateau
	indice--;
    if(indice!=3 && test){
      j->tab_vie[indice-1] = cases+48; //met le nombre de cases du bateau dans le tableau de vie
      cases --;//decrémente cases pour passer à un autre bateau
    }
    if(indice == 3 && test) //si c'est égale à 3 rajoute son nombre de cases dans le tableau de vie
      j->tab_vie[indice-1] = cases+48;
    if(j->type_personnage == 4 && j->capacite == 1 && indice== 1){ // si c'est un nécromant 
      j->capacite = 0; //il perd egalement sa capacité
      cases++; //on incrémente cases pour qu'il replace un bateau à 4 cases
    }
    if(test)
      clrscr();
  }
  j->nbr_bateau_restant = (indice-1)+48; //remplit le nbr de bateau restant avec le nombre de bateau générés
  
}
/**Si le mode de jeu est avec les classes alors cette fonction présente les différentes classes possibles et renvoie la valeur de la classe choisie.
  */
int initialisation_Classe_Choix(void){ 
  int choix=0;
  printf("Bonjour vous allez choisir votre classe\n");
  printf("Vous possédez comme choix les classes suivantes :\n");
  printf("1.La classe Pirate (permet de placer des mines au début)\n");
  printf("2.La classe capitaine (revèle 6 cases du tableau)\n");
  printf("3.La classe canonnier (permet de tirer une fois un tir de 4 cases aléatoirement) \n");
  printf("4.La classe Nécromant (le bateau de 5 cases perd une case et une mine est placée aléatoirement)\n");
  do{
    choix = mon_scanf();
    if((choix<=0 || choix > 7)) 
      printf("vous n'avez pas rentré un choix valide\n");
  }
  while(choix<=0 || choix > 4 ); //tant que la saisie est invalide, resaisir un choix
  return choix; //renvoie le choix
}

/**Cette fonction est utilisée pour remplir un tableau notamment le champ tab_Bateau du joueur avec des 0 partout.
  *Elle est surtout utilisée pour remettre à 0 le tableau si un joueur n'est pas satisfait du placement de ses Bateaux.
  */
void efface(char t[10][10]){  
  int ligne,colonne;
  for(ligne=0;ligne<10;ligne++)
    for(colonne=0;colonne<10;colonne++)
      t[ligne][colonne] = 0;
}

/**Fonction utilisée pour le pouvoir de la classe Pirate.
  *Elle permet donc de placer des mines dans tab_Bateau.
  *Ces mines sont definies par la valeur '*' dans le tableau.
  *Bien entendu les coordonnées données pour le placement des mines sont testées(vide et ne dépasse pas tableau) .
  */
void initialisation_Classe_Mine(joueur *j){
  int ligne,colonne,ok,mine,auto_mine,sur;
  mine = 1; //on commence à la première mine
  auto_mine = 1;//par defaut le placement est automatique
  sur = 1; //on est sur de notre choix par defaut
  srand((unsigned)time(NULL)); //utilisé pour avoir des nombres différents à chaque fois
  do{ 
    if(j->human == 0){ //si le joueur est humain 
      printf("Bonjour nous allons placer vos mines\n");
      do{
	printf("Voulez-vous placer aléatoirement vos mines ? \n1/Oui 2/Non \n"); //demander si on veut placer les mines automatiquement
	auto_mine = mon_scanf();
	clrscr();
	if(auto_mine!= 1 &&  auto_mine !=2) //si erreur de choix
	  printf("Ceci n'est pas un choix valide \n"); //l'indiquer
      }
      while(auto_mine != 1 && auto_mine !=2); //tant que la saisie est invalide
    }
    while(mine != 4){ //tant que mine est différent de 4
      if(auto_mine == 2){ //si le placement n'est pas automatique
	do{
	  ok = 0;
	  affichage(j->tab_Bateau);
	  printf("Veuillez rentrer la ligne de la mine numero %d\n",mine); //demander les coordonnées de la mine
	  ligne  = mon_scanf(); 
	  if(ligne<=0 || ligne >10) //si la coordonnée donné n'est pas dans le tableau
	    printf("la coordonnée rentrée n'est pas dans le tableau\n");  //l'indiquer
	}while(ligne<=0 || ligne >10); //tant que la coordonnée rentrée n'est pas dans le tableau
	do{//idem pour colonne
	  printf("Veuillez rentrer la colonne de la mine numero %d\n",mine); 
	  colonne = mon_scanf();
	  if(colonne<=0 || colonne >10)
	    printf("la coordonnée rentrée n'est pas dans le tableau\n");
	}while(colonne<=0 || colonne >10);
	ligne--;//on décremente pour avoir les indices du tableau 
	colonne--;
      }
      else{ //si le placement est automatique 
	ligne = rand_n(9); //tire la ligne et la colonne aléatoirement
	colonne = rand_n(9);
      }
      clrscr(); //clear le terminal
      if(j->tab_Bateau[ligne][colonne] != 0) //si la case est déja occupée 
	printf("Les coordonnées rentrées ne sont pas libres\n"); //l'indiquer
      else{ //sinon
	j->tab_Bateau[ligne][colonne] = '*'; //on place la mine
	ok = 1; //le placement s'est bien passé
      }
      if(ok) //si le placement s'est bien passé
	mine ++; //on peut passer à la mine suivante 
    }
    if(j->human == 0){ //si c'est un humain
      do{ // faire tant que la saisie n'est pas valide
	affichage(j->tab_Bateau);
	printf("Cela vous convient-il ?\n1/Oui 2/Non \n"); //demander si le placement des mines est satisfaisant pour le joueur
	sur = mon_scanf(); 
	clrscr();
	if(sur!= 1 &&  sur !=2) //si le choix n'est pas valide
	  printf("Ceci n'est pas un choix valide \n"); //l'indiquer
      }
      while(sur != 1 && sur !=2); 
      if(sur == 2){ //si le joueur n'est pas satistisfait
	efface(j->tab_Bateau); //on efface la grille
	mine = 1; //on repart à la première mine
      }
    }
  }
  while(sur == 2);//tant que le joueur n'est pas satisfait de son placement
}

/**Si le mode avec les classes est actif alors cette fonction initialise la classe du joueur passée en paramètre.
  *Pour cela elle fait appel aux fonctions précèdentes initialisation_Classe_Choix et initialisation_Classe_Mine.
  *Si c'est une ia choisit sa classe aléatoirement.
  */
void initialisation_Classe_Total(joueur *j){ 
  int test;
  test = 0;
  srand((unsigned)time(NULL));
  if(!j->human) //si le joueur est humain
    j->type_personnage = initialisation_Classe_Choix(); //demander son choix
  else //sinon
    while(test == 0){ //tant que ce n'est pas bon
      j->type_personnage = rand_n(4); //tirer aléatoirement la classe du personnage
      if(j->type_personnage != 0) //si le chiffre n'est pas 0
	test = 1; //c'est bon
    }
  j->capacite = 1; //le joueur gagne une capacité
  if(j->type_personnage == 1){ //si c'est un pirate
    initialisation_Classe_Mine(j); //il place ses mines 
    j->capacite = 0; //   perd donc sa capacité
  }
}

/**Fonction qui rassemble toutes les fonctions d'initialisation ensemble pour pouvoir assurer l'initialisation des deux joueurs correctement ia ou non.
  *Effectue en premier l'initialisation du joueur 1 avec le placement de ses bateaux plus le choix de sa classe.
  *Demande à l'utilisateur si il veut que le placement de ses bateaux se fasse automatiquement.
  *A le fin de son initialisation demande si le joueur est sur de son choix sinon il peut rechoisir son placement de bateux et sa classe.
  *Effectue la même chose pour le joueur 2.
  */ 
void initialisation_Total(joueur *j1,joueur *j2,int game,int ia){ 
  int choix_auto,sur;
  sur= 1; //on est sur de notre choix par defaut
  clrscr();//on clear
  printf("Bonjour joueur 1\n");
  do{
    *j1 = initialiser_Joueur_Vide(); //on initialise un joueur vide
     j1->num = 1;//initialise le numero de joueur
     if(ia == 2) //si il y a 2 ia 
       j1->human = 1; //j1 est marqué comme une ia
     if(game == 2) //si on autorise le jeu avec les classes
       initialisation_Classe_Total(j1); //on passe par l'initialisation de la classe
     if(j1->human==0){ //si le joueur est humain
      do{
	printf("Voulez vous placer automatiquement ou non vos bateaux ?\n1/oui 2/non \n"); //demande si le joueur veut placer automatiquement ses bateaux
	choix_auto = mon_scanf();
	clrscr();
	if(choix_auto <= 0 || choix_auto>2) //si le choix n'est pas valide
	  printf("ceci n'est pas un choix valide \n"); //l'indiquer
      }
      while(choix_auto <= 0 || choix_auto>2); //si ce n'est pas valide recommencer
    }
     else if (j1->human==1) //si c'est une ia
       choix_auto=1; //le placement sera obligatoirement automatique
    initialiser_Bateau_Joueur(j1,choix_auto);//appelle la fonction pour initialiser les bateaux des joueurs
    if(j1->human==0){ //si le joueur est humain
      do{
	affichage(j1->tab_Bateau); //demander si il ne veut pas tout rechoisir
	printf("Etes-vous sur de votre choix ?\n1/oui 2/non\n");
	sur = mon_scanf();
	clrscr();
	if(sur <= 0 || sur>2) //si le choix n'est pas valide
	  printf("Ceci n'est pas un choix valide \n"); //l'indiquer
      } 
      while(sur <= 0 || sur>2);//si le choix n'est pas valide recommencer
    }
  }while(sur == 2); //si le joueur n'est pas satisfait de son choix recommencer
  clrscr(); //clear pour cacher la grille du joueur 1
  sur = 1;
  printf("Bonjour joueur 2\n");
  do{//idem que le joueur 1
    *j2 = initialiser_Joueur_Vide();
    j2->num = 2;
    if(ia == 1 || ia == 2) //sauf qu'il suffit d'avoir une seule ia
      j2->human = 1;
    if(game == 2)
      initialisation_Classe_Total(j2);
    if(j2->human==0){
      do{
	printf("Voulez vous placer automatiquement ou non vos bateaux ?\n1/oui 2/non  \n");
	choix_auto = mon_scanf();
	clrscr();
	if(choix_auto <= 0 || choix_auto>2)
	  printf("ceci n'est pas un choix valide \n");
      }
      while(choix_auto <= 0 || choix_auto>2);
    }
    else if(j2->human==1)
      choix_auto=1;
    initialiser_Bateau_Joueur(j2,choix_auto);//idem
    if(j2->human==0){
      do{
	affichage(j2->tab_Bateau);
	printf("Etes-vous sur de votre choix ?\n1/oui 2/non\n");
	sur = mon_scanf();
	clrscr();
	if(sur <= 0 || sur>2)
	  printf("Ceci n'est pas un choix valide \n");
      }
      while(sur <= 0 || sur>2);
    }
  }while(sur == 2);
}

