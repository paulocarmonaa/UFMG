#include"AlgoritmosOrdenacao.hpp"
#include<stdlib.h>

typedef struct estatisticas{
  int cmp;
  int move;
  int calls;
}estatisticas_t;


void resetcounter(estatisticas_t *s){
// Descricao: inicializa estrutura
// Entrada: 
// Saida: s
  s->cmp = 0;
  s->move = 0;
  s->calls = 0;
}

void inccmp(estatisticas_t * s, int num){
// Descricao: incrementa o numero de comparacoes em num 
// Entrada: s, num
// Saida: s
  s->cmp += num;
}

void incmove(estatisticas_t * s, int num){
// Descricao: incrementa o numero de movimentacoes de dados em num 
// Entrada: s, num
// Saida: s
  s->move += num;
}

void inccalls(estatisticas_t * s, int num){
// Descricao: incrementa o numero de chamadas de função em num 
// Entrada: s, num
// Saida: s
  s->calls += num;
}

void swap(int *xp, int *yp, estatisticas_t *s){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    incmove(s,3);
}

//insertion sort
void insertionSort(int v[], int l, int r, estatisticas_t * s) {

  inccalls(s,1);
  int temp,j;

  for(int i = l + 1; i <= r; i++)
  {
    inccmp(s,1);

    int temp = v[i];
    incmove(s,1);
    
    j = i - 1;

    while((temp < v[j]) && (0 <= j))
    {
      inccmp(s,1);
      v[j+1] = v[j];
      j--;
      incmove(s,1);
    }

    v[j+1] = temp;
    incmove(s,1);
  }

  return;
}

// median of 3 integers
int median (int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}


// quicksort partition using median of 3
void partition(int * A, int l, int r, int *i, int *j, estatisticas_t *s) {
    
  int m = l + (r - l) / 2;
  int pivo = median(A[l],A[r],A[m]);

  *i = l;
  *j = r;

  while(*i <= *j){
      
    while(A[*i]< pivo){
      (*i)++;
      inccmp(s,1);
    }
    
    inccmp(s,1);

    while(pivo < A[*j]){
      (*j)--;
      inccmp(s,1);
    }
    
    inccmp(s,1);
    
    if(*i <= *j){
      swap(&A[*i],&A[*j],s);
      (*i)++;
      (*j)--;
    }
  } 
}


// quicksort with insertion for small partitions and median of 3
void quickSort(int * A, int l, int r, estatisticas_t *s) { 
     inccalls(s, 2);

    int i, j;
    partition(A, l, r, &i, &j, s);

    if (l < j){
        if(j-l <= 50)
            insertionSort(A, l, j, s);
        else
            quickSort(A, l, j, s);
    }
    if (i < r){
        if((r-i) <= 50)
            insertionSort(A, i, r, s);
        else
            quickSort(A, i, r, s);
    }
}

 int shuffleVector(int *vet, int size, int numShuffle){
 int p1 = 0, p2 = 0, temp;
 for (int t = 0; t < numShuffle; t++) {
 /* Gera dois índices distintos no intervalo [0..size-1] */
 while (p1 == p2) {
 p1 = (int)(drand48() * size);
 p2 = (int)(drand48() * size);
 }
 /* Realiza a troca para introduzir uma quebra */
 temp
 = vet[p1];
 vet[p1] = vet[p2];
 vet[p2] = temp;
 p1 = p2 = 0;
 }
 return 0;
 }