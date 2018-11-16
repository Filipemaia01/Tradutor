#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <list>
using namespace std;

typedef struct diretiva {
  char nome[50];
  int valor;
} diretiva;

void preencheparametro(int *i, int *parametro, int *mudaadic, int *mudarot, int *mudaop, int *mudaop1, int *mudaop2, char palavra[], char rotulo[], char operacao[], char operando1[], char operando2[], char letra, char adicionado[]) {
  if(*i>0 || letra == '+'){ //verifica se ja tem alguma palavra sendo formada//
    if ((letra == ' ' || letra == '\n' || letra == '\t' || letra == ':' || letra == '+')){ //verifica se eh termino de palavra//
      if (letra == ':'){ //eh rotulo?//
        *mudarot = *mudarot + 1;
        *i = *i-1;
        printf("rotulo: ");
        strcpy(rotulo, palavra); // completa o rotulo
        printf("%s\t", rotulo);
      }
      else if (*mudaadic == 1) {
        strcpy(adicionado, palavra);
        printf("adicionado: %s\t", adicionado);
      }
      else {
        if (letra == '+') {
          *mudaadic = 1;
        }
        if (*parametro == 1 && *mudaop == 0){
          *mudaop = 1;
          printf("operacao: ");
          strcpy(operacao, palavra);
          printf("%s\t", operacao);
        }
        if (*parametro == 2 && *mudaop1 == 0){
          *mudaop1 = 1;
          printf("operando1: ");
          strcpy(operando1, palavra);
          printf("%s\t", operando1);
        }
          if (*parametro == 3 && *mudaop2 == 0){
            *mudaop2 = 1;
            printf("operando2: ");
            strcpy(operando2, palavra);
            printf("%s\t", operando2);
          }
          *parametro = *parametro + 1;
        }
      *i=0;
    }
  }
}

int descobreinstrucao (char instrucao[]) { // funcao que descobre a instrucao

  if(strcmp(instrucao,"add")==0){
    return 1;
  }
  else if(strcmp(instrucao,"sub")==0){
    return 2;
  }
  else if(strcmp(instrucao,"mult")==0){
    return 3;
  }
  else if(strcmp(instrucao,"div")==0){
    return 4;
  }
  else if(strcmp(instrucao,"jmp")==0){
    return 5;
  }
  else if(strcmp(instrucao,"jmpn")==0){
    return 6;
  }
  else if(strcmp(instrucao,"jmpp")==0){
    return 7;
  }
  else if(strcmp(instrucao,"jmpz")==0){
    return 8;
  }
  else if(strcmp(instrucao,"copy")==0){
    return 9;
  }
  else if(strcmp(instrucao,"load")==0){
    return 10;
  }
  else if(strcmp(instrucao,"store")==0){
    return 11;
  }
  else if(strcmp(instrucao,"input")==0){
    return 12;
  }
  else if(strcmp(instrucao,"output")==0){
    return 13;
  }
  else if(strcmp(instrucao,"stop")==0){
    return 14;
  }
  else {
    return 0;
  }
}

int descobrediretiva (char instrucao[]) {

  if(strcmp(instrucao,"space")==0){
    return 1;
  }
  else if(strcmp(instrucao,"const")==0){
    return 2;
  }
  else if(strcmp(instrucao,"section")==0) {
    return 3;
  }
  else if(strcmp(instrucao,"public")==0) {
    return 4;
  }
  else if(strcmp(instrucao,"extern")==0) {
    return 5;
  }
  else if(strcmp(instrucao, "begin")==0) {
    return 6;
  }
  else if (strcmp(instrucao, "end")==0) {
    return 7;
  }
  else if (strcmp(instrucao, "equ")==0) {
    return 8;
  }
  else {
    return 0;
  }
}

void preproc (char arquivo_entrada[], char arquivo_precomp[])  { // funcao que realiza o preprocessamento
  FILE *instrucoes, *instrucoes0;
  char letra, letrant, palavra[100], rotulo[50], operacao[50], operando1[50], operando2[50], operando3[10][50], adicionado[50];
  int i, j,letrint, parametro, tam_rot, mudarot=0, mudaop=0, mudaop1=0, mudaop2=0, ignoralinha=0, mudaadic=0, contadorlinha=1;
  list<diretiva> tab_preproc;
  diretiva elemento_preproc;
  list<diretiva>::iterator iterador_p;

  instrucoes = fopen(arquivo_entrada, "r");
  instrucoes0 = fopen(arquivo_precomp, "w+");

  parametro=1;
  i=0;
  while(!feof(instrucoes)){ // enquanto o arquivo nao terminar
    letrant = letra;
    letra = getc(instrucoes);
    if (letra == ';'){ //se for comentario, ignora tudo ate o \n//
      while (letra != '\n') {
        letra = getc(instrucoes);
      }
    }
    if(letra == '+' && (letrant == '\t'|| letrant == ' ')){ // se o char for + e a letra anterior for espaco, eh porque a palavra anterior ja foi preenchida
      mudaadic = 1;
    }

    letrint = letra;
    if (letrint > 64 && letrint < 91){ //verifica se letra eh maiuscula e, se sim, troca por minuscula//
      letrint = letrint + 32;
      letra = letrint;
    }

    if (letra != ' ' && letra != '\n' && letra != '\t' && letra != ':' && letra != ',' && letra != '+'){ //verifica se o char faz parte de alguma palavra//
      palavra[i]=letra;
      palavra[i+1] = '\0';
      i++;
    }

    if(i>0 || letra == '+'){ //verifica se ja tem alguma palavra sendo formada//
      if ((letra == ' ' || letra == '\n' || letra == '\t' || letra == ':' || letra == '+')){ //verifica se eh termino de palavra//
        if (letra == ':'){ //eh rotulo?//
          mudarot = mudarot + 1;
          printf("rotulo: ");
          strcpy(rotulo, palavra);
          printf("%s\t", rotulo);
        }
        else if (mudaadic == 1) {
          strcpy(adicionado, palavra);
          printf("adicionado: %s\t", adicionado);
        }
        else {
          if (letra == '+') {
            mudaadic = 1;
          }
          if (parametro == 1 && mudaop == 0){
            mudaop = 1;
            printf("operacao: ");
            strcpy(operacao, palavra);
            printf("%s\t", operacao);
          }
          if (parametro == 2 && mudaop1 == 0){
            mudaop1 = 1;
            printf("operando1: ");
            strcpy(operando1, palavra);
            printf("%s\t", operando1);
          }
          if (parametro == 3 && mudaop2 == 0){
            mudaop2 = 1;
            printf("operando2: ");
            strcpy(operando2, palavra);
            printf("%s\t", operando2);
          }
          if (parametro > 3) {
            strcpy(operando3[parametro-4], palavra);
          }
          parametro = parametro + 1;
        }
        i=0;
      }
    }

    if (letra == '\n' && mudaop == 1){ //se a linha terminou//
      if (mudaop == 1){
        if (strcmp(operacao, "equ")==0){ // se for equ, armazena nome do rotulo e valor
          printf("rotulo: %s\n", rotulo);
          strcpy(elemento_preproc.nome, rotulo);
          elemento_preproc.valor = atoi(operando1); //corrigir o inteiro dado pela tabela ascii
          printf("elemento_nome: %s\n", elemento_preproc.nome);
          printf("valor: %d\t", elemento_preproc.valor);
          tab_preproc.push_back(elemento_preproc);
        }
        else if (strcmp(operacao, "if")==0){
          iterador_p = tab_preproc.begin();
          while(strcmp(iterador_p->nome, rotulo)!=0 && iterador_p != tab_preproc.end()){ //tenta achar rotulo na lista de simbolos//
            printf("iterador->nome: %s , rotulo: %s\n", iterador_p->nome, rotulo);
            iterador_p++;
          }
          if (iterador_p == tab_preproc.end()){
            printf("Erro! Rotulo nao encontrado!\t");
          }
          else {
            if (iterador_p->valor != 1) {
              ignoralinha = 1;
            }
          }
        }
        else{
          if (ignoralinha == 0) {
            printf("mudarot: %d\t", mudarot);
            if (mudarot > 0) {
              fputs(rotulo, instrucoes0);
              fputs(":", instrucoes0);
              fputs("\t", instrucoes0);
            }
            fputs(operacao, instrucoes0);
            if (mudaop1 == 1) {
              fputs("\t", instrucoes0);
              fputs(operando1, instrucoes0);
            }
            if (mudaop2 == 1) {
              fputs("\t", instrucoes0);
              fputs(operando2, instrucoes0);
            }
            if(parametro > 3) {
              for(j=4; j < parametro; j++) {
                fputs("\t", instrucoes0);
                fputs(operando3[j-4], instrucoes0);
              }
            }
            if (mudaadic == 1) {
              fputs("+", instrucoes0);
              fputs(adicionado, instrucoes0);
            }
            fputs("\n", instrucoes0);
          }
          else {
            ignoralinha = 0;
          }
        }
      }
      contadorlinha++;
      parametro = 1;
      printf(" \n");
      mudarot = 0; mudaop = 0; mudaop1 = 0; mudaop2 = 0; mudaadic = 0;
    }
  }
  fclose(instrucoes);
  fclose(instrucoes0);

  printf ("\nfim pre processamento!");
  printf("\n -------------------------------------------- \n");
}

void converteia32(int num_op, int num_dir, FILE *entrada, FILE *saida, char rotulo[], char operacao[], char operando1[], char operando2[], char adicionado[], int mudaop) {

  if (mudaop > 0) {
    if (num_op == 1 || num_op == 2) {
      fprintf(saida, "%s  %s,  %s\n", operacao, "eax", operando1);
    }
    else if (num_op == 5) {
      fprintf(saida, "%s  %s \n", operacao, operando1);
    }
    else if (num_op == 6) {
      fprintf(saida, "%s  %s,  %s\n", "cmp", "eax", "zero");
      fprintf(saida, "%s  %s\n", "jl", operando1);
    }
    else if (num_op == 7) {
      fprintf(saida, "%s  %s,  %s\n", "cmp", "eax", "zero");
      fprintf(saida, "%s  %s\n", "jg", operando1);
    }
    else if (num_op == 8) {
      fprintf(saida, "%s  %s\n", "jz", operando1);
    }
    else if (num_op == 10) {
      fprintf(saida, "%s  %s,  %s\n", "mov", "eax", operando1);
    }
    else if (num_op == 11) {
      fprintf(saida, "%s  %s,  %s\n", "mov", operando1, "eax");
    }
    else if (num_op == 14) {
      fprintf(saida, "%s  %s,  %s\n", "mov", "eax", "1");
      fprintf(saida, "%s  %s  %s\n", "mov", "ebx", "0");
      fprintf(saida, "%s  %s\n", "int", "80h");
    }
    else if (num_op == 0 && num_dir !=0) {
      if (num_dir == 3) {
        fprintf(saida, "%s  %s%s\n", operacao, " .", operando1);
      }
      else if (num_dir == 8) {
        fprintf(saida, "%s  %s  %s\n", rotulo, "EQU", operando1);
      }
    }
  }
}

int main (int argc, char *argv[]){
  int i=0, parametro=1, mudaadic=0, mudarot=0, mudaop=0, mudaop1=0, mudaop2=0, num_op, num_dir, letrint;
  char arquivo_entrada[50], arquivo_saida[50], arquivo_precomp[50], letra, palavra[50], rotulo[50], operacao[50],
  operando1[50], operando2[50], adicionado[50];
  FILE *entrada, *precomp, *saida;

  if(argc != 2) {
    printf("Erro no numero de argumentos!\n");
    return 0;
  }

  strcpy(arquivo_entrada, argv[1]);
  strcpy(arquivo_precomp, argv[1]);
  strcpy(arquivo_saida, argv[1]);
  strcat(arquivo_entrada, ".asm");
  strcat(arquivo_precomp, ".pre");
  strcat(arquivo_saida, ".txt");

  cout << arquivo_entrada << " ";
  cout << arquivo_saida << endl;

  preproc (arquivo_entrada, arquivo_precomp);

  precomp = fopen(arquivo_precomp, "r");
  saida = fopen(arquivo_saida, "w+");
  letra = getc(precomp);

  while(letra != EOF){
    letrint = letra;
    if (letrint > 64 && letrint < 91){ //verifica se letra eh maiuscula e, se sim, troca por minuscula//
      letrint = letrint + 32;
      letra = letrint;
    }
    if (letra != ' ' && letra != '\n' && letra != '\t'  && letra != '+' && letra != ':'){ //verifica se o char faz parte de alguma palavra//
      palavra[i]=letra;
      palavra[i+1] = '\0';
      i++;
    }

    preencheparametro(&i, &parametro, &mudaadic, &mudarot, &mudaop, &mudaop1, &mudaop2, palavra, rotulo, operacao, operando1, operando2, letra, adicionado);

    if (letra == '\n'){ //se a linha terminou//
      num_op = descobreinstrucao(operacao);
      num_dir = descobrediretiva(operacao);
      converteia32(num_op, num_dir, entrada, saida, rotulo, operacao, operando1, operando2, adicionado, mudaop);
      parametro = 1;
      mudarot = 0; mudaop = 0; mudaop1 = 0; mudaop2 = 0; mudaadic = 0;
      cout << endl;
    }
//    cout << letra;
    letra = getc(precomp);
  }
  fclose(saida);
  fclose(precomp);

  return 0;
}
