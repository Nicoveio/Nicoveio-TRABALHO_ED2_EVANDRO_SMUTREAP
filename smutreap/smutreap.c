#include "smutreap.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

 
typedef struct boundingBox{
	double x1, x2, y1, y2;
}boundingBox;
typedef struct NodeST{
	double x,y;
	int prioridade;
	Info info;
	DescritorTipoInfo descritor;
	int hits;
	struct NodeST *dir, *esq;
	boundingBox *bb;

}NodeST;

typedef struct SmuTreapImp{
	NodeST *raiz;
	int hitCount;
	double promotionRate;
	double epsilon;

}SmuTreapImp;


NodeST* rotateLeft(NodeST* node);
NodeST* rotateRight(NodeST* node);
NodeST* insertSmuTAux(NodeST *atual, double x, double y, double epsilon, Info i, DescritorTipoInfo d, FCalculaBoundingBox fCalcBb);
void atualizaBoundingBox(NodeST* node);
NodeST* promoteNodeSmuTAux(NodeST* raiz, NodeST* n, double epsilon);
Node getNodeSmuTAux(NodeST*raiz, SmuTreapImp*t, double x, double y);
NodeST* removeNoSmuTAux(NodeST*raiz, NodeST*no, double epsilon);


SmuTreap newSmuTreap(int hitCount, double promotionRate, double epsilon){
	if (hitCount<1 || promotionRate<0.00)return NULL;
	SmuTreapImp *arvore = (SmuTreapImp*)malloc(sizeof(SmuTreapImp));
	arvore->raiz=NULL;
	arvore->hitCount = hitCount;
	arvore->promotionRate=promotionRate;
	arvore->epsilon=epsilon;
	return arvore;
}


Node insertSmuT(SmuTreap t, double x, double y, Info i, DescritorTipoInfo d,
		FCalculaBoundingBox fCalcBb){
	if(t==NULL|| fCalcBb==NULL)return NULL;
	else{
		SmuTreapImp*treap = (SmuTreapImp*)t;
		treap->raiz = insertSmuTAux(treap->raiz, x, y, treap->epsilon, i, d, fCalcBb);
		return (Node)treap->raiz;
	}
}



NodeST* insertSmuTAux(NodeST *atual, double x, double y, double epsilon, Info i, DescritorTipoInfo d, 
	FCalculaBoundingBox fCalcBb){
	if(atual==NULL){
		NodeST*aux = (NodeST*)malloc(sizeof(NodeST));
		aux->bb = (boundingBox*)malloc(sizeof(boundingBox));
		if(aux == NULL )return NULL;
		if(aux->bb == NULL){
			free(aux);
			return NULL;
		}
		aux->x= x;
		aux->y = y;
		aux->prioridade= rand();
		aux->info=i;
		aux->descritor = d;
		aux->dir=aux->esq = NULL;
		double xa, ya, wa, ha;
		fCalcBb(d, i, &xa, &ya, &wa, &ha);
		aux->bb->x1 = xa;
		aux->bb->y1 = ya;
        aux->bb->x2 = xa + wa;
        aux->bb->y2 = ya + ha;

        atualizaBoundingBox(aux);
        return aux;
    }


        if (fabs(x - atual->x) < epsilon && fabs(y - atual->y) < epsilon) {

        return atual;
    }
    if(x < atual->x - epsilon || (fabs(x - atual->x) < epsilon && y < atual->y - epsilon)){
    	atual->esq =insertSmuTAux(atual->esq, x, y, epsilon, i, d, fCalcBb);

    	if(atual->esq && atual->esq->prioridade>atual->prioridade)
    		return rotateRight(atual);
    	
    }else {
    	atual->dir = insertSmuTAux(atual->dir, x, y, epsilon, i, d, fCalcBb);

    	if(atual->dir&& atual->dir->prioridade>atual->prioridade)
    		return rotateLeft(atual);

	}

    atualizaBoundingBox(atual);
	return atual;
}
NodeST* rotateLeft(NodeST* node) {
    if (!node || !node->dir) return node; 
    
    NodeST* newRoot = node->dir;   
    node->dir = newRoot->esq;      
    newRoot->esq = node;

    atualizaBoundingBox(node);
    atualizaBoundingBox(newRoot);           
    
    return newRoot;  
}

NodeST* rotateRight(NodeST* node) {
    if (!node || !node->esq) return node; 
    
    NodeST* newRoot = node->esq;   
    node->esq = newRoot->dir;      
    newRoot->dir = node;

    atualizaBoundingBox(node);
    atualizaBoundingBox(newRoot);           
    
    return newRoot;  
}

void atualizaBoundingBox(NodeST* node) {
    if (!node) return;

   
    double x1 = node->bb->x1;
    double y1 = node->bb->y1;
    double x2 = node->bb->x2;
    double y2 = node->bb->y2;

    
    if (node->esq) {
        if (node->esq->bb->x1 < x1) x1 = node->esq->bb->x1;
        if (node->esq->bb->y1 < y1) y1 = node->esq->bb->y1;
        if (node->esq->bb->x2 > x2) x2 = node->esq->bb->x2;
        if (node->esq->bb->y2 > y2) y2 = node->esq->bb->y2;
    }

    
    if (node->dir) {
        if (node->dir->bb->x1 < x1) x1 = node->dir->bb->x1;
        if (node->dir->bb->y1 < y1) y1 = node->dir->bb->y1;
        if (node->dir->bb->x2 > x2) x2 = node->dir->bb->x2;
        if (node->dir->bb->y2 > y2) y2 = node->dir->bb->y2;
    }

    
    node->bb->x1 = x1;
    node->bb->y1 = y1;
    node->bb->x2 = x2;
    node->bb->y2 = y2;
}


Node getNodeSmuT(SmuTreap t, double x, double y){
    SmuTreapImp* arvore = (SmuTreapImp*)t;
    return getNodeSmuTAux(arvore->raiz, arvore,  x, y);
}
Node getNodeSmuTAux(NodeST*raiz, SmuTreapImp*t, double x, double y){

    if(raiz==NULL)return NULL;

    if((x+t->epsilon)<raiz->bb->x1 || (x-t->epsilon)>raiz->bb->x2 || (y+t->epsilon)<raiz->bb->y1 
        || (y-t->epsilon)>raiz->bb->y2)
        return NULL;
    double distanciaPontos = sqrt (pow(raiz->x - x, 2) + pow(raiz->y -y, 2));

    if(distanciaPontos<= t->epsilon){
        raiz->hits +=1;
        if( raiz->hits == t->hitCount)
            promoteNodeSmuT((SmuTreap)t, (Node)raiz, t->promotionRate);

        return (Node)raiz;
    }

   if (x < raiz->x - t->epsilon || 
   (fabs(x - raiz->x) <= t->epsilon && y < raiz->y - t->epsilon))

    return getNodeSmuTAux(raiz->esq, t, x, y);

   else if (x > raiz->x + t-> epsilon || 
        (fabs(x - raiz->x) <= t->epsilon && y > raiz->y + t->epsilon))

    return getNodeSmuTAux(raiz->dir, t,  x, y);



}

DescritorTipoInfo getTypeInfoSrbT(SmuTreap t, Node n) {
    NodeST* no = (NodeST*)n;
    return no->descritor;
}


void promoteNodeSmuT(SmuTreap t, Node n, double promotionRate){
    SmuTreapImp*arvore = (SmuTreapImp*)t;
    NodeST *no = (NodeST*)n;
    no->prioridade *=promotionRate;
    arvore->raiz = promoteNodeSmuTAux(arvore->raiz, no, arvore->epsilon);
}

NodeST* promoteNodeSmuTAux(NodeST* raiz, NodeST* n, double epsilon){

    if(raiz==NULL || n==raiz)return raiz;

   if(n->x < raiz->x - epsilon || (fabs(n->x - raiz->x) < epsilon && n->y < raiz->y - epsilon))
        raiz->esq =promoteNodeSmuTAux(raiz->esq, n, epsilon );
        else raiz->dir = promoteNodeSmuTAux (raiz->dir, n, epsilon);

    if(raiz->esq != NULL && raiz -> esq->prioridade > raiz->prioridade)
    raiz = rotateRight (raiz);
    else if (raiz->dir !=NULL && raiz ->dir->prioridade > raiz->prioridade)
    return raiz = rotateLeft(raiz);


    return raiz;    


}


void removeNoSmuT(SmuTreap t, Node n){
    SmuTreapImp*arvore = (SmuTreapImp*)t;
    NodeST*node = (NodeST*)n;
    arvore->raiz = removeNoSmuTAux(arvore->raiz, n, arvore->epsilon);
}

NodeST* removeNoSmuTAux(NodeST*raiz, NodeST*no, double epsilon){
    if(raiz==NULL)return NULL;

    if(raiz==no){
        if(raiz->esq ==NULL && raiz->dir==NULL){
            free(raiz->bb);
            free(raiz);
            return NULL;
        }else if(raiz->esq!=NULL && (raiz->dir ==NULL 
            || raiz->esq->prioridade>raiz->dir->prioridade)){
            raiz = rotateRight(raiz);
            raiz->dir=removeNoSmuTAux(raiz->dir, no, epsilon);
        }else{
            raiz = rotateLeft(raiz);
            raiz->esq=removeNoSmuTAux(raiz->esq, no, epsilon);
        }
    }
    else if(no->x < raiz->x - epsilon 
        || (fabs(no->x - raiz->x) < epsilon && no->y < raiz->y - epsilon))
        raiz->esq = removeNoSmuTAux (raiz->esq, no, epsilon);
    else raiz->dir = removeNoSmuTAux(raiz->dir, no, epsilon);

    atualizaBoundingBox(raiz);
    return raiz;

}

Info getInfoSmuT(SmuTreap t, Node n){
    return ((NodeST*)n)->info;
}

Info getBoundingBoxSmuT(SmuTreap t, Node n, double *x, double *y, double *w, double *h){
    if (n==NULL)return NULL;

    NodeST* no = (NodeST*)n;
    *x = no->bb->x1;
    *y = no->bb->x2;
    *w = no->bb->x2 - no->bb->x1;
    *h = no->bb->y2 - no->bb->y1;

}


