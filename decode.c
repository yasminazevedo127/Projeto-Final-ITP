#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz_final.h"
#include "validar_codigo.h"
#include "codigo_bin.h"

// Função principal: recebe um arquivo PBM como parâmetro.
int main(int argc, char *argv[]) {

    // Verifica se o nome do arquivo foi passado como parâmetro.
    if (argc != 2) { 
        printf("\nErro: Nenhum arquivo foi escolhido!");
        return 1;
    }

    // Abre o arquivo especificado no modo de leitura.
    FILE *arquivo = fopen(argv[1], "r");

    // Verifica se o arquivo existe e é acessível.
    if (arquivo == NULL) {
        printf("\nErro: O arquivo com o nome informado não existe!"); 
        return 1;
    }

    // Verifica se a primeira linha do arquivo contém "P1" (indica formato PBM).
    if (!verificar_primeira_linha(arquivo)) {
        printf("Erro: Arquivo inválido. Não está no formato PBM.\n");
        fclose(arquivo);
        return 1;
    }

    // Verifica a segunda linha para validar as dimensões do arquivo.
    if (!verificar_segunda_linha(arquivo)) {
        printf("Erro: Arquivo inválido. Dimensões inconsistentes.\n");
        fclose(arquivo);
        return 1;
    }

    // Retorna o ponteiro para o início do arquivo, pois as funções anteriores avançaram a leitura.
    fseek(arquivo, 0, SEEK_SET);

    // Calcula o espaçamento lateral no código de barras.
    int espace = checar_espace(arquivo, largura);

    // Retorna o ponteiro para o início do arquivo novamente.
    fseek(arquivo, 0, SEEK_SET);

    // Calcula a largura de cada área do código de barras.
    int area = calcular_area(largura, espace, arquivo);

    // Retorna o ponteiro para o início do arquivo novamente.
    fseek(arquivo, 0, SEEK_SET);

    // Cria uma matriz de strings onde cada linha representa um dígito binário do código de barras.
    char **matriz_binaria = criar_vetores(largura, area, espace, arquivo);

    // Converte cada linha da matriz binária para seu valor numérico em base 10.
    int *digitos_codigo_barras = converter_binario_base10(matriz_binaria);

    //verificando a validade do código de barras:

    if(!verificar_codigo_de_barras(matriz_binaria, digitos_codigo_barras, espace)){
        free(matriz_binaria);
        free(digitos_codigo_barras);
        fclose(arquivo);
        return 0;
    }

    // Valida o código de barras com base no dígito verificador.
    if (validacao_identificador(digitos_codigo_barras)) {
        printf("O código de barras lido é válido.\n");
    } else {
        printf("O código de barras lido é inválido.\n");
    }

    // Exibe o código de barras em base 10 na tela.
    printf("Código de barras lido: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", digitos_codigo_barras[i]);
    }
    printf("\n");

    // Libera a memória alocada para a matriz binária e o vetor de números.
    free(matriz_binaria);
    free(digitos_codigo_barras);

    // Fecha o arquivo.
    fclose(arquivo);

    return 0;
}