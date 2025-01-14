/******************************************************************************************************************
 * Jogo da Velha
 * Autor: Robert Emanuel
 * Data de Criação: 03-12-2022
 * Versão: 4.0
 * Descrição:
Jogo da velha (3X3 OU 4X4);
a) Apenas um tabuleiro 3x3 (ou 5x5)
b) Caso não exista o segundo jogador, o computador deve assumir a posição do
oponente;
c) Ranking em arquivo;
d) Deve haver menu com opções de Jogar, Ver Ranking, Créditos e Sair;
e) Utilize matriz com alocação dinâmica;
f) Utilize struct para armazenar dados em memória e depois transferir para arquivo;
g) Controle de jogada deve ser feito utilizando entrada de dados pelo teclado
contendo informação da posição e usuário;

******************************************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define POSICOES_PLACAR 10

//inicio
//struct para os movimentos do pc.
struct Move{
  int linha, coluna;
};
//struct para os dados do placar.
struct Placar{
  int vitorias, derrotas, velhas;
};
//struct para os dados do usuario.
struct Jogador {
  char nome[20];
  int pontuacao;
  int peca;
};

// Protótipos das funções (Mova TODAS as suas funções para cá)
int single();
int multi();
int Ranking();
int creditos();
int submenu1();
void dadosUsuario(struct Jogador *, struct Placar *);
void mostrarUsuario(struct Jogador *);
void redefinirTabuleiro(int a[3][3]);
void rodadaInit(int (*tabuleiro)[3], int, struct Placar *);
void inserirRanking(struct Jogador);
int calculaPontuacao(struct Placar);
void desenharTabuleiro(int (*tabuleiro)[3]);
void rodadaJogador(int (*tabuleiro)[3], int);
char converteNumero(int);
void efetuarJogada(int tabuleiro[3][3], int linha, int coluna, int jogador);
int verificaJogada(int tab[3][3], int x, int y);
int verificaVencedor(int tabuleiro[3][3], int jogador);
int existemPossibilidades(int tabuleiro[3][3]);
void jogadaBot(int tabuleiro[3][3], int bot);
int minimax(int tabuleiro[3][3], int profundidade, int isMax, int jogador); 
int avaliaJogada(int tabuleiro[3][3], int jogador);
struct Move movimentoBot(int tabuleiro[3][3], int jogador);
void mostrarPlacar(struct Placar placar);
int mostrarUsuarioRanking(struct Jogador jogador);
void ordenarVetor(struct Jogador jogadores[POSICOES_PLACAR], int ranking_total);

//inicio do MENU do jogo
int main(void) {

  int single();
  int multi();
  int Ranking();
  int creditos();

  int valor;

  do{ 
    system("clear"); 

    printf("\n.......... Jogo da Velha ..........\n\n");
    printf("1. Jogar \n");
    printf("2. Ver Ranking \n");
    printf("3. Créditos\n");
    printf("4. Sair\n");

    printf("\nEscolha uma opção: ");
    scanf("%d", &valor);

    //abrir uma das opções do usuário
    switch(valor){
        case 1: printf("\n.......... Escolha o modo de jogo ..........\n"); submenu1(); break;
        case 2: printf("ranking"); Ranking(); break;
        case 3: printf("creditos"); creditos(); break;
    }

  }while(valor != 4);

  system("clear"); 

  return 0;
}
//abrir o submenu pra escolher o modo de jogo
int submenu1(){
 int tipo2;
 printf("\n1- Singleplayer\n2- Multiplayer\n\n");

 printf("\nEscolha uma opção: ");
 scanf("%d", &tipo2);
 switch(tipo2){
     case 1: printf("\n\n.......... Você escolheu o modo Singleplayer ..........\n"); single(); break;
     case 2: printf("\n\n.......... Você escolheu o modo Multiplayer ..........\n"); multi(); break;

     default: printf("coloque o valor correto respectivo ao menu que quer selecionar!\n"); submenu1();
 }
}
//modo singleplayer x bot pc
int single(){

  void dadosUsuario(struct Jogador *, struct Placar *);
  void mostrarUsuario(struct Jogador *);
  void redefinirTabuleiro(int a[3][3]);
  void rodadaInit(int (*tabuleiro)[3], int, struct Placar *);
  void inserirRanking(struct Jogador);

  int calculaPontuacao(struct Placar);

  int tabuleiro[3][3];  //variavel que cria o tabuleiro
  int valor;        //variavel dados do usuário
  struct Jogador jogador;
  struct Placar placar;

  //preencher dados do usuario
  dadosUsuario(&jogador, &placar);

  //loop das rodadas até jogador desejar sair
  do{ 
    system("clear");

    redefinirTabuleiro(tabuleiro);

    //inicio o loop das rodadas 
    rodadaInit(tabuleiro, jogador.peca, &placar);

    jogador.pontuacao = calculaPontuacao(placar);
    mostrarUsuario(&jogador);

    printf("\n\n1. Continuar \n\n");
    printf("2. Sair\n");

    printf("\nEscolha uma opção: ");
    scanf("%d", & valor);

  }while(valor != 2); 

  inserirRanking(jogador);

  return 0;
}

//pegar os dados do usuario
void dadosUsuario(struct Jogador *jogador, struct Placar *placar){
  int valor;
  system("clear"); 

  printf("\n.......... Bem vindo ao jogo da velha em C ..........\n");

  printf("\nQual seu nome: ");
  scanf("%s", (*jogador).nome);

  do{ 
    printf("\nEscolha entre: ");
    printf("\n1. X \n");
    printf("2. O\n");

    printf("\nEscolha uma opção:");
    scanf("%d", & valor);

     //Analisar a opção do usuario
    switch(valor){
      case 1:
        (*jogador).peca = 1;
        break;
      case 2:
         (*jogador).peca = -1;
        break;
    }
  }while(valor > 2 || valor <=0); 

  //inicializar os placares em 0
  (*placar).velhas = 0;
  (*placar).derrotas = 0;
  (*placar).vitorias = 0;

}

//executar o loop das jogadas no tabuleiro
void rodadaInit(int tabuleiro[3][3], int jogador, struct Placar *placar){

  void desenharTabuleiro(int (*tabuleiro)[3]);
  void rodadaJogador(int (*tabuleiro)[3], int);
  void mostrarPlacar(struct Placar placar);

  int existemPossibilidades(int (*tabuleiro)[3]);
  int verificaVencedor(int (*tabuleiro)[3], int);

  void jogadaBot(int (*tabuleiro)[3], int);

  int bot = jogador == 1?-1:1; 
  int vez = rand()%3 + jogador; 

  int vencedor = 0;

  //loop para as jogadas
  while(existemPossibilidades(tabuleiro)){
    system("clear"); 
    mostrarPlacar(*placar);
    desenharTabuleiro(tabuleiro);
    int rodada = 0;

    if(vez % 2 == 0){
      //jogada do usuario
      printf("\n\nSua Vez!");
      rodadaJogador(tabuleiro, jogador);
      rodada = jogador;
    }else{
      // jogada do bot
      printf("\n");
      jogadaBot(tabuleiro, bot);
      rodada = bot;
    }

    vez++;

    //se alguém vencer
    if(verificaVencedor(tabuleiro, rodada)){
      system("clear");

      if(rodada == jogador){
        printf("\nParabéns!!! a vitória é sua \n\n");
        vencedor = 1;
        (*placar).vitorias++;
      }else{
         printf("Você perdeu!!! mais sorte na próxima vez\n");
         vencedor = 1;
         (*placar).derrotas++;
      }
      break;
    }
  }
//caso dê empate = velha
  if(!vencedor){
    system("clear");
    printf("\n Deu Velha \n\n");
    (*placar).velhas++;
  } 

  desenharTabuleiro(tabuleiro);
  mostrarPlacar(*placar);
}
void rodadaJogador(int tabuleiro[3][3], int jogador){
  int verificaJogada(int (*tab)[3], int, int);
  void efetuarJogada(int (*tab)[3],int, int, int);

  int linha, coluna;

  //loop para o usuario definir uma jogada correta
  do{

    printf("\nInsira a Linha que deseja jogar:");
    scanf("%d", &linha); 

    printf("\nInsira a Coluna que deseja jogar:");
    scanf("%d", &coluna);

  }while(!verificaJogada(tabuleiro, linha-1, coluna-1));
  efetuarJogada(tabuleiro, linha-1, coluna-1, jogador);
}

//desenhar o tabuleiro 
void desenharTabuleiro(int tabuleiro[3][3]){
  char converteNumero(int);
  int tabuleiroChar[3][3];

  for(int i = 0; i <3; i++){
    printf("\n  %d", i+1);
     printf("\t ");
    for(int j = 0; j<3; j++){
      tabuleiroChar[i][j] = converteNumero(tabuleiro[i][j]);
      if(j < 2){
        printf("  %c |", tabuleiroChar[i][j]);
      }else{
        printf(" %c  ", tabuleiroChar[i][j]);
      }
    }
    if(i<2){
      printf("\n\t  ------------");
    }
  } 
  printf("\n\n\t   1    2   3 \n");
}

//recebe tabuleiro, e altera seus valores em nulo
void redefinirTabuleiro(int tab[3][3]){
  for(int i = 0; i <3; i++){
    for(int j = 0; j<3; j++){
      tab[i][j] = 0;
    }
  }
}

//recebe um numero e converte
char converteNumero(int valor){
  if(valor == 0){
    return ' ';
  }else{
    if(valor == 1){
      return 'X';
    }else{
      if(valor == -1){
        return 'O';
      }
    }
  }
  return ' ';
} 

//efetuar jogada no tabuleiro
void efetuarJogada(int tabuleiro[3][3], int linha, int coluna, int jogador){
  tabuleiro[linha][coluna] = jogador;
}

//verificar se esta disponivel, sendo 1 ou 0
int verificaJogada(int tab[3][3], int x, int y) {
    if (x >= 0 && y >= 0 && x < 3 && y < 3) { 
        if (tab[x][y] == 0) {
            return 1;
        }
    }
    return 0;
}

//verifica se existe um vencedor
int verificaVencedor(int tabuleiro[3][3], int jogador){

   //verificando as linhas para decidir se há um vencedor.
   if (tabuleiro[0][0]==jogador 
      && tabuleiro[0][1]==jogador 
      && tabuleiro[0][2]==jogador) {
      printf("\nLinha 1\n");
    return 1 ;
  }
  if (tabuleiro[1][0]==jogador 
      && tabuleiro[1][1]==jogador 
      && tabuleiro[1][2]==jogador) {
        printf("\nLinha 2\n");
    return 1 ;
  }
  if (tabuleiro[2][0]==jogador 
      && tabuleiro[2][1]==jogador 
      && tabuleiro[2][2]==jogador) {
        printf("\nLinha 3\n");
    return 1 ;
  }
  if (tabuleiro[0][0]==jogador 
      && tabuleiro[1][0]==jogador 
      && tabuleiro[2][0]==jogador) {
        printf("\nColuna 1\n");
    return 1 ;
  } 
   //verificando as colunas para decidir se há um vencedor.
  if (tabuleiro[0][1]==jogador 
      && tabuleiro[1][1]==jogador 
      && tabuleiro[2][1]==jogador) {
        printf("\nColuna 2\n");
    return 1 ;
  } 
  if (tabuleiro[0][2]==jogador 
      && tabuleiro[1][2]==jogador 
      && tabuleiro[2][2]==jogador) {
        printf("\nColuna 3\n");
    return 1 ;
  }
   //verificando as diagonais decidir se há um vencedor.
  if (tabuleiro[0][0]==jogador 
      && tabuleiro[1][1]==jogador 
      && tabuleiro[2][2]==jogador) {
        printf("\nDiagonal principal\n");
    return 1 ;
  }
  if (tabuleiro[0][2]==jogador 
      && tabuleiro[1][1]==jogador 
      && tabuleiro[2][0]==jogador) { 
        printf("\nDiagonal secundaria\n");
    return 1 ;
  }   

  return 0; //caso não tenha vencedor, retorna 0
}

//esta função retorna verdadeiro se houver movimentos no tabuleiro. 
//retorna 0 se não há mais movimentos para jogar.
int existemPossibilidades(int tabuleiro[3][3]){
  for (int i = 0; i<3; i++)
      for (int j = 0; j<3; j++)
          if (tabuleiro[i][j]== 0)
              return 1;
  return 0;
}

//codigo referente a analise do Bot
//analisar e efetuar a jogada do bot
void jogadaBot(int tabuleiro[3][3], int bot){
  struct Move movimentoBot(int a[3][3], int);
  void efetuarJogada(int (*tabuleiro)[3], int linha, int coluna, int jogador);

  struct Move jogadaBot = movimentoBot(tabuleiro, bot);

  efetuarJogada(tabuleiro, jogadaBot.linha, jogadaBot.coluna, bot);
} 

//escolhe um caminho possivel para seguir
int minimax(int tabuleiro[3][3], int profundidade, int isMax, int jogador) {
    int avaliaJogada(int (*tabuleiro)[3], int);
    int existemPossibilidades(int tabuleiro[3][3]);

    int pontuacao = avaliaJogada(tabuleiro, jogador);

    //casos base da recursão
    if (pontuacao == 10) {
        return pontuacao - profundidade; 
    }
    if (pontuacao == -10) {
        return pontuacao + profundidade; 
    }
    if (!existemPossibilidades(tabuleiro)) {
        return 0;
    }

    if (isMax) {
        int melhor = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tabuleiro[i][j] == 0) {
                    tabuleiro[i][j] = jogador;
                    int valor = minimax(tabuleiro, profundidade + 1, !isMax, jogador);
                    tabuleiro[i][j] = 0;
                    if (valor > melhor) {
                        melhor = valor;
                    }
                }
            }
        }
        return melhor;
    } else { 
        int melhor = 1000;
        int outroJogador = (jogador == 1) ? -1 : 1; 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tabuleiro[i][j] == 0) {
                    tabuleiro[i][j] = outroJogador;
                    int valor = minimax(tabuleiro, profundidade + 1, !isMax, jogador);
                    tabuleiro[i][j] = 0; 
                    if (valor < melhor) {
                        melhor = valor;
                    }
                }
            }
        }
        return melhor;
    }
}

//struct para escolher o melhor movimento para o bot
struct Move movimentoBot(int tabuleiro[3][3], int jogador) {
    int minimax(int tabuleiro[3][3], int profundidade, int isMax, int jogador);
    int verificaJogada(int (*tab)[3], int, int);

    int melhorValor = -1000;
    struct Move melhorMovimento;
    melhorMovimento.linha = -1;
    melhorMovimento.coluna = -1;
    int outroJogador = (jogador == 1) ? -1 : 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == 0) {
                tabuleiro[i][j] = jogador;
                int valorMovimento = minimax(tabuleiro, 0, 0, jogador); 
                tabuleiro[i][j] = 0;

                if (valorMovimento > melhorValor) {
                    melhorMovimento.linha = i;
                    melhorMovimento.coluna = j;
                    melhorValor = valorMovimento;
                }
            }
        }
    }

    return melhorMovimento;
}

//esse função avalia se a jogada irá resultar chances de vitoria ou derrota 
int avaliaJogada(int tabuleiro[3][3], int jogador){
  //verificando as linhas para vitória 
  for (int linha = 0; linha<3; linha++)
  {
      if (tabuleiro[linha][0]==tabuleiro[linha][1] &&
          tabuleiro[linha][1]==tabuleiro[linha][2] && tabuleiro[linha][2]!=0)
      {
          if (tabuleiro[linha][0]==jogador)
              return +10;
          else 
              return -10;
      }
  }

  //verificando colunas para vitória 
  for (int coluna = 0; coluna<3; coluna++)
  {
      if (tabuleiro[0][coluna]==tabuleiro[1][coluna] &&
          tabuleiro[1][coluna]==tabuleiro[2][coluna] && tabuleiro[2][coluna]!=0)
      {
          if (tabuleiro[0][coluna]==jogador)
              return +10;
          else
              return -10;
      }
  }

  //verificando as diagonais para vitória
  if (tabuleiro[0][0]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][2] && tabuleiro[2][2]!=0)
  {
      if (tabuleiro[0][0]==jogador)
          return +10;
      else 
          return -10;
  }

  if (tabuleiro[0][2]==tabuleiro[1][1] && tabuleiro[1][1]==tabuleiro[2][0] !=0)
  {
      if (tabuleiro[0][2]==jogador)
          return +10;
      else 
          return -10;
  }

  //se nenhum ganhou, retorna 0
  return 0;
}

int multi() {
    void dadosUsuario(struct Jogador *, struct Placar *);
    void mostrarUsuario(struct Jogador *);
    void redefinirTabuleiro(int a[3][3]);
    void rodadaInit(int (*tabuleiro)[3], int, struct Placar *);
    void inserirRanking(struct Jogador);
    int calculaPontuacao(struct Placar);

    int tabuleiro[3][3];
    int valor;
    struct Jogador jogador1, jogador2; 
    struct Placar placar1, placar2;

    system("clear");
    printf("\n.......... Modo Multiplayer ..........\n");

    printf("\nDados do Jogador 1:\n");
    dadosUsuario(&jogador1, &placar1);

    system("clear");
    printf("\n.......... Modo Multiplayer ..........\n");
    printf("\nDados do Jogador 2:\n");
    dadosUsuario(&jogador2, &placar2);

    //ajuste para garantir que as peças sejam diferentes
    while (jogador1.peca == jogador2.peca) {
        printf("\nJogador 2, sua peça deve ser diferente da do Jogador 1.\n");
        dadosUsuario(&jogador2, &placar2);
    }


    do {
        system("clear");
        redefinirTabuleiro(tabuleiro);

        //define quem começa aleatoriamente
        int jogadorAtual = (rand() % 2 == 0) ? 1 : 2;

        while (existemPossibilidades(tabuleiro)) {
            system("clear");
            desenharTabuleiro(tabuleiro);
            if (jogadorAtual == 1) {
                printf("\nVez de %s (Jogador 1 - %c):\n", jogador1.nome, converteNumero(jogador1.peca));
                rodadaJogador(tabuleiro, jogador1.peca);
                if(verificaVencedor(tabuleiro, jogador1.peca)){
                    printf("\n%s (Jogador 1) Venceu!\n", jogador1.nome);
                    placar1.vitorias++;
                    placar2.derrotas++;
                    break;
                }
            } else {
                printf("\nVez de %s (Jogador 2 - %c):\n", jogador2.nome, converteNumero(jogador2.peca));
                rodadaJogador(tabuleiro, jogador2.peca);
                if(verificaVencedor(tabuleiro, jogador2.peca)){
                     printf("\n%s (Jogador 2) Venceu!\n", jogador2.nome);
                    placar2.vitorias++;
                    placar1.derrotas++;
                    break;
                }
            }
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1; 
        }

        if(!verificaVencedor(tabuleiro, jogador1.peca) && !verificaVencedor(tabuleiro, jogador2.peca)){
             printf("\nDeu Velha!\n");
             placar1.velhas++;
             placar2.velhas++;
        }
        desenharTabuleiro(tabuleiro);

        jogador1.pontuacao = calculaPontuacao(placar1);
        jogador2.pontuacao = calculaPontuacao(placar2);

        mostrarUsuario(&jogador1);
        mostrarUsuario(&jogador2);

        printf("\n1. Continuar\n2. Voltar ao Menu\n");
        printf("Escolha uma opção: ");
        scanf("%d", &valor);

    } while (valor != 2);

    inserirRanking(jogador1);
    inserirRanking(jogador2);

    return 0;
}
//inicia a visualização do Ranking, fazendo a leitura do arquivo e apresentando ao usuario
int Ranking(){

  void ordenarVetor(struct Jogador *jogadores, int);
  int mostrarUsuarioRanking(struct Jogador);

  int sair;
  struct Jogador jogadores[POSICOES_PLACAR]; 

  //variaveis auxiliares
  char nome[20];
  int pontuacao;
  int ranking_total = 0;

  system("clear");
  printf(".......... Ranking ..........");

  //ponteiro do arquivo
  FILE *arquivo;

  //abrindo o arquivo somente para leitura
  arquivo = fopen("placar.txt", "r");

  //caso tiver um erro na abertura do arquivo ele não executa as operações
  if(arquivo == NULL){
      printf("\nErro ao abrir o arquivo!\n");
  }else{

    //enquanto não for fim de arquivo o looping será executado e será impresso o texto
    while(fscanf(arquivo, "%s %d", nome, &pontuacao)!=EOF){

      strcpy(jogadores[ranking_total].nome, nome);
      jogadores[ranking_total].pontuacao = pontuacao;
      ranking_total++;
    }
    //fecha o arquivo
    fclose(arquivo);

    // testa se existem pessoas no ranking e ordena para apresenta-lo
    if(ranking_total>0){
      ordenarVetor(jogadores, ranking_total);
      for(int i=0; i < ranking_total; i++){
        //fazer a apresentação 
        mostrarUsuarioRanking(jogadores[i]);
      }
    }
  }

  //travar o loop
  printf("\n\nSelecione 1 para voltar:");
  scanf("%d", &sair);  

  return 0;
}

//fazer a ordenação dos ranking
void ordenarVetor(struct Jogador jogadores[POSICOES_PLACAR], int ranking_total){
  int status;
  do{
    status = 0;
    for(int i=ranking_total; i>0; i--){
      if(jogadores[i].pontuacao> jogadores[i-1].pontuacao){
        struct Jogador aux;
        aux = jogadores[i];
        jogadores[i] = jogadores[i-1];
        jogadores[i-1] = aux;
        status = 1;
      }
    }
  }while(status);
}

//adicionar Jogador ao arquivo de ranking
void inserirRanking(struct Jogador jogador){

  FILE *arquivo;
  //abrindo o arquivo
  arquivo = fopen("placar.txt", "a");

  //salvando dados no aquivo
  fprintf(arquivo, "\n%s %d", jogador.nome, jogador.pontuacao);

  //fechando o arquivo
  fclose(arquivo);
}

//apresenta os dados do usuario
void mostrarUsuario(struct Jogador *jogador){
  printf("\n---------------------------");
  printf("\nNome: %s \t", (*jogador).nome);
  printf("Pontuação: %d\n", (*jogador).pontuacao);

}

//apresenta os dados do usuario
int mostrarUsuarioRanking(struct Jogador jogador){

  for(int i = 0; i < strlen(jogador.nome); i++){
    if((jogador.nome[i] < 'a' && jogador.nome[i] > 'z') || (jogador.nome[i] < 'A' && jogador.nome[i] > 'Z') ||  
    (jogador.pontuacao > 10000) || (jogador.pontuacao < 0)){
      return 0;
    }
  }

  printf("\n\n%s \t", jogador.nome);
  printf("%d\n", jogador.pontuacao);
  printf("-----------------------------");

  return 1;
}

//apresenta o placar
void mostrarPlacar(struct Placar placar){

  printf("\n| Você || Velha || Bot |\n");
  printf("|   %d  ||   %d   ||  %d  | \n\n", placar.vitorias, placar.velhas, placar.derrotas);
}

//recebe o placar e faz o calculo da sua pontuacao
int calculaPontuacao(struct Placar placar){
  int pontuacao = 0;

  int vitorias = placar.vitorias * 3;
  int derrotas = placar.derrotas * 2;
  int empates = placar.velhas;

  pontuacao = ((vitorias + empates)-derrotas);

  //caso a pontuacao seja menor que 0, será retornado o valor 0
  return pontuacao > 0 ? pontuacao : 0;
}

int creditos(){
    int sair;


    printf("\n .......... Créditos .......... \n\n");

    printf("  Jogo criado e desenvolvido por:  \n");
    printf("\nNome/RGM - Robert Emanuel             /********");

  printf("\n\nSelecione 1 para voltar: ");
  scanf("%d", &sair);  

  return 0;
}
