#include "Data.h"
#include "Mutation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

// cria os indivíduos com atributos aleatórios (entre 1 e 11)
void generatePeasants(DATA *D){
  for(int i = 0; i < D->numPeasants; i++){
    D->Peasants[i].atk = 1 + rand()%11;
    D->Peasants[i].def = 1 + rand()%11;
    D->Peasants[i].dex = 1 + rand()%11;
    D->Peasants[i].HP = 1 + rand()%11;
  }
}

// retorna um valor de modificador de acordo com a tabela de modificadores
int modifier(DATA* D, int val){
  return D->mod_table[val%31] + (val/31)*7;
}

// rola iniciativa: o vencedor é o primeiro a atacar
short int roll_initiative(DATA* D, PLEB A, PLEB B){
  srand(time(NULL));

  // A venceu a iniciativa
  if(rand()%20 + 1 + modifier(D, A.dex) > rand()%20 + 1 + modifier(D, B.dex))
    return 0;

  return 1; // B venceu a iniciativa
}

// função que retorna dano que 'attacker' causará em 'victim'
int dammage(DATA* D, PLEB attacker, PLEB victim){
  srand(time(NULL));

  if(rand()%20 + 1 + modifier(D, attacker.atk) < victim.def) // nao acertou
    return 0;

  // retorna dano que a vitima vai tomar (1d4 + modificador de ataque)
  return rand()%4 + 1 + modifier(D, attacker.atk);
}

// indivíduos A e B lutam até que um deles morra
short int combat(DATA* D, PLEB A, PLEB B){
  short int turn = roll_initiative(D, A, B);

  while(A.HP > 0 && B.HP > 0){
    switch(turn){
      case 0: B.HP -= dammage(D, A, B); break;
      case 1: A.HP -= dammage(D, B, A); break;
      default: break;
    }
    turn = !turn;
  }

  return !turn;
}

// função de mutação (a mutação tem uma chance de 'D->mutation'% de acontecer)
int mutation(DATA* D){
  srand(time(NULL));

  int r = rand()%101;

  // mutação ocorreu (pode aumentar ou diminuir em 1)
  if(r <= D->mutation){
      if(rand()%2)
        return 1;
      return -1;
  }

  return 0; // mutação não ocorreu
}

// reprodução entre indivíduos A e B
PLEB reproduction(DATA *D, PLEB A, PLEB B){
  PLEB child;

  // cada um fornece metade de seu "DNA"
  child.atk = (A.atk + B.atk)/2 + mutation(D);
  child.def = (A.def + B.def)/2 + mutation(D);
  child.dex = (A.dex + B.dex)/2 + mutation(D);
  child.HP = (A.HP + B.HP)/2 + mutation(D);

  // caso tenha atingido zero, volta para 1
  child.atk = child.atk <= 0 ? 1 : child.atk;
  child.def = child.def <= 0 ? 1 : child.def;
  child.dex = child.dex <= 0 ? 1 : child.dex;
  child.HP = child.HP <= 0 ? 1 : child.HP;

  return child;
}

/*
  - torneio entre no máximo metade dos indivíduos (são escolhidos aleatoriamente)
  - o vencedor reproduz com todos os outros e cria uma nova geração
*/
void tournament(DATA *D){
  int np = D->numPeasants, enemy;
  int champion = D->Best;
  int num_competitors = rand()%(np/2 + 1);
  char dead[np]; // vetor que indica quem morreu

  memset(dead, 0, np*sizeof(char));

  PLEB winner, parent;

  printf("Number of competitors = %d\n", num_competitors);
  printf("Champion: Individual #%d\n\n", D->Best);

  while(num_competitors--){
    enemy = rand()%np;
    if(!dead[enemy] && enemy != champion && combat(D, D->Peasants[champion], D->Peasants[enemy])){
      dead[champion] = 1;
      champion = enemy;
    }
    else
      dead[enemy] = 1;
  }

  winner = D->Peasants[champion]; // vencedor da geração
  np = D->numPeasants;

  if(D->Best == champion){
    D->wins++;
  }
  else{
    D->wins = 1;
    D->Best = champion;
  }

  // faz reprodução entre o vencedor e todos os outros e cria uma nova geração
  for(int i = 0; i < np; i++){
    if(i != champion){
      parent = D->Peasants[i];
      D->Peasants[i] = reproduction(D, winner, parent);
    }
  }
}

void printGeneration(DATA* D){
  for(int i = 0; i < D->numPeasants; i++)
    printf("[%d|%d|%d|%d]\n", D->Peasants[i].atk, D->Peasants[i].def, D->Peasants[i].dex, D->Peasants[i].HP);
}

// função que faz a evolução da população
void evolution(DATA *D){

  printf("[Generation x] - Best => [attack|defence|dexterity|life]\n\n");
  printf("Press enter to start next tournament: \n");

  while(D->wins < 5){ // para terminar a evolução, um indivíduo precisa vencer 5 vezes seguidas
    getchar();
    tournament(D);
    printf("[Generation %d] - New Champion => Individual #%d : [%2d|%2d|%2d|%2d]\n",
      D->generation++,
      D->Best,
      D->Peasants[D->Best].atk,
      D->Peasants[D->Best].def,
      D->Peasants[D->Best].dex,
      D->Peasants[D->Best].HP
    );
  }

  D->generation--;
}
