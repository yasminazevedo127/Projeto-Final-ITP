#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "matriz_final.h"
#include "validar_codigo.h"


// Função para alocar dinamicamente uma matriz de inteiros
// A função retorna um ponteiro para a matriz alocada, com o número especificado de linhas e colunas.
int** dimensionar(int linhas, int colunas){
    int**m;
    m = calloc(linhas, sizeof(int*));

    // Aloca a memória para cada linha da matriz
    for(int i = 0; i < linhas; ++i){
        m[i] = calloc(colunas, sizeof(int));
    }

    return m; // Retorna o ponteiro para a matriz alocada
}

//função para montar a matriz ajustada de acordo com a largura de cada área e baseada no vetor_ean
void montarMatriz(int** matriz, int* vetor, int borda, int largura_area, int linhas, int colunas){

    int i = borda;
    int x = 0;

    // Preenche a matriz com os valores do vetor, ajustando a largura da área
    while(i < (colunas - borda)){
        
        int cont = 0;
        // Preenche a linha na posição especificada, respeitando a largura de cada área
        while(cont < largura_area){
            matriz[borda][i] = vetor[x];
            cont = cont + 1;
            i = i + 1;
        }
        x = x + 1;
    }
    // Preenche todas as linhas (exceto as bordas) com a mesma linha que a borda
    for(int linhaAtual = 0; linhaAtual < linhas; ++linhaAtual){
        if(linhaAtual > borda && linhaAtual < linhas - borda){
            matriz[linhaAtual] = matriz[borda];
        }
    }

    free(vetor);
}

// Função que printa a matriz final no arquivo PBM
void print(int** matriz, int linhas, int colunas, char image_name[]) {

    setlocale(LC_ALL, "");
    char confirmacao;
    FILE *saida_pbm;

    // Tenta abrir o arquivo no modo de leitura
    saida_pbm = fopen(image_name, "r");

    // Caso o arquivo ainda não exista, cria um novo arquivo e escreve a matriz nele
    if (saida_pbm == NULL) {
        saida_pbm = fopen(image_name, "w+"); // Abre o arquivo para escrita
        fprintf(saida_pbm, "P1\n");
        fprintf(saida_pbm, "%d %d\n", colunas, linhas);

        // Escreve os valores da matriz no arquivo
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                fprintf(saida_pbm, "%d", matriz[i][j]);
            }
            fprintf(saida_pbm, "\n");
        }
        fclose(saida_pbm);

        free(matriz);

    } else {
        printf("O arquivo a ser criado já existe. Deseja sobrescrevê-lo (s/n)?\n");
        scanf(" %c", &confirmacao);
    }

    if (confirmacao == 's') {
        saida_pbm = fopen(image_name, "w+");
        fprintf(saida_pbm, "P1\n");
        fprintf(saida_pbm, "%d %d\n", colunas, linhas);

        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                fprintf(saida_pbm, "%d", matriz[i][j]);
            }
            fprintf(saida_pbm, "\n");
        }
        fclose(saida_pbm);

        free(matriz);

    } else if (confirmacao == 'n') {
        printf("Arquivo resultante já existe!\n");
    }
}

//transformar codigo de barras em matriz

//TODO: criar um vetor com a linha espacamento_superior+1, a partir da coluna espacamento_superior+1 até a coluna espacamento_superior-1
//a partir da coluna espacamento_superior+1 checar quantos 1 seguidos, para saber a area.

int calcular_area(int largura, int espace, FILE *arquivo){

    int area = 0;
    char linha[largura+1];  
    int linha_central = (altura / 2)+2;

    fseek(arquivo, linha_central * largura * sizeof(char), SEEK_SET);

    //pulando para a linha após o espacamento
    for(int i = 0; i<espace+1;i++){ 
        fgets(linha, sizeof(linha), arquivo);
    }

    fgets(linha, sizeof(linha), arquivo); //lê uma linha do código de 
    
    for (int i = espace; i < largura; i++) { //conta quantos 1s seguidos tem, para descobrir a area
            if (linha[i] == '1') {
                area++;  
            } else if (linha[i] == '0'){
                break;
            }
    }
    
    return area;
}

void processar_codigo(char** vetores, FILE* arquivo, int start, int end, int indice_inicial, int area, int* cont) {

    for (int i = indice_inicial; i < indice_inicial + 4; i++) {
        int j = 0; // Índice para posicionar os caracteres em cada vetor de destino
        // Enquanto não ultrapassar o limite de 'end' e o número de caracteres lidos não for maior que 7
        while (*cont < end && j < 7) {
            char c = fgetc(arquivo); 
            // Se o contador de leitura ultrapassou o início e está no intervalo certo para ser armazenado
            if (*cont > start && (*cont - start - 1) % area == 0) {
                vetores[i][j++] = c; 
            }
            (*cont)++; 
        }
        vetores[i][7] = '\0'; 
    }
}

char** criar_vetores(int largura, int area, int espace, FILE *arquivo) {
    char linha[largura * 2];  // Buffer para leitura da linha do PBM
    char **vetores = (char **)malloc(8 * sizeof(char *));
    for (int i = 0; i < 8; i++) {
        vetores[i] = (char *)malloc(8 * sizeof(char)); // 7 caracteres + terminador \0
    }

    // Pular cabeçalho e espaços iniciais
    for (int i = 0; i < espace + 3; i++) {
        fgets(linha, sizeof(linha), arquivo);
    }

    char c;
    int cont = 0;
    int startL = espace + (area * 3);                      // Após o marcador inicial
    int startR = startL + (area * 4 * 7) + (area * 5);     // Após o marcador central

    // Extração dos primeiros 4 dígitos (L-code)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 7; j++) {
            int posicao = startL + (i * area * 7) + (j * area);
            if (posicao < largura) {
                vetores[i][j] = linha[posicao];  
            } else {
                vetores[i][j] = '0';  // Preenchendo com '0' caso a posição esteja errada
            }
        }
        vetores[i][7] = '\0';  // Finaliza a string
    }

    // Extração dos últimos 4 dígitos (R-code)
    for (int i = 4; i < 8; i++) {
        for (int j = 0; j < 7; j++) {
            int posicao = startR + ((i - 4) * area * 7) + (j * area);
            if (posicao < largura) {
                vetores[i][j] = linha[posicao];  
            } else {
                vetores[i][j] = '0';  
            }
        }
        vetores[i][7] = '\0';  
    }

    return vetores;
}
