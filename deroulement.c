#include "header.h"
/** Cette fonction permet de générer un tir aléatoire sur une case disponible.
 *Celle-ci tire aléatoirement en vérifiant que la case est libre, si la case n'est pas libre, on recommence le tir aléatoire.
 *une fois la position validée on renvoie la case ciblée
*/
Case tir_ia(joueur *j){
  Case cible;
  cible.case_ligne=0;
  cible.case_colonne=0;
  do{
    cible.case_ligne=rand_n(9)+1;
    cible.case_colonne=rand_n(9)+1;
  }
  while(j->tab_Bateau[cible.case_ligne-1][cible.case_colonne-1] <0);
  return cible;
}

/** Cette fonction permet de dévoiler toutes les cases autour d'un bateau coulé.
 *Le principe est le suivant: on cherche l'extrémité du bateau touché, ensuite on parcours ses cases une par une en dévoilant les cases à proximitées
*/
void devoile_case(joueur *j, Case cible){
  char valeur_bateau, direction; // valeur_bateau sert à connaitre quel bateau est touché, direction : 1 = en ligne , 2 = en colonne

  valeur_bateau= j->tab_Bateau[cible.case_ligne-1][cible.case_colonne-1];
  // cherche la direction
  if( j->tab_Bateau[cible.case_ligne-2][cible.case_colonne-1] == valeur_bateau || j->tab_Bateau[cible.case_ligne][cible.case_colonne-1] == valeur_bateau ){
    direction=1;
  }
  if( j->tab_Bateau[cible.case_ligne-1][cible.case_colonne-2] == valeur_bateau || j->tab_Bateau[cible.case_ligne-1][cible.case_colonne] == valeur_bateau ){
    direction=2;
  }
  
 //atteint le haut ou la gauche du bateau
  while( (cible.case_ligne != 1)  && (j->tab_Bateau[cible.case_ligne-2][cible.case_colonne-1] == valeur_bateau) ){
    cible.case_ligne--;
  }

  while( (cible.case_colonne != 1)  && (j->tab_Bateau[cible.case_ligne-1][cible.case_colonne-2] == valeur_bateau) ){
    cible.case_colonne--;
  }

 // dévoile les cases autour du bateau
  if(direction==1){
    if(cible.case_ligne>1){
      j->tab_Bateau[cible.case_ligne-2][cible.case_colonne-1]=-9;
    }
    
    while(j->tab_Bateau[cible.case_ligne-1][cible.case_colonne-1] == valeur_bateau){
      if(cible.case_colonne >1){
        j->tab_Bateau[cible.case_ligne-1][cible.case_colonne-2]=-9;
      }
      if(cible.case_colonne <10){
        j->tab_Bateau[cible.case_ligne-1][cible.case_colonne]=-9;
      }
      cible.case_ligne++;
    }
    
    if(cible.case_ligne<10){
      j->tab_Bateau[cible.case_ligne-1][cible.case_colonne-1]=-9;
    }

  }


  else if(direction==2){
    if(cible.case_colonne>1){
      j->tab_Bateau[cible.case_ligne-1][cible.case_colonne-2]=-9;
    }
    
    while(j->tab_Bateau[cible.case_ligne-1][cible.case_colonne-1] == valeur_bateau){
      if(cible.case_ligne >1){
        j->tab_Bateau[cible.case_ligne-2][cible.case_colonne-1]=-9;
      }
      if(cible.case_ligne <10){
        j->tab_Bateau[cible.case_ligne][cible.case_colonne-1]=-9;
      }
      cible.case_colonne++;
    }

    if(cible.case_colonne<10){
      j->tab_Bateau[cible.case_ligne-1][cible.case_colonne-1]=-9;
    }
  }


}

/** Cette fonction permet de renvoyer les coordonnées d'une case pour pouvoir tirer dessus. Ces coordonnées sont demandées au joueur placé en argument.
 *La variable C est de type "Case" qui est une structure comportant deux valeurs, utilisées comme coordonnées.
 */
Case tir(joueur *j){//J, Où on tir ?
  int ligne=-1,colonne=-1;
  Case c;
  printf("Joueur %d, quelle case visez-vous?",j->num); 
  while(ligne>10||ligne<1){ //coordonnée ligne
    printf("\nligne=");
    scanf("%d",&ligne);
  }
  while(colonne>10||colonne<1){//coordonnée colonne
    printf("\ncolonne=");
    scanf("%d",&colonne);
  }
  c.case_ligne=ligne;
  c.case_colonne=colonne; 
  return c;
}
    

///Petite fonction qui regarde si tous les bateaux sont coulés via le tableau de points de vie des bateaux dans la structure du joueur.
int death(joueur *j){//Joueur,es-tu mort?
  int i;
  for(i=0;i<5;i++){
    if(j->tab_vie[i]!='0')
      return 0;
  }
  return 1;
}

/** Cette fonction intervient après une des fonctions de tir. Elle permet de visualiser la valeur à l'interieur de la case et d'agir en fonction.
 *Si il y a une étoile c'est que l'on a tiré sur une mine (capacité d'une classe du jeu), on passe donc un tour.
 *Si c'est -9, c'est que l'on a déja tiré sur cette case.
 *Si c'est 0, il n'y a rien dans cette case (il y a de l'eau) "plouf".
 *Sinon un bateau est touché et on enlève une unité du tableau de point de vie du joueur. Le Bateau touché est celui du chiffre dans la case (Si la case contient 3, le bateau 3 est touché), le joueur rejouera (la variable t passe à 1).
 *Si les points de vie du bateau touché tombent à 0, on coule le bateau et on libère les cases à coté du bateau coulé car deux bateaux ne peuvent pas etre collés.
 */
int cible(joueur *j,Case c){//Je tir ici, que se passe-t-il?
  int i;//pour la boucle
  int t=0;//pour le cas d'un bateau touché
  if(j->tab_Bateau[c.case_ligne-1][c.case_colonne-1]=='*'){//tir sur mine
    printf("\nVous etes tombé sur une mine, vous perdez un tour\n");
    j->tab_Bateau[c.case_ligne-1][c.case_colonne-1]=8;
    return 2;
  }
  if(j->tab_Bateau[c.case_ligne-1][c.case_colonne-1]<0)//déja tiré ici
    printf("\nDésolé,vous avez déja tiré ici\n");
  else if(j->tab_Bateau[c.case_ligne-1][c.case_colonne-1]==0){//rien ici
    printf("\nPlouf!!, un tir dans l'eau\n");
    j->tab_Bateau[c.case_ligne-1][c.case_colonne-1]=-9;
  }
  else{
    i = j->tab_Bateau[c.case_ligne-1][c.case_colonne-1];//un bateau est touché
    j->tab_vie[i-1-48]--;//-1 vie pour ce bateau
    printf("\ntouché ");
    j->tab_Bateau[c.case_ligne-1][c.case_colonne-1]=j->tab_Bateau[c.case_ligne-1][c.case_colonne-1]*-1;
    if(j->tab_vie[i-1 - 48]=='0'){//coulé?
      printf("et coulé ");
      devoile_case(j,c);
    }
    printf("!! \n Vous rejouez\n");
    
    t=1;

  
  }
  
  return t;
}

/** Cette fonction sert à utiliser le pouvoir du capitaine .C'est à dire découvrir des cases du tableau sans les toucher.
  *Les cases découvertes sont sélectionnées aléatoirement sur le tableau entier et sont au nombre de 6 .
  *Les cases que le capitaine decouvre sont des cases vides ou des bateaux non touchés.
  *On ajoute 20 à ces cases pour signifier le fait que la case est visible.
*/
void capitaine_Decouverte(joueur *j){
  int mouettes;
  int x,y;
  mouettes = 6;
  while(mouettes > 0){
    x = rand_n(9);
    y = rand_n(9);
    if(j->tab_Bateau[x][y] >= 0){
      printf("avant = %d \n",j->tab_Bateau[x][y]);
      j->tab_Bateau[x][y] += 20;
      mouettes--;
      printf("x== %d y== %d t = %d\n",x+1,y+1,j->tab_Bateau[x][y]);
    }
  }
}

void tout_bateau(joueur *j){
  int x,y;
  for(x=0;x<10;x++)
    for(y=0;y<10;y++)
      j->tab_Bateau[x][y] = '1';
}

/** Cette fonction est la fonction au centre du jeu. Elle définit le systeme de tour.
 *On place une boucle infinie avec comme seule sortie la défaite d'un joueur.
 *On fait jouer le joueur 1,il choisit si il utilise son pouvoir ou non, il tire, il regarde la case où il a tiré, le jeu agit en conséquence.
 *Si le joueur à touché un bateau,on le fait rejouer. Si il utilise son pouvoir ou qu'il touche une mine on incrémente la variable passe, qui fera passer le prochain tour.
 *La boucle fait jouer le joueur 2 de la meme façon.
 */
int deroulement(joueur *j1,joueur *j2){ 
  Case c;//Case visée 
  int t;//Si on touche 
  int oui;//Sert pour questionner le joueur et pour le pouvoir canonnier
  
  while(1){ 
    /////joueur 1//// 
    affiche(j1,j2);
    if(j1->passe==0){//J1 doit-il jouer?(Ou saute-t-il son tour?)
      if(j1->human==0){//Est-il humain?
	if(j1->capacite != 0){//A-t-il un pouvoir utilisable?
	  printf("\nJ1 voulez-vous utiliser votre pouvoir?(1=oui, autre=non)\n");
	  scanf("%d",&oui);
	  if(oui==1){
	    //tout_bateau(j2);
	    if(j1->type_personnage == 2){//Pouvoir Capitaine
	      capitaine_Decouverte(j2);
	      j1->capacite = 0;//Il utilise donc son pouvoir unique.
	      j1->passe++;//Il devra passer un tour.
	      printf("Vous devez passer un tour \n");
	      affiche(j1,j2);
	    }
	    if(j1->type_personnage == 3){//Canonnier
	      oui=4;//4 tirs
	      while(oui>0){
		c=tir_ia(j2);
		t=cible(j2,c); 
		if(t==2){//Tir sur mine
		  t=0;
		  j1->passe++;//Il passera son prochain tour.
		  printf("Vous devez passer un tour \n");
		}
		oui--;
	      }
	      j1->passe++;//Il devra passer une tour.
	      j1->capacite = 0;//Il utilise sa capacité unique.
	      affiche(j1,j2);
	    }
	  }
	}
	c=tir(j1);//Il tire.
      }
	else
	  c=tir_ia(j2);//Ia tire.
	t=cible(j2,c); 
	if(t==2){//Tir sur mine
	  t=0;
	  j1->passe++;//Il devra passer un tour.
	  printf("Vous devez passer un tour \n");
	}
	if(death(j2)){//Gagne-t-il? */
	  affiche(j1,j2);
	  printf("\n\nJoueur 1, vous avez gagné.\n\n"); 
	  return 0; 
	} 
	while(t){//Si il touche, il tire à nouveau.
	  affiche(j1,j2);
	  if(j1->human==0) 
	    c=tir(j1); 
	  else
	    c=tir_ia(j2);
	  t=cible(j2,c); 
	  if(t==2){//Tir sur mine
	    t=0;
	    j1->passe++;//Il passera un tour.
	    printf("Vous devez passer un tour \n");
	  }
	  if(death(j2)){//Gagne-t-il? */
	    affiche(j1,j2);
	    printf("\n\nJoueur 1, vous avez gagné.\n\n");
	    return 0; 
	  } 
	}
    }
    else{//Il doit passer un tour donc il ne fait rien.
      j1->passe--;//Un tour est passé.
    }
    ////joueur 2//// 
    affiche(j1,j2);
    if(j2->passe==0){//J2 doit-il jouer?(Ou saute-t-il son tour?)
      if(j2->human==0){//Est-il humain?
	if(j2->capacite != 0){//A-t-il un pouvoir utilisable?
	  printf("\nJ2 voulez-vous utiliser votre pouvoir?(1=oui, autre=non)\n");
	  scanf("%d",&oui);
	  if(oui==1){
	    //tout_bateau(j1);
	    if(j2->type_personnage == 2){//Pouvoir capitaine
	      capitaine_Decouverte(j1);
	      j2->type_personnage = 0;//Utilisation du pouvoir unique.
	      j2->passe++;//Il passera un tour.
	      printf("Vous devez passer un tour \n");
	      affiche(j1,j2);
	    }
	    if(j2->type_personnage == 3){//Pouvoir canonnier
	      oui=4;//4 tirs
	      while(oui>0){
		c=tir_ia(j1);
		t=cible(j1,c); 
		if(t==2){//Tir sur mine
		  t=0;
		  j2->passe++;//Il passera un tour.
		  printf("Vous devez passer un tour \n");
		}
		oui--;
	      }
	      j2->capacite = 0;//Utilisaton capacité unique.
	      j2->passe++;//Il passera un tour.
	      affiche(j1,j2);
	    }
	  }
	}
	c=tir(j2);//Tir du j2 
      }
      else 
	c=tir_ia(j1);//Tir du j2 
      t=cible(j1,c); 
      if(t==2){//Tir sur mine
	t=0;
	j2->passe++;//Il passera un tour.
	printf("Vous devez passer un tour \n");
      }
      if(death(j1)){//Gagne-t-il? 
	affiche(j1,j2);
	printf("\n\nJoueur 2, vous avez gagné.\n\n"); 
	return 0; 
      } 
      while(t){//Si il touche il rejoue.
	affiche(j1,j2);
	if(j2->human==0)
	  c=tir(j2);//Tir du j2 
	else 
	  c=tir_ia(j1);//Tir du j2 
	t=cible(j1,c);
	if(t==2){//Tir sur mine
	  t=0;
	  j2->passe++;//Il passera un tour.
	  printf("Vous devez passer un tour \n");
	}
	if(death(j1)){//Gagne-t-il? 
	  affiche(j1,j2);
	  printf("\n\nJoueur 2, vous avez gagné.\n\n");
	  return 0; 
	}
      }
    }
    else//Il doit passer un tour.
      j2->passe--;
  }
  return 0; 
}
