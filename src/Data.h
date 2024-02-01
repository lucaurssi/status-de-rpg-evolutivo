typedef struct pleb{
  int atk; // valor de ataque
  int def; // valor de defesa
  int dex; // valor de destreza
  int HP; // valor de HP
}PLEB;

typedef struct data{
  PLEB *Peasants; // vetor dos indivíduos
  int mod_table[31]; // tabela de modificadores
  int Best; // o melhor indivíduo
  int mutation; // valor de mutação
  int numPeasants; // número total de indivíduos
  int wins; // número de vitórias do melhor
  int generation; // número da geração
}DATA;

void CreateData(DATA *, int, int);
void DeleteData(DATA *);
