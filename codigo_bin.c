#include <stdlib.h>
#include <stdio.h>
#include "codigo_bin.h"
#include <string.h>  // Para usar strcspn e strcmp


// Variáveis globais para controle dos índices de leitura do código de barras L e R
int cont_L = INICIO_L;
int cont_R = INICIO_R;

void bits_padrao(int* vetor){

    vetor[0] = 1;
    vetor[1] = 0;
    vetor[2] = 1;
    vetor[31] = 0;
    vetor[32] = 1;
    vetor[33] = 0;
    vetor[34] = 1;
    vetor[35] = 0;
    vetor[64] = 1;
    vetor[65] = 0;
    vetor[66] = 1;

}
void conversor_L_code(int* codigo, int num){

    if(num == 0){
        int vetor[] = {0,0,0,1,1,0,1};

        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 1){
        int vetor[] = {0,0,1,1,0,0,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 2){
        int vetor[] = {0,0,1,0,0,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 3){
        int vetor[] = {0,1,1,1,1,0,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 4){
        int vetor[] = {0,1,0,0,0,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 5){
        int vetor[] = {0,1,1,0,0,0,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 6){
        int vetor[] = {0,1,0,1,1,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 7){
        int vetor[] = {0,1,1,1,0,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 8){
        int vetor[] = {0,1,1,0,1,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }
    if(num == 9){
        int vetor[] = {0,0,0,1,0,1,1};
        for(int i = cont_L; i < cont_L+7; ++i){
            codigo[i] = vetor[i-cont_L];
        }
        cont_L = cont_L + 7;
    }

}

void conversor_R_code(int* codigo, int num){

    if(num == 0){
        int vetor[] = {1,1,1,0,0,1,0};

        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 1){
        int vetor[] = {1,1,0,0,1,1,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 2){
        int vetor[] = {1,1,0,1,1,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 3){
        int vetor[] = {1,0,0,0,0,1,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 4){
        int vetor[] = {1,0,1,1,1,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 5){
        int vetor[] = {1,0,0,1,1,1,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 6){
        int vetor[] = {1,0,1,0,0,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 7){
        int vetor[] = {1,0,0,0,1,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 8){
        int vetor[] = {1,0,0,1,0,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }
    if(num == 9){
        int vetor[] = {1,1,1,0,1,0,0};
        for(int i = cont_R; i < cont_R+7; ++i){
            codigo[i] = vetor[i-cont_R];
        }
        cont_R = cont_R + 7;
    }

}

// Função para converter uma matriz de strings representando códigos de barras em números binários (base 10)
// 'matriz_recebida' contém os valores recebidos como strings representando códigos binários.
// A função converte os valores e retorna um vetor com os números correspondentes, ou -1 em caso de erro.
int* converter_binario_base10(char** matriz_recebida){
    // Aloca memória para o vetor de 8 inteiros (resultados da conversão)
    int *digitos_codigo_barras = (int*)malloc(8 * sizeof(int));

    // Tabela de códigos binários para os dígitos de 0 a 9 (L e R)
    char* matriz_base[] = {
        "0001101", //0L
        "0011001", //1L
        "0010011", //2L
        "0111101", //3L
        "0100011", //4L
        "0110001", //5L
        "0101111", //6L
        "0111011", //7L
        "0110111", //8L
        "0001011", //9L
        "1110010", //0R
        "1100110", //1R
        "1101100", //2R
        "1000010", //3R
        "1011100", //4R
        "1001110", //5R
        "1010000", //6R
        "1000100", //7R
        "1001000", //8R
        "1110100"  //9R
    };

    int checagem = 0; // Flag para checar se todos os códigos foram convertidos corretamente

    // Converte os primeiros 4 dígitos
    for(int i = 0; i < 4; i++){
        matriz_recebida[i][strcspn(matriz_recebida[i], "\n")] = '\0'; // Remove newline
        for(int j = 0; j < 10; j++){
            if(strcmp(matriz_recebida[i], matriz_base[j]) == 0){
                digitos_codigo_barras[i] = j;
                checagem++; // Marca como convertido corretamente
            }
        }
    }

    // Converte os últimos 4 dígitos
    for(int i = 4; i < 8; i++){
        matriz_recebida[i][strcspn(matriz_recebida[i], "\n")] = '\0'; // Remove newline
        for(int j = 10; j < 20; j++){
            if(strcmp(matriz_recebida[i], matriz_base[j]) == 0){
                digitos_codigo_barras[i] = j - 10;
                checagem++; // Marca como convertido corretamente
            }
        }
    }

    // Se algum dígito não foi encontrado, retorna uma flag de erro (-1)
    if(checagem < 8){
        digitos_codigo_barras[0] = -1; // Erro na conversão
        return digitos_codigo_barras;
    }

    return digitos_codigo_barras; // Retorna o vetor com os valores convertidos
}