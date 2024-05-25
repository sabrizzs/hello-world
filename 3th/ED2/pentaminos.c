#include <stdio.h>
#include <stdlib.h>

#define TipoDaPilha pecaenc
#define TipoDaFila posicao

typedef struct {
  int rot,ref,lin,col;
  char letra,**mat;
} peca;

typedef struct{
  int peca,rot,ref;
} pecaenc;

typedef struct {
  TipoDaPilha *v;
  int topo;
  int max;
} pilha;

typedef struct {
  int lin,col;
} posicao;


char **tammatriz(int n,int p){ /*matrix allocation */
  char **A;
  int i;
  A = malloc( n * sizeof (char *));
  for (i = 0; i < n; ++i)
    A[i] = malloc( p* sizeof (char));
  return A;
}

void liberamatriz(char **mat,int n){ /*função para liberar uma matriz */
  int i;
  for (i=0;i<n;i++){
    free(mat[i]);
  }
  free(mat);
}
/******************************************************************* Stack******************************************/
void destroipilha(pilha *p){
  free(p->v);
}
void criapilha(pilha *p, int tam){
  p->v=malloc(tam*sizeof(TipoDaPilha));
  p->topo=0;
  p->max=tam;
}
int pilhaVazia(pilha *p){
  if(p->topo==0){
    return 1;
  }
  else return 0;
}
void empilha(pilha *p,TipoDaPilha i){
  p->v[p->topo]=i;
  (p->topo)++;
}
TipoDaPilha desempilha(pilha *p){
  TipoDaPilha i;
  i=p->v[p->topo-1];
  (p->topo)--;
  return(i);
}

/*********************************************************************Queue ******************************************/
typedef struct{
  TipoDaFila *v;
  int ini,fim;
  int max;
}fila;

void criaFila(fila *f,int tam){
  f->v=malloc(tam*sizeof(TipoDaFila));
  f->ini=0;
  f->fim=0;
  f->max=tam;
}
void destroiFila(fila *f){
  free(f->v);
}
void resizeFila(fila *f,int tam){
  f=realloc(f,tam);
}
void insereFila(fila *f,TipoDaFila x){
  if((f->fim+1)%f->max==f->ini){
    resizeFila(f,f->max*2);
  }
  f->v[f->fim]=x;
  f->fim=(f->fim+1)%f->max;
}
int filaVazia(fila f){
  return(f.fim==f.ini);
}
TipoDaFila removeFila(fila *f){
  TipoDaFila x;
  x=f->v[f->ini];
  f->ini=(f->ini+1)%f->max;
  return x;

}
/****************************************************************************************************************/

int bfs(char **tab,int m,int n,posicao pos){
  /*BFS for searching smallest hole. If smallest hole is smaller than 5 zeros, return 1. Else return 0. */


  int count,dl[]={1,-1,0,0},dc[]={0,0,1,-1},l,c,i;
  fila f;
  posicao p;
  criaFila(&f,m*n);


  tab[pos.lin][pos.col]='1';
  count=1;
  insereFila(&f,pos);

  while(!filaVazia(f)){
    pos=removeFila(&f);

    for(i=0;i<4;i++){
      l=pos.lin+dl[i]; 
      c=pos.col+dc[i];
      if(l>=0 && l<m && c>=0 && c<n && tab[l][c]=='0'){
	p.lin=l;
	p.col=c;
	insereFila(&f,p);
	count++;
	tab[l][c]='1';
      }
    }
  }

  destroiFila(&f);
  if(count>=5) return 0;
  return 1; 


}

int buracos(char **tab,int m, int n){
  //Check if smallest hole available has at least five free spaces
  int i,j,bpq=0;
  char **matzeros;
  posicao pos;


  matzeros=tammatriz(m,n);

  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      if(tab[i][j]=='0'){
	matzeros[i][j]='0';
      }
      else{
	matzeros[i][j]='1';
      }
    }
  }
  for(i=0;i<m && bpq==0;i++){
    for(j=0;j<n && bpq==0;j++){
      if(matzeros[i][j]=='0'){
	pos.lin=i;
	pos.col=j;
	bpq=bfs(matzeros,m,n,pos); /*bpq ==1 <-> there is a hole smaller than 5 pieces */
      }
    }
  }

  liberamatriz(matzeros,m);

  return (bpq);
}


void criaPecas(peca pecas[12]){

  pecas[0].letra='F';
  pecas[0].ref=1;
  pecas[0].rot=4;
  pecas[0].lin=pecas[0].col=3;
  pecas[0].mat=tammatriz(pecas[0].lin,pecas[0].col);
  pecas[0].mat[0][0]='0';pecas[0].mat[0][1]='F';pecas[0].mat[0][2]='F';
  pecas[0].mat[1][0]='F';pecas[0].mat[1][1]='F';pecas[0].mat[1][2]='0';
  pecas[0].mat[2][0]='0';pecas[0].mat[2][1]='F';pecas[0].mat[2][2]='0';

  pecas[1].letra='I';
  pecas[1].ref=0;
  pecas[1].rot=2;
  pecas[1].col=1; pecas[1].lin=5;
  pecas[1].mat=tammatriz(pecas[1].lin,pecas[1].col);
  pecas[1].mat[0][0]='I';pecas[1].mat[1][0]='I';pecas[1].mat[2][0]='I';pecas[1].mat[3][0]='I';pecas[1].mat[4][0]='I';

  pecas[2].letra='L';
  pecas[2].ref=1;
  pecas[2].rot=4;
  pecas[2].lin=4;pecas[2].col=2;
  pecas[2].mat=tammatriz(pecas[2].lin,pecas[2].col);
  pecas[2].mat[0][0]='L';pecas[2].mat[1][0]='L';pecas[2].mat[2][0]='L';pecas[2].mat[3][0]='L';pecas[2].mat[0][1]='0';
  pecas[2].mat[1][1]='0';pecas[2].mat[2][1]='0';pecas[2].mat[3][1]='L';

  pecas[3].letra='N';
  pecas[3].ref=1;
  pecas[3].rot=4;
  pecas[3].lin=2;pecas[3].col=4;
  pecas[3].mat=tammatriz(pecas[3].lin,pecas[3].col);
  pecas[3].mat[0][0]='N';pecas[3].mat[0][1]='N';pecas[3].mat[0][2]='0';pecas[3].mat[0][3]='0';
  pecas[3].mat[1][0]='0';pecas[3].mat[1][1]='N';pecas[3].mat[1][2]='N';pecas[3].mat[1][3]='N';


  pecas[4].letra='P';
  pecas[4].ref=1;
  pecas[4].rot=4;
  pecas[4].lin=3;pecas[4].col=2;
  pecas[4].mat=tammatriz(pecas[4].lin,pecas[4].col);
  pecas[4].mat[0][0]='P';pecas[4].mat[0][1]='P';pecas[4].mat[1][0]='P';pecas[4].mat[1][1]='P';
  pecas[4].mat[2][0]='P';pecas[4].mat[2][1]='0';

  pecas[5].letra='T';
  pecas[5].ref=0;
  pecas[5].rot=4;
  pecas[5].lin=3;pecas[5].col=3;
  pecas[5].mat=tammatriz(pecas[5].lin,pecas[5].col);
  pecas[5].mat[0][0]='T';	pecas[5].mat[0][1]='T';	pecas[5].mat[0][2]='T';	pecas[5].mat[1][0]='0';
  pecas[5].mat[1][1]='T';	pecas[5].mat[1][2]='0';	pecas[5].mat[2][0]='0';	pecas[5].mat[2][1]='T';
  pecas[5].mat[2][2]='0';

  pecas[6].letra='U';
  pecas[6].ref=0;
  pecas[6].rot=4;
  pecas[6].lin=2;pecas[6].col=3;
  pecas[6].mat=tammatriz(pecas[6].lin,pecas[6].col);
  pecas[6].mat[0][0]='U';pecas[6].mat[0][1]='0';pecas[6].mat[0][2]='U';pecas[6].mat[1][0]='U';
  pecas[6].mat[1][1]='U';pecas[6].mat[1][2]='U';

  pecas[7].letra='V';
  pecas[7].ref=0;
  pecas[7].rot=4;
  pecas[7].lin=pecas[7].col=3;
  pecas[7].mat=tammatriz(pecas[7].lin,pecas[7].col);
  pecas[7].mat[0][0]='V';	pecas[7].mat[0][1]='0';	pecas[7].mat[0][2]='0';	pecas[7].mat[1][0]='V';
  pecas[7].mat[1][1]='0';	pecas[7].mat[1][2]='0';	pecas[7].mat[2][0]='V';pecas[7].mat[2][1]='V';
  pecas[7].mat[2][2]='V';

  pecas[8].letra='W';
  pecas[8].ref=0;
  pecas[8].rot=4;
  pecas[8].lin=pecas[8].col=3;
  pecas[8].mat=tammatriz(pecas[8].lin,pecas[8].col);
  pecas[8].mat[0][0]='W';	pecas[8].mat[0][1]='0';	pecas[8].mat[0][2]='0';	pecas[8].mat[1][0]='W';
  pecas[8].mat[1][1]='W';	pecas[8].mat[1][2]='0';	pecas[8].mat[2][0]='0';pecas[8].mat[2][1]='W';
  pecas[8].mat[2][2]='W';

  pecas[9].letra='X';
  pecas[9].ref=0;
  pecas[9].rot=1;
  pecas[9].lin=pecas[9].col=3;
  pecas[9].mat=tammatriz(pecas[9].lin,pecas[9].col);
  pecas[9].mat[0][0]='0';	pecas[9].mat[0][1]='X';	pecas[9].mat[0][2]='0';	pecas[9].mat[1][0]='X';
  pecas[9].mat[1][1]='X';	pecas[9].mat[1][2]='X';	pecas[9].mat[2][0]='0';pecas[9].mat[2][1]='X';
  pecas[9].mat[2][2]='0';

  pecas[10].letra='Y';
  pecas[10].ref=1;
  pecas[10].rot=4;
  pecas[10].lin=2;pecas[10].col=4;
  pecas[10].mat=tammatriz(pecas[10].lin,pecas[10].col);
  pecas[10].mat[0][0]='0';pecas[10].mat[0][1]='0';pecas[10].mat[0][2]='Y';pecas[10].mat[0][3]='0';
  pecas[10].mat[1][0]='Y';pecas[10].mat[1][1]='Y';pecas[10].mat[1][2]='Y';pecas[10].mat[1][3]='Y';

  pecas[11].letra='Z';
  pecas[11].ref=1;
  pecas[11].rot=2;
  pecas[11].lin=pecas[11].col=3;
  pecas[11].mat=tammatriz(pecas[11].lin,pecas[11].col);
  pecas[11].mat[0][0]='Z';pecas[11].mat[0][1]='Z';pecas[11].mat[0][2]='0';pecas[11].mat[1][0]='0';
  pecas[11].mat[1][1]='Z';pecas[11].mat[1][2]='0';pecas[11].mat[2][0]='0';pecas[11].mat[2][1]='Z';
  pecas[11].mat[2][2]='Z';


}

char **Gira (char **mat,int lin,int col){
  char **nova;
  int i,j;

  nova=tammatriz(col,lin);
  for(i=0;i<col;i++){
    for(j=0;j<lin;j++){
      nova[i][j]=mat[lin-j-1][i];
    }
  }
  liberamatriz(mat,lin);
  return nova;
}

char **Reflete (char **mat,int lin,int col){
  char **nova;
  int i,j;


  nova=tammatriz(lin,col);
  for(i=0;i<lin;i++){
    for(j=0;j<col;j++){
      nova[i][j]=mat[i][col-j-1];
    }
  }

  liberamatriz(mat,lin);
  return nova;
}

int encaixa (char **tab,peca p,int indice,int rot,int ref,int m, int n,pecaenc *pos){ /*try to put p piece in the board */

  int i,j,encaixou,l,c,refl,rota,vazio=0,nlin=p.lin,ncol=p.col,aux,tl,tc,pl,pc;
  char **matpeca;

  matpeca=tammatriz(nlin,ncol);

  for(i=0;i<p.lin;i++){ /*auxiliary matrix */
    for(j=0;j<p.col;j++){
      matpeca[i][j]=p.mat[i][j];
    }
  }

  for(refl=0;refl<ref;refl++){ /*the piece should be reflected */
    matpeca=Reflete(matpeca,nlin,ncol);
  }

  for(rota=0;rota<rot;rota++){ /*the piece should be rotated*/
    matpeca=Gira(matpeca,nlin,ncol);
    aux=nlin;
    nlin=ncol;
    ncol=aux;

  }

  for(refl=ref;refl<=p.ref;refl++){
    for(rota=rot;rota<p.rot;rota++){

      encaixou=1;

      /*Try to put piece in first available space*/
      vazio=0;
      for(i=0;i<m;i++){ /*first available space */
	for(j=0;j<n;j++){
	  if(tab[i][j]=='0'){
	    vazio=1;
	    break;
	  }
	}
	if(vazio) break;
      }

      vazio=0;
      for(l=0;l<nlin;l++){ /*fist block of piece */
	for(c=0;c<ncol;c++){
	  if(matpeca[l][c]!='0'){
	    vazio=1;
	    break;
	  }
	}
	if(vazio) break;
      }
      /*saving free positions */
      tl=i;
      tc=j;
      pl=l;
      pc=c;

      for(i=i-l, l=0;l<nlin && encaixou==1; i++,l++ ){
	for(j=j-c, c=0; c<ncol; j++,c++){
	  if(i<0 || i>=m || j<0 || j>=n || ( tab[i][j]!='0' && matpeca[l][c]!='0')){
	    encaixou=0;
	    break;
	  }
	}
      }

      if(encaixou){ /*putting on the board */
	pos->peca=indice;
	pos->ref=refl;
	pos->rot=rota;

	for(tl=tl-pl, pl=0 ;pl<nlin; tl++, pl++){
	  for(tc=tc-pc, pc=0 ; pc<ncol; pc++,tc++){
	    if(matpeca[pl][pc]!='0')
	      tab[tl][tc]=matpeca[pl][pc];
	  }
	}
	liberamatriz(matpeca,nlin);
	return 1;
      }

      matpeca=Gira(matpeca,nlin,ncol);  /*didnt fit. Lets try to rotate*/
      aux=nlin;
      nlin=ncol;
      ncol=aux;
    }

    matpeca =Reflete(matpeca,nlin,ncol); /*Didnt fit. Lets try to reflect*/
  }
  liberamatriz(matpeca,nlin);
  return 0;
}

void desencaixa(char **tab,peca *pecas,pecaenc pos,int m, int n){
  /*take a piece out of the board */
  int i,j;
  char letra;
  letra = pecas[pos.peca].letra;
  for(i=0;i<m;i++){
    for (j=0;j<n;j++){
      if(tab[i][j]==letra) tab[i][j]='0';
    }
  }
}
void pentaminos(char **tab,int m,int n,int gira){
  int cont=0,colocadas[12],i,j,inicio=0,rot=0,ref=0;
  peca pecas[12];
  pilha p;
  pecaenc pos;

  criaPecas(pecas);
  criapilha(&p,12);
  for(i=0;i<12;i++)colocadas[i]=0; /*which pieces were used? */

  if(gira){ /*Primeiro Giro, caso m<n*/
    tab=Gira(tab,m,n);
    i=m;
    m=n;
    n=i;
  }


  while(cont<12){ /*while there is a available piece to fit*/
    for(i=inicio;i<12;i++){
      if(colocadas[i]==0 &&encaixa(tab,pecas[i],i,rot,ref,m,n,&pos)&& cont<12){
	cont++;
	empilha(&p,pos);
	colocadas[i]=1;

	if(inicio!=0){
	  inicio=0;
	  i=-1; 
	}

	if(buracos(tab,m,n)) break;
	/*there is hole with less than five spaces. Take last piece out immediately*/
      }

      rot=0;
      ref=0;
    }

    if(cont<12){                                   /********Backtracking*********/
      if(!pilhaVazia(&p)){
	pos=desempilha(&p);
	desencaixa(tab,pecas,pos,m,n);
			
	colocadas[pos.peca]=0;
	inicio=pos.peca; /*lets try to start from this piece*/
	if(pos.rot<pecas[pos.peca].rot-1){/*if possible to rotate, rotate*/
	  rot=pos.rot+1;
	  ref=pos.ref;
	}
	else{ /*Reflect otherwise*/
	  rot=0;
	  ref=pos.ref+1;
	}
	cont--;
      }
      else{
	printf("Impossible \n");
	destroipilha(&p);

	for(i=0;i<12;i++){
	  liberamatriz(pecas[i].mat,pecas[i].lin); 
	}
	return;
      }
    }
  }
	
  if(gira){
    for(i=0;i<3;i++) { /*Rotate back if m<n*/
      tab=Gira(tab,m,n);
      j=m;
      m=n;
      n=j;
    }
  }

	
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      if(tab[i][j]=='1') printf("* ");
      else
	printf("%c ",tab[i][j]);
    }
    printf("\n");
  }

  destroipilha(&p);

  for(i=0;i<12;i++){
    liberamatriz(pecas[i].mat,pecas[i].lin); 
  }


}


int main(){
  int m,n,i,j;
  char **tab;


  scanf("%d %d",&m,&n);

	
  tab=tammatriz(m,n);

  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      scanf(" %c",&tab[i][j]);
    }
  }	

  pentaminos(tab,m,n,m<n);
  /*Algorith is faster when line n > m. If otherwise, rotate, execute, then rotate back*/


  return 0;
}
