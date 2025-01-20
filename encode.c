#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz_final.h"
#include "validar_codigo.h"
#include "codigo_bin.h"

// Definições de constantes com valores padrão para o código de barras EAN-8
#define ESPACAMENTO_LATERAL_PADRAO 4
#define LARGURA_AREA_PADRAO 3
#define ALTURA_CODIGO_PADRAO 50
#define NOME_IMAGEM_PADRAO "barcode.pbm"

int main(void){
    // Definição das variáveis utilizadas na implementação do código de barras
    int** matriz_imagem;  // Matriz para armazenar a imagem do código de barras
    char codigo_string[100];  // String para armazenar o código EAN-8 fornecido pelo usuário
    int codigo_int[8];  // Vetor para armazenar os dígitos do código EAN-8 em formato numérico
    int* codigo_ean = calloc(67, sizeof(int));  // Vetor para armazenar a representação binária do código de barras
    int espaco_lateral, altura_cod, largura_area;  // Variáveis para armazenar o espaçamento lateral, altura e largura do código
    char nome[100];  // Nome do arquivo da imagem (sem extensão)
    char nome_imagem_completa[100];  // Nome completo do arquivo com a extensão ".pbm"
    char resposta_usuario;  // Variável para verificar a resposta do usuário nas entradas personalizadas
    int linhas_img, colunas_img;  // Dimensões da imagem gerada (altura e largura)

    // Solicita o código EAN-8 ao usuário
    printf("Informe o codigo no padrao EAN-8:\n");
    scanf("%s", codigo_string);

    // Valida o código EAN-8 informado pelo usuário e converte os caracteres para inteiros
    if(quant_tipo_elementos(codigo_string)){
        for(int i = 0; i < 8; ++i){
            codigo_int[i] = convertInter(codigo_string[i]);  // Converte cada dígito para inteiro
        }

        // Verifica a validade do código EAN-8 informado (verificação do dígito verificador)
        if(validacao_identificador(codigo_int)){
            // Solicita o espaçamento lateral para o código de barras, com opção de valor personalizado ou padrão
            printf("Deseja especificar o espacamento lateral do codigo na imagem (s/n)? ");
            scanf(" %c", &resposta_usuario);

            if(resposta_usuario == 's'){
                printf("Espacamento lateral: ");
                scanf("%d", &espaco_lateral);
            } else {
                espaco_lateral = ESPACAMENTO_LATERAL_PADRAO;  // Valor padrão
            }

            // Solicita a largura da área do código de barras (quantidade de pixels por área)
            printf("Deseja especificar a quantidade de pixels por area do codigo (s/n)? ");
            scanf(" %c", &resposta_usuario);

            if(resposta_usuario == 's'){
                printf("Pixels por area: ");
                scanf("%d", &largura_area);
            } else {
                largura_area = LARGURA_AREA_PADRAO;  // Valor padrão
            }

            // Solicita a altura do código de barras em pixels
            printf("Deseja especificar a altura do codigo de barras (s/n)? ");
            scanf(" %c", &resposta_usuario);

            if(resposta_usuario == 's'){
                printf("Altura do codigo (pixels): ");
                scanf("%d", &altura_cod);
            } else {
                altura_cod = ALTURA_CODIGO_PADRAO;  // Valor padrão
            }

            // Solicita o nome do arquivo de imagem
            printf("Deseja especificar o nome da imagem (s/n)? ");
            scanf(" %c", &resposta_usuario);

            if(resposta_usuario == 's'){
                printf("Nome da imagem: ");
                scanf("%s", nome);
                strcpy(nome_imagem_completa, strcat(nome, ".pbm"));  // Adiciona a extensão ".pbm"
            } else {
                strcpy(nome_imagem_completa, NOME_IMAGEM_PADRAO);  // Valor padrão para o nome do arquivo
            }

            // Calcula as dimensões da imagem (altura e largura)
            linhas_img = (altura_cod + 2 * espaco_lateral);  // A altura total inclui o espaçamento lateral superior e inferior
            colunas_img = (67 * largura_area + 2 * espaco_lateral);  // A largura total inclui o espaçamento lateral esquerdo e direito

            // Define os bits padrão para o código EAN-8
            bits_padrao(codigo_ean);

            // Converte cada dígito do código EAN-8 para sua representação binária, dividindo em dois grupos (L e R)
            for(int i = 0; i < 8; ++i){
                if(i < 4){
                    conversor_L_code(codigo_ean, codigo_int[i]);  // Converte os primeiros 4 dígitos para o código L
                } else {
                    conversor_R_code(codigo_ean, codigo_int[i]);  // Converte os últimos 4 dígitos para o código R
                }
            }

            // Dimensiona a matriz que representará a imagem do código de barras
            matriz_imagem = dimensionar(linhas_img, colunas_img);

            // Monta a matriz com a representação binária do código de barras
            montarMatriz(matriz_imagem, codigo_ean, espaco_lateral, largura_area, linhas_img, colunas_img);

            // Gera e imprime a imagem no formato PBM com o nome especificado
            print(matriz_imagem, linhas_img, colunas_img, nome_imagem_completa);
        }
    }

    return 0;
}