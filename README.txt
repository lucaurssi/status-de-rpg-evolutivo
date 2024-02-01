Status de RPG Evolutivo

Descrição: trabalho da disciplina Algoritmos Evolutivos do curso de Bacharelado em Ciências da Computação (ICMC-USP).

Link para explicação do trabalho:
  https://www.youtube.com/watch?v=3zQd_qqZrdI&ab_channel=Luca
Link para a disciplina:
  https://gitlab.com/simoesusp/disciplinas/-/tree/master/SSC0713-Sistemas-Evolutivos-Aplicados-a-Robotica

Alunos:
  - Luca Gomes Urssi - 10425396
  - Igor Lovatto Resende - 10439099
  - Vinicius Finke Raiter José - 9791052
  - Rafael Meliani Velloso - 4165457

Professor: Eduardo Simões

Para rodar o programa:
  - Abra o terminal e navegue até a pasta "src".
  - Digite o comando "make" para compilar.
  - Digite o comando "make run" para rodar.

Resumo:
  - O algoritmo recebe de entrada como argumento o valor de mutação que pode ser
  entre 1-100 e o numero de indivíduos por geração com um mínimo de 1.
  - Na saída o algoritmo devolve o melhor individuo encontrado e a geração
  na qual ele foi encontrado.

  - O algoritmo avalia 4 valores pra achar o melhor, sendo eles ataque, defesa,
  destreza e vida.
  - É gerado n indivíduos com pontos distribuídos aleatoriamente nas 4
categorias.

  - O método de seleção para achar o melhor é composto de um torneio, onde os
indivíduos formam pares, lutam e o vencedor segue para a próxima "fase" do
torneio.
  - o campeão do torneio é o considerado o melhor e aplicamos o crossover nele,
cruzando ele com os outros competidores.

  - nosso crossover trata cada atributo (ataque, defesa, ...) como um gene. O
"filho" do melhor com outro individuo tem a media dos genes de cada parente, com
uma porcentagem dada na entrada de receber +1 ou -1 em cada atributo 
individualmente.
  - O melhor é mantido sem alterações.

  - O indivíduo com a maior destreza tem a vantagem em rolar melhor sua
iniciativa e portanto atacar primeiro.
  - O atacante rola um d20 + um modificador baseado no ataque. caso seja maior
ou igual a defesa ele da um dano de 1d4 + o modificador de ataque. Caso o valor
seja menor que a defesa, o ataque não acerta e da 0 de dano.

  - Caso o melhor perca, o indivíduo que o venceu toma o seu lugar.
  - É encontrado o melhor dos melhores quando algum melhor conseguir vencer 5
torneios seguidos.
  - O codigo mostra o melhor de cada geração e pede para apertar 'enter'.

Métodos:
  - CreateData: inicializa a struct DATA com os valores de mutação, numero de
  indivíduos e outras variáveis interessantes.
  - DeleteData: libera a memoria alocada para numero de indivíduos.

  - generatePeasants: gera n indivíduos com valores aleatórios em seus atributos.
  - evolution: faz um torneio entre um número aleatório de competidores (no máximo metade dos indivíduos),
o indivíduo que venceu vira o novo melhor. O melhor reproduz com todos os outros indivíduos e
cria uma nova geração. A função roda até achar um indivíduo que vença 5 torneios seguidos.


