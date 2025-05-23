#ifndef ALGORITMOS_H
#define ALGORITMOS_H

typedef struct estatisticas{
  int cmp;
  int move;
  int calls;
}estatisticas_t;

void inccmp(estatisticas_t * s, int num);
void incmove(estatisticas_t * s, int num);
void inccalls(estatisticas_t * s, int num);

void resetcounter(estatisticas_t * s);
void swap(int *xp, int *yp, estatisticas_t *s);

void insertionSort(int v[], int l, int r, estatisticas_t * s);

int median (int a, int b, int c);
void partition(int * A, int l, int r, int *i, int *j, estatisticas_t *s);
void quickSort(int * A, int l, int r, estatisticas_t *s);

int shuffleVector(int *vet, int size, int numShuffle);

#endif