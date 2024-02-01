#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Data.h"
#include "Mutation.h"



int main(){
  int m, ind;
  printf("Type mutation value: ");
  if(!scanf("%d", &m)){
    printf("Invalid input. Input must be integer.\n");
    return 0;
  }

  printf("Type number of individuals: ");
  if(!scanf("%d", &ind)){
    printf("Invalid input. Input must be an integer.\n");
    return 0;
  }

  if(m < 1 || m > 100 || ind < 1){
    printf("invalid values, use values as:\n");
    printf("mutation: 1-100\n");
    printf("subjects: 1 or more\n\n");
    return 0;
  }

  printf("Mutation: %d%%\n", m);
  printf("Subjects: %d\n\n", ind);

  time_t t;
  srand((unsigned) time(&t));

  DATA D;
  CreateData(&D, m, ind);

  generatePeasants(&D);
  evolution(&D);


  printf("\nBest of all found on generation %d:\n", D.generation);
  printf("Individual #%d : [%d|%d|%d|%d]\n",
    D.Best,
    D.Peasants[D.Best].atk,
    D.Peasants[D.Best].def,
    D.Peasants[D.Best].dex,
    D.Peasants[D.Best].HP
  );

  DeleteData(&D);
  return 0;
}
