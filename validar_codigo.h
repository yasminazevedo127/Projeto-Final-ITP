#ifndef VALIDADE_CODIGO_H_INCLUDED
#define VALIDADE_CODIGO_H_INCLUDED

extern int largura;
extern int altura;

int quant_tipo_elementos(char codeStr[]);

int convertInter(char x);

int validacao_identificador(int vetor[]);

int verificar_primeira_linha(FILE *arquivo);

int verificar_segunda_linha(FILE *arquivo);

int checar_espace(FILE *arquivo, int largura);

int verificar_codigo_de_barras(char** matriz_binaria, int* digitos_codigo_barras, int espace);

#endif // VALIDADE_CODIGO_H_INCLUDED