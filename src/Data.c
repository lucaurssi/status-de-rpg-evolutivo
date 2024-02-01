#include "Data.h"
#include <stdlib.h>

void CreateData(DATA *D, int m, int ind){
  D->mutation = m; // valor de mutação
  D->numPeasants = ind; // número de indivíduos

  D->Peasants = malloc(D->numPeasants * sizeof (PLEB)); // cria vetor de indivíduos

  D->wins = 0; // número de vitórias do melhor indivíduo
  D->generation = 1; // número da geração atual
  D->Best = rand()%D->numPeasants; // o melhor indivíduo inicial é aleatório

  // criando tabela de modificadores
  int i;
  for(i = 1; i <= 2; i++) D->mod_table[i] = 0;
  for(i = 3; i <= 4; i++) D->mod_table[i] = 1;
  for(i = 5; i <= 6; i++) D->mod_table[i] = 2;
  for(i = 7; i <= 8; i++) D->mod_table[i] = 3;
  for(i = 9; i <= 12; i++) D->mod_table[i] = 4;
  for(i = 13; i <= 18; i++) D->mod_table[i] = 5;
  for(i = 18; i <= 25; i++) D->mod_table[i] = 6;
  for(i = 26; i <= 30; i++) D->mod_table[i] = 7;
}

void DeleteData(DATA *D){
  free(D->Peasants);
}
