

struct Noeud {

	struct Noeud *suivant; 
	void *contenu;

};


struct Article{

	char* nom; 
	int prix; 
	int quantite;

};


typedef struct Noeud noeud;
typedef struct Article article; 



struct Liste {

	noeud * suivant; 

};


typedef struct Liste liste;




liste newList(); 
noeud *nouveauNoeud(void* c); 
article nouvelArticle(char* n, int p, int q ); 
noeud* queue(liste); 
int ajouteEnTete(liste*, noeud*); 
int ajouteEnQueue(liste, noeud*); 
