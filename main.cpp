#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstring>

using namespace std;

//tamanho vetor de strings
#define TAM_VETOR 10000
#define TAM_STRING 100

//Lendo arquivo
int abrirArquivo(char l[TAM_VETOR][TAM_STRING], char* nomeArquivo){ //retorno do tipo int, onde a função retornará a quantidade de linhas lidas no arquivo

    FILE* arquivo = fopen (nomeArquivo, "r");
    int i = 0;

    if (arquivo == NULL){
        printf ("Erro ao abrir o arquivo!");
    }else{
        int result;
        char aux[50];

        result = fscanf (arquivo, "%[^\n]\n", aux);

        while (result != EOF){

        strcpy(l[i++],aux);

        result = fscanf (arquivo, "%[^\n]\n", aux);
        }
    }

    fclose (arquivo);
    return i;
}

void calcPrefix(char p[], int lps[]) {
    lps[0] = 0;
    int i = 0, j = 1;
    while (j < strlen(p)) {
        if (p[i] == p[j]) {
            lps[j] = i + 1;
            i++;
            j++;
        } else if (p[i] != p[j] && i != 0) {
            i = lps[i - 1];
        } else if (p[i] != p[j]) {
            lps[j] = 0;
            j++;
        }
    }
}

int kmp(char t[], char p[]) {

    int lps[strlen(p)];
    calcPrefix(p, lps);

    int i = 0, j = 0, k, l = 0;

    while (i <= strlen(t)) {
        int r = i - j;
        k = j;
        for (l = i; j < strlen(p); j++, l++) {
            if (t[l] == p[j]) {
                k++;
            } else {
                break;
            }
        }
        if (k == strlen(p)) {
            return r;
        }
        if (lps[j - 1] == 0) {
            i = l + 1;
        } else {
            i = l;
        }
        j = lps[j - 1];
    }

    return -1;
}

//imprimindo lista
void imprimeLista(char l[TAM_VETOR][TAM_STRING], int n, char nome[TAM_STRING]){

    for (int i = 0; i < n; i++){
        if (kmp(l[i], nome) != -1) {
            printf ("%d -\t%s\n",i+1, l[i]);
        }
    }
    printf ("\n");
}

int main (){

    char listaNomes[TAM_VETOR][TAM_STRING];
    int quantidadeNomes;
    char nome[TAM_STRING];

    quantidadeNomes = abrirArquivo(listaNomes, "nomes.txt");

    if (quantidadeNomes > 0){

        printf("Digite um nome: ");
        scanf (" %[^\n]", nome);

        imprimeLista(listaNomes, quantidadeNomes, nome);

    }
    return 0;
}
