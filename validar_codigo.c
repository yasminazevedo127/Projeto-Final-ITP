#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include "validar_codigo.h"


int largura, altura;

int quant_tipo_elementos(char codeStr[]){

    setlocale(LC_ALL,"");
    int validade;
    char verificacao[] = "0123456789";

    // Verifica a validade do c�digo informado pelo o usu�rio
    if(!(strlen(codeStr) == 8)){
        printf("Identificador n�o possui 8 d�gitos!\n");
        return 0;

    }else{
        // Verifica se todos os caracteres do código são numéricos
        for(int i = 0; i < strlen(codeStr); ++i){

            int testeElem = 0;

            for(int j = 0; j < 10; ++j){
                if(codeStr[i] == verificacao[j]){
                    testeElem = 1;
                }
            }
            // Se algum caractere não for numérico, o código é inválido
            if(testeElem == 0){
                validade = 0;
                printf("Identificador cont�m valores n�o num�ricos!\n");
                break;

            }else{
                validade = 1;
            }
        }
        return validade;
    }

}

// Converte o c�digo tipo string para tipo inteiro
int convertInter(char x){
    char verificador[] = "0123456789";

    // Percorre o conjunto de números válidos e retorna o valor correspondente ao caractere
    for(int i = 0; i < 10; ++i){
        if(x == verificador[i]){
            return i;
            break;
        }
    }
    return -1; // Retorna -1 se o caractere não for numérico
}

// Função que realiza a validação do dígito verificador baseado nos 7 primeiros dígitos.
// A validação é feita com a fórmula ponderada utilizando os multiplicadores 1 e 3 alternadamente.
int validacao_identificador(int vetor[]){

    setlocale(LC_ALL,"");
    int soma_ponderada = 0;

    // Calcula a soma ponderada utilizando multiplicadores alternados (1 e 3)
    for(int i = 0; i < 7; ++i){

        if(((i+1)%2) != 0){
            soma_ponderada = soma_ponderada + (vetor[i]*3);

        }else{
            soma_ponderada = soma_ponderada + vetor[i];

        }
    }

    int cont = 1;
    int mult_dez = 10*cont;

    // Ajusta o multiplicador até ser maior que a soma ponderada
    while(soma_ponderada > mult_dez){
        cont = cont +1;
        mult_dez = cont*10;
    }

    // Calcula o dígito verificador e compara com o valor do vetor
    int digito_verificador = mult_dez - soma_ponderada;

    if(digito_verificador == vetor[7]){
        return 1;// Dígito verificador válido
    }else{
        printf("O d�gito verificador do identificador � inv�lido (n�o corresponde aos valores anteriores)!\n");
        return 0; // Dígito verificador inválido
    }
}


// Função para verificar a primeira linha (cabeçalho "P1")
int verificar_primeira_linha(FILE *arquivo) { //DEU CERTO
    char linha[100];  // Tamanho da linha a ser lida

    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove qualquer caractere de nova linha ao final
        linha[strcspn(linha, "\n")] = '\0';

        // Verifica se a linha contém exatamente "P1"
        if (strcmp(linha, "P1") == 0) {
            return 1;  // Retorna 1 se a primeira linha for "P1"
        } else {return 0;}
    }
    return 0;
}

//verificando segunda linha em busca da altura e largura do codigo de barras
int verificar_segunda_linha(FILE *arquivo) { ///DEU CERTO
    char linha[100];

     // Lê a segunda linha do arquivo
    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove qualquer caractere de nova linha ao final
        linha[strcspn(linha, "\n")] = '\0';

        // Usa sscanf para tentar ler dois inteiros da linha
        if (sscanf(linha, "%d %d", &largura, &altura) == 2) {
            return 1;  // Retorna 1 se a linha contiver exatamente dois inteiros
        }
    }
    return 0;  // Retorna 0 caso contrário
}



int checar_espace(FILE *arquivo, int largura) {
    char linha[largura*2];  // Cria o buffer com o tamanho exato da linha (considerando o terminador '\0')
    int espace = 0;
 
    // Lê duas primeiras linhas do arquivo
    fgets(linha, sizeof(linha), arquivo);
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remover a nova linha (\n) que fgets pode adicionar, se houver
        linha[strcspn(linha, "\n")] = '\0';

        // Verificar se a linha contém '1'
        if (strchr(linha, '1') != NULL) {
            break;  // Parar a contagem ao encontrar o primeiro '1'
        }

        // Verificar se a linha é composta apenas por '0's
        int i = 0;
        for (i = 0; linha[i] != '\0'; i++) {
            if (linha[i] != '0') {
            break;
            }
        }

        // Se a linha for composta apenas por '0's, incrementa o contador
        if (linha[i] == '\0') {
            espace++;
        }
    }

    return espace; // Retorna a quantidade de linhas compostas apenas por '0's
}

int verificar_codigo_de_barras(char** matriz_binaria, int* digitos_codigo_barras, int espace){

    if(espace == -1){ //checando flag de erro
        printf("O codigo de barras nao foi encontrado.");
        return 0;
    } else if(espace == -2){ //checando flag de erro
        printf("Codigo de barras invalido: Caracteres invalidos presentes no arquivo.");
        return 0;
    }

    if(matriz_binaria[0][0] == '2'){ //checando flag de erro
        printf("Codigo de barras invalido: Caracteres invalidos presentes no arquivo.");
        return 0;
    }

    if(digitos_codigo_barras[0]== -1){ //checando flag de erro
        printf("Codigo de barras invalido: Digitos do codigo de barras sao invalidos");
        return 0;
    }

    return 1; //caso nenhum problema for encontrado
}