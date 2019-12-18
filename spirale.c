#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


//Salvataggio database circolare
//vantaggio: tempo di ricerca dimezzato

typedef struct nodo{
  int val;
  struct nodo *next, *prec;
  bool capo;
} nodo_t;

nodo_t* freeSpirale(nodo_t*testa, nodo_t**posto){
  if(*posto!=testa){
    nodo_t* app=*posto;
    app=app->next;
    free(*posto);
    *posto=NULL;
    return freeSpirale(testa, &app);
  }
  return NULL;
}

nodo_t* nuovoNodoSpirale(nodo_t* testa, int val){
  nodo_t* nuovo=(nodo_t*)malloc(sizeof(nodo_t));
  nuovo->val=val;
  nuovo->capo=false;

  if(testa==NULL){
    nuovo->next=nuovo;
    nuovo->prec=nuovo;
    nuovo->capo=true;
    testa=nuovo;
  }

  else{
  nodo_t* corr=testa;
  while(corr->next!=testa){
    corr=corr->next;
  }
  testa->prec=nuovo;
  corr->next=nuovo;
  nuovo->next=testa;
  nuovo->prec=corr;
  }

  return testa;
}

void visualizza(nodo_t* testa){
  if(testa!=NULL){
  nodo_t* corr=testa;
  printf("TESTA-> ");
  while(corr->next!=testa){
    printf(" %d",corr->val);
    corr=corr->next;
  }
  //stampa ultimo
  printf(" %d ",corr->val);
  printf("TESTA->\n");
 }
}

nodo_t* ordina(nodo_t* testa){
  if (testa && testa->next) {
  for(nodo_t* pi = testa; pi->next->capo!=true; pi=pi->next){
    for (nodo_t *pj = pi->next; pj->capo!=true; pj=pj->next){ 
                if (pj->val < pi->val){
                  int app=pi->val;
                  pi->val=pj->val;
                  pj->val=app;
                }
   }
	}
  }
	return testa;
}

bool trova(nodo_t * p, int n){
    p=ordina(p);
    if (p && p->next && p->next->capo!=true) {
      nodo_t* pi=p;
      int nodi=0;

      while (pi->next->capo!=true) {
        nodi++;
        pi=pi->next;
      }
      nodi++; //conta anche l'ultimo
      int valMax=pi->val;

      if(n<=valMax){ //////////////////////////////////////////////////////////////////////////////////
      printf("\n\nIl valore forse esiste!\n");
      pi=p;

      int conta=0;
      while (conta<nodi/2 && pi->val!=n) { //sposto il puntatore al nodo in meta
        conta++;
        pi=pi->next;
      }

      printf("num nodi:%d; val a meta:%d; valMax:%d\n",nodi, pi->val, valMax);
      int salti=0;
      bool f=false;

      if(n>pi->val) { //check se maggiore della meta, se si imposto il nodo corr "p" all'ultimo nodo
        f=true;
        pi=p->prec;
      }
      else pi=p; //altrimenti imposto il nodo alla posizione iniziale, cioè alla testa della lista

      printf("n è maggiore del valore a meta? : %d\n",f );

      if(nodi%2!=0) nodi++;

      while (salti<=nodi/2) {
           printf("numero di salti eseguiti=%d, valore in considerazione:%d\n",salti, pi->val);
           if(pi->val==n) return true;
           salti++;

           if(f) pi=pi->prec; //check di procedimento, se il flag è TRUE allora mi sposto sempre indietro
           else pi=pi->next;

           if(f && pi->val<n) return false; //double check in coda
           if(!f && pi->val>n) return false;
         }
    }
  }////////////////////////////////////////////////////////////////////////////////////////////////////////
  return false;
}




int main() {
  nodo_t* testa=NULL;
  int i;
  printf("main\n");
  for (int i=-400; i<=400; i+=3) {
    testa=nuovoNodoSpirale(testa,i);
  }
  visualizza(testa);
  testa=ordina(testa);
  visualizza(testa);
  if(trova(testa,-30)) printf("\nSi il valore esiste");
  else printf("\nIl valore non esiste");
  testa=freeSpirale(testa,&testa->next);
//  visualizza(testa);
  return 0;

}
