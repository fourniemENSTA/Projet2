#include <stdio.h>
#include <stdlib.h>
#include "BE_note.h"


liste newList(){

	
	liste mynewlist; 
	mynewlist.suivant = NULL; 
	
	return mynewlist; 
}


noeud *nouveauNoeud(void* c){

	noeud *newNode = (noeud*) malloc(sizeof(noeud)); 
	newNode->contenu = c; 
	newNode->suivant = NULL; 
 
	return newNode; 
}


article nouvelArticle(char* n, int p, int q ){

	article *a = malloc(sizeof(article)); 
	a->nom = n; 
	a->prix = p; 
	a->quantite = q; 
	
	return *a; 
	
}



noeud* queue(liste l){
	if (l.suivant != NULL) {
		if ((*l.suivant).suivant == NULL) {
			return l.suivant;
		}
		else
		{
			liste l2 = newList();
			l2.suivant = (*l.suivant).suivant;
			queue(l2);
		}
	} 
		return NULL; 
} 



int ajouteEnQueue(liste l , noeud* n) {
	if (l.suivant != NULL) {
		if (l.suivant->suivant == NULL) {
			l.suivant->suivant = n;
			return 0;
		}
		else
		{
			liste l2 = newList();
			l2.suivant = l.suivant->suivant;
			return ajouteEnQueue(l2, n); 
		}
		return -1;
	}
	return -1; 
}


// truc bizarre, marches pas. 
int ajouteEnTete(liste *l, noeud* n) {
	if (n != NULL) {
		if (l->suivant == NULL) {
			l->suivant = n; 
			return 0; 
		}
		else {
			n->suivant = l->suivant; 
			l->suivant = n; 
			return 0; 
		}
	}
	else
	{
		return -1; 
	}
}

// AFFICHE UNE LISTE D'ENTIERS
void affiche(liste l) {
	if (l.suivant != NULL) {
		printf("%d \n", *((int*)l.suivant->contenu));
		if (l.suivant->suivant != NULL) {
		liste l2 = newList();
		l2.suivant = l.suivant->suivant;
		affiche(l2);
		}
	}
}

// AFFICHE LES PRIX D'UNE LISTE D'ARTICLES	

void affichearticle(liste l) {
	if (l.suivant != NULL) {
		printf("%d \n", ((int) ((article*) l.suivant->contenu)->prix));
		if (l.suivant->suivant != NULL) {
			liste l2 = newList();
			l2.suivant = l.suivant->suivant;
			affichearticle(l2);
		}
	}
}



int facture(liste l) {
	if (l.suivant != NULL) {
		if (l.suivant->suivant != NULL) {
			liste l2 = newList();
			l2.suivant = l.suivant->suivant;
			return *((int*)l.suivant->contenu) + facture(l2); 
		}
		else {
			return *((int*)l.suivant->contenu);
		}

	}
	else {
		return 0; 
	}
}


liste exemple() {
	liste l = newList(); 
	article* a = malloc(sizeof(article)); 
	article* b = malloc(sizeof(article));
	article* c = malloc(sizeof(article));

	a->nom = "pat";
	a->prix = 12; 
	a->quantite = 20; 

	b->nom = "cat"; 
	b->prix = 2; 
	b->quantite = 5; 

	c->nom = "bat"; 
	c->prix = 3; 
	c->quantite = 6; 

	noeud* na = nouveauNoeud((void*)a); 
	noeud* nb = nouveauNoeud((void*)b);
	noeud* nc = nouveauNoeud((void*)c);

	l.suivant = na; 
	na->suivant = nb; 
	nb->suivant = nc; 


	return l; 

}

article ArticleComplet() {

	printf("Entrez le nom de l'article");
	char n[256];
	scanf("%s", &n);

	printf("Entrez le prix de l'article");
	int p = 0;
	scanf("%d", &p);
	

	printf("Entrez la quantite");
	int q = 0; 
	scanf("%i", &q);
	article *a = malloc(sizeof(article));
	*a = nouvelArticle(n,p,q);
	return *a; 
}



int ajouteDansListeTriee(liste l, article a) {
	if (l.suivant != NULL) {
		if (l.suivant->suivant == NULL) {
			noeud *n = nouveauNoeud((void*)&a);
			l.suivant->suivant = n;
			return 0;
		}
		else
		{
			noeud* n = nouveauNoeud((void*)&a);
			if (((article*)(l.suivant->contenu))->prix > a.prix) {
				ajouteEnQueue(l, n);
			}
			else {

				liste *l2 = malloc(sizeof(liste));
				l2->suivant = l.suivant->suivant;
				noeud* n = nouveauNoeud((void*)l.suivant);
				ajouteDansListeTriee(*l2, a);
				ajouteEnTete(&l2, n);

			}
		}
		return -1;
	}
	return -1;
}

liste tri(liste *l) {
	if (l->suivant == NULL) {
		return newList();
	}
	else {
		liste *l2 = malloc(sizeof(liste));
		l2->suivant = l->suivant->suivant;

		ajouteDansListeTriee(tri(l2), *(article*) l->suivant->contenu); 

	}
}



int main(){
	
	int a = 10, b = 11, c = 12, d = 13; 
	liste l = newList(); 
	noeud* na = nouveauNoeud((void*) &a); 
	l.suivant = na; 

	noeud* nb = nouveauNoeud((void*)&b); 
	noeud* nc = nouveauNoeud((void*)&c);
	noeud* nd = nouveauNoeud((void*)&d); 

	na->suivant = nc; 
	ajouteEnQueue(l, nd);
	//ajouteEnTete(&l, nd); 
	liste l3 = exemple(); 

	affichearticle(l3);
	
	ajouteDansListeTriee(l3, nouvelArticle("nom", 4, 10)); 



		
	// TEST DE AFFICHE()
	affichearticle(l3);
/*
// TEST DE FACTURE()
	printf("%d \n",facture(l)); 

// TEST de ARTICLECOMPLET()

	article *art = malloc(sizeof(article)); 
	*art = ArticleComplet(); 
	printf("nom :%s \n prix : %d \ quantite : %d", art->nom,art->prix, art->quantite);



	// TEST de QUEUE() // 
	noeud *nq = l.suivant;
	noeud *nq2 = queue(l);

	printf("%d \n", *((int*) nq->contenu));
	printf("%d \n", *((int*) nq2->contenu));
*/

	system("PAUSE"); 

	return 0; 
}
