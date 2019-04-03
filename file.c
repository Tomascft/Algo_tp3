#include <stdlib.h>
#include <stdio.h>


#include "file.h"
//#include "graphe.h"

pfile_t creer_file()
{
  pfile_t result = (pfile_t)malloc(sizeof(file_t));
  result->tete = 0;
  result->queue = 0;
  return result;
}

int file_vide(pfile_t f)
{
  return (f->tete >= f->queue);
}

int file_pleine(pfile_t f)
{
  return (f->tete == 0) && (f->queue == MAX_FILE_SIZE);
}

pnoeud_t retirer_file(pfile_t f)
{
  if(f->tete == f->queue)
  {
    return NULL;
  }
  pnoeud_t result = f->Tab[f->tete];
  f->tete++;
  return result;
}

int deposer_file(pfile_t f, pnoeud_t p)
{
  if(f->queue >= MAX_FILE_SIZE && f->queue >= 0)
  {
    return 1;
  }
  f->Tab[f->queue] = p;
  f->queue++;
  return 0 ;
}

void afficher_file(pfile_t f){
printf("file: ");
for(int i=f->tete;i<f->queue;i++){
	printf(" %d ",f->Tab[i]->label);
}
printf("\n");
}

/*int min_file_index(pfile_t f){
	int ind=f->tete;
  int tmp=f->Tab[f->tete]->label;
  for(int i=f->tete+1; i < f->queue; i++){
    if(f->Tab[i]->label < tmp){
      tmp=f->Tab[i]->label;
	ind=i;
	}
  }
  return ind;
}*/



























