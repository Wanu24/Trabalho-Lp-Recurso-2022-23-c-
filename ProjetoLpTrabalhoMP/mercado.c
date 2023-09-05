#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mercado.h"
#include "input.h"

int procurarMercado(Mercados mercados, int codigo) {
    int i;

    for (i = 0; i < mercados.numMercados; i++) {
        if (mercados.mercados[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void adicionarMercado(Mercados *mercados) {
    int cod;
    printf("Criar mercado:\n");
    cod = obterInteiro(0, MAX_INT, "Insira o código do mercado que pretende criar: ");


    if (procurarMercado(*mercados, cod) == -1) {

        if ((*mercados).totalMercados == (*mercados).numMercados) {
            (*mercados).totalMercados += 3;
            (*mercados).mercados = (Mercado*) realloc((*mercados).mercados, ((*mercados).totalMercados) * sizeof (Mercado));
        }



        (*mercados).mercados[(*mercados).numMercados].codigo = cod;
        (*mercados).mercados[(*mercados).numMercados].estado = 0;

        char buffer[SIZE_BUFFER];

        lerString(buffer, SIZE_BUFFER, "Nome: ");
        (*mercados).mercados[(*mercados).numMercados].nome = malloc((strlen(buffer) + 1) * sizeof (char));
        strcpy((*mercados).mercados[(*mercados).numMercados].nome, buffer);

        (*mercados).mercados[(*mercados).numMercados].numComissoes = 0;
        (*mercados).mercados[(*mercados).numMercados].totalComissoes = 3;

        (*mercados).mercados[(*mercados).numMercados].comissoes = (Comissao*) malloc(sizeof (Mercado) * (*mercados).mercados[(*mercados).numMercados].totalComissoes);

        (*mercados).numMercados++;

    } else {
        printf("O mercado já existe!!");
    }
}

void libertarMemMercado(Mercados *mercados) {
    int i;
    for (i = 0; i < mercados->numMercados; i++) {

        free(mercados->mercados[i].nome);
        free(mercados->mercados[i].comissoes);
    }
    free(mercados->mercados);
}

void imprimirMercado(Mercado mercado) {
    int i;
    printf("\nCódigo:%d\nNome:%s\n", mercado.codigo, mercado.nome);

    for (i = 0; i < mercado.numComissoes; i++) {
        imprimirComissaoMercado(mercado, i);
    }

    if (mercado.estado == 0) {
        printf("Estado do mercado: Ativo\n");
    } else if (mercado.estado == 1) {
        printf("Estado: desativo\n");
    }
}

void listarMercados(Mercados mercados) {
    int i;

    if (mercados.numMercados > 0) {
        for (i = 0; i < mercados.numMercados; i++) {
            imprimirMercado(mercados.mercados[i]);
        }
    } else {
        printf("Não existem mercados criados!!\n");
    }
}

void atualizarDadosMercado(Mercado *mercado) {
    int escolha, i, k;
    char buffer[SIZE_BUFFER];

    do {
        printf("1- Nome\n");
        printf("0- Voltar\n");
        escolha = obterInteiro(0, 1, "\nEscolha uma opção!\n");
        switch (escolha) {
            case 0:
                fflush(stdin);
                system("clear");
                break;

            case 1:
                lerString(buffer, SIZE_BUFFER, "Nome: ");
                mercado->nome = realloc(mercado->nome, (strlen(buffer) + 1) * sizeof (char));
                strcpy(mercado->nome, buffer);
                break;
            default:
                printf("Opção inválida\n");
                fflush(stdin);
                system("clear");
                break;
        }
    } while (escolha != 0);

}

void editarMercado(Mercados *mercados) {
    listarMercados(*mercados);

    printf("Editar dados do mercado:\n");
    int id = procurarMercado(*mercados, obterInteiro(0, MAX_INT, "Insira o código do mercado que pertende alterar: "));

    if (id != -1) {
        imprimirMercado((*mercados).mercados[id]);
        atualizarDadosMercado(&(*mercados).mercados[id]);

    } else {
        printf("Mercado não existe!!\n");
    }
}

void adicionarComissao(Mercados *mercados, Vendedores vendedores) {
    int codVendedor, indiceVendedor, indiceMercado, i, j;
    printf("Crirar comissao:\n");
    codVendedor = obterInteiro(0, MAX_INT, "Insira o código do vendedor: ");
    indiceVendedor = procurarVendedor(vendedores, codVendedor);

    if (indiceVendedor != -1) {
        if (vendedores.vendedores[indiceVendedor].estado == 0) {

            indiceMercado = procurarMercado(*mercados, obterInteiro(0, MAX_INT, "Insira o código do mercado onde pretende criar: "));
            if (indiceMercado != -1) {
                if (mercados->mercados[indiceMercado].estado == 0) {

                    if ((*mercados).mercados[indiceMercado].totalComissoes == (*mercados).mercados->numComissoes) {
                        (*mercados).mercados[indiceMercado].totalComissoes += 3;
                        (*mercados).mercados[indiceMercado].comissoes = (Comissao*) realloc((*mercados).mercados[indiceMercado].comissoes, ((*mercados).mercados[indiceMercado].totalComissoes) * sizeof (Comissao));
                    }



                    (*mercados).mercados[indiceMercado].comissoes[(*mercados).mercados[indiceMercado].numComissoes].codigoVendedor = codVendedor;
                    (*mercados).mercados[indiceMercado].comissoes[(*mercados).mercados[indiceMercado].numComissoes].percentagem = obterInteiro(0, 100, "Insira a percentagem de comissão: ");
                    (*mercados).mercados[indiceMercado].comissoes[(*mercados).mercados[indiceMercado].numComissoes].estado = 0;
                    (*mercados).mercados[indiceMercado].comissoes[(*mercados).mercados[indiceMercado].numComissoes].dataInicio.ano = obterInteiro(1900, 2023, "Insira o ano: ");
                    (*mercados).mercados[indiceMercado].comissoes[(*mercados).mercados[indiceMercado].numComissoes].dataInicio.mes = obterInteiro(1, 12, "Insira o mes: ");
                    (*mercados).mercados[indiceMercado].comissoes[(*mercados).mercados[indiceMercado].numComissoes].dataInicio.dia = obterInteiro(1, 31, "Insira o dia: ");
                    (*mercados).mercados[indiceMercado].comissoes[(*mercados).mercados[indiceMercado].numComissoes].dataFim.ano = 0;
                    (*mercados).mercados[indiceMercado].comissoes[(*mercados).mercados[indiceMercado].numComissoes].dataFim.mes = 0;
                    (*mercados).mercados[indiceMercado].comissoes[(*mercados).mercados[indiceMercado].numComissoes].dataFim.dia = 0;


                    for (i = 0, j = 0; i < (*mercados).mercados[indiceMercado].numComissoes; i++) {
                        if ((*mercados).mercados[indiceMercado].comissoes[i].codigoVendedor == codVendedor) {
                            if (verificarData((*mercados).mercados[indiceMercado].comissoes[(*mercados).mercados[indiceMercado].numComissoes], (*mercados).mercados[indiceMercado].comissoes[i]) != 0) {
                                j++;
                            }
                        }
                    }
                    if (j == 0) {
                        (*mercados).mercados[indiceMercado].numComissoes++;
                    } else {
                        printf("A data introduzida é inválida!!\n");
                    }
                } else {
                    printf("O Mercado está desativo!!");
                }
            } else {
                printf("O mercado não existe!!");
            }
        } else {
            printf("O vendendor está desativo!!");
        }
    } else {
        printf("O vendedor não existe!!");
    }
}

void imprimirComissaoMercado(Mercado mercado, int indiceComissao) {
    printf("\nComissão %d:\n", (indiceComissao + 1));
    printf("\nCódigo:%d\nPercentagem:%d\nData de início:%d/%d/%d\n", mercado.comissoes[indiceComissao].codigoVendedor,
            mercado.comissoes[indiceComissao].percentagem, mercado.comissoes[indiceComissao].dataInicio.dia,
            mercado.comissoes[indiceComissao].dataInicio.mes, mercado.comissoes[indiceComissao].dataInicio.ano);

    if (mercado.comissoes[indiceComissao].estado == 0) {
        printf("Estado da comissao: Ativo\n\n\n");
    } else {
        printf("Data do Fim:%d/%d/%d\n", mercado.comissoes[indiceComissao].dataFim.dia,
                mercado.comissoes[indiceComissao].dataFim.mes, mercado.comissoes[indiceComissao].dataFim.ano);
        printf("Estado: Concluído\n\n\n");
    }


}

void eliminarMercado(Mercados *mercados) {
    listarMercados(*mercados);

    printf("Eliminar mercado:\n");
    int indice = procurarMercado(*mercados, obterInteiro(0, MAX_INT, "Insira o código do mercado que pertende eliminar: "));


    if (indice != -1) {

        if (mercados->mercados[indice].numComissoes != 0) {
            mercados->mercados[indice].estado = 1;
            return;
        }

        free(mercados->mercados[indice].nome);
        free(mercados->mercados[indice].comissoes);



        mercados->numMercados--;

        mercados->mercados[indice] = mercados->mercados[mercados->numMercados];

    } else {
        printf("Mercado não existe!!\n");
    }
}

int verificarData(Comissao comissao1, Comissao comissao2) {
    if (comissao2.estado == 0) {
        printf("O vendedor já tem uma comissao ativa neste mercado!!\n");
        return 0;
    }
    if (comissao1.dataInicio.ano == comissao2.dataFim.ano) {
        if (comissao1.dataInicio.mes == comissao2.dataFim.mes) {
            if (comissao1.dataInicio.dia < comissao2.dataFim.dia) {
                return -1;
            }
        } else {
            if (comissao1.dataInicio.mes < comissao2.dataFim.mes) {
                return -1;
            }
        }
    } else {
        if (comissao1.dataInicio.ano < comissao2.dataFim.ano) {
            return -1;
        }
    }
    return 0;
}

void concluirComissao(Mercados *mercados, Vendedores vendedores) {
    int i;
    int indiceMercado = procurarMercado(*mercados, obterInteiro(0, MAX_INT, "Insira o código do mercado: "));
    if (indiceMercado != -1) {
        int codVendedor = obterInteiro(0, MAX_INT, "Insira o código do vendedor: ");
        if (procurarVendedor(vendedores, codVendedor) != -1) {
            for (i = 0; i < (*mercados).mercados[indiceMercado].numComissoes; i++) {
                if ((*mercados).mercados[indiceMercado].comissoes[i].codigoVendedor == codVendedor && (*mercados).mercados[indiceMercado].comissoes[i].estado == 0) {

                    (*mercados).mercados[indiceMercado].comissoes[i].dataFim.ano = obterInteiro(1900, 2023, "Insira o ano: ");
                    (*mercados).mercados[indiceMercado].comissoes[i].dataFim.mes = obterInteiro(1, 12, "Insira o mes: ");
                    (*mercados).mercados[indiceMercado].comissoes[i].dataFim.dia = obterInteiro(1, 31, "Insira o dia: ");
                    (*mercados).mercados[indiceMercado].comissoes[i].estado == 1;
                }
            }
        } else {
            printf("O vendedor não existe!!");
        }
    } else {
        printf("O mercado não existe!!");
    }
}

void readMercados(Mercados *mercados) {
    FILE *ficheiro;
    int i, j;
    ficheiro = fopen("Mercados.bin", "rb");
    if (ficheiro == NULL) {
        printf("\nErro ao abrir/criar o ficheiro\n");
        return;
    }
    fread(&mercados->totalMercados, sizeof (int), 1, ficheiro);
    fread(&mercados->numMercados, sizeof (int), 1, ficheiro);
    if (mercados->numMercados == 0) {
        fclose(ficheiro);
        printf("\nNao existem mercados para importar\n");
    } else {
        mercados->mercados = (Mercado*) realloc((*mercados).mercados, ((*mercados).totalMercados) * sizeof (Mercado));
        for (i = 0; i < mercados->numMercados; i++) {
            fread(&mercados->mercados[i].codigo, sizeof (int), 1, ficheiro);
            fread(&mercados->mercados[i].numComissoes, sizeof (int), 1, ficheiro);
            fread(&mercados->mercados[i].totalComissoes, sizeof (int), 1, ficheiro);
            fread(&mercados->mercados[i].estado, sizeof (Estado), 1, ficheiro);
            int buffer;
            fread(&buffer, sizeof (int), 1, ficheiro);
            mercados->mercados[i].nome = (char*) malloc(sizeof (char) * (buffer + 1));
            fread(mercados->mercados[i].nome, sizeof (char), buffer, ficheiro);
            mercados->mercados[i].nome[buffer] = '\0';
            mercados->mercados[i].comissoes = (Comissao*) malloc(((*mercados).mercados[i].totalComissoes) * sizeof (Comissao));
            if (mercados->mercados[i].numComissoes != 0) {
                for (j = 0; j < mercados->mercados[i].numComissoes; j++) {
                    fread(&mercados->mercados[i].comissoes[j].dataInicio.ano, sizeof (int), 1, ficheiro);
                    fread(&mercados->mercados[i].comissoes[j].dataInicio.mes, sizeof (int), 1, ficheiro);
                    fread(&mercados->mercados[i].comissoes[j].dataInicio.dia, sizeof (int), 1, ficheiro);
                    fread(&mercados->mercados[i].comissoes[j].dataFim.ano, sizeof (int), 1, ficheiro);
                    fread(&mercados->mercados[i].comissoes[j].dataFim.mes, sizeof (int), 1, ficheiro);
                    fread(&mercados->mercados[i].comissoes[j].dataFim.dia, sizeof (int), 1, ficheiro);
                    fread(&mercados->mercados[i].comissoes[j].codigoVendedor, sizeof (int), 1, ficheiro);
                    fread(&mercados->mercados[i].comissoes[j].percentagem, sizeof (int), 1, ficheiro);
                    fread(&mercados->mercados[i].comissoes[j].estado, sizeof (Estado), 1, ficheiro);
                }
            }
        }
        fclose(ficheiro);
        printf("\nMercados importados com sucesso\n");
    }
}

void writeMercados(Mercados *mercados) {
    if (mercados->numMercados == 0) {
        printf("\nNao existem mercados para exportar\n");
        return;
    }
    int i, j;
    FILE *ficheiro;
    ficheiro = fopen("Mercados.bin", "wb");
    if (ficheiro == NULL) {
        printf("\nErro ao criar/abrir o ficheiro\n");
        return;
    }
    fwrite(&mercados->totalMercados, sizeof (int), 1, ficheiro);
    fwrite(&mercados->numMercados, sizeof (int), 1, ficheiro);
    for (i = 0; i < mercados->numMercados; i++) {
        fwrite(&mercados->mercados[i].codigo, sizeof (int), 1, ficheiro);
        fwrite(&mercados->mercados[i].numComissoes, sizeof (int), 1, ficheiro);
        fwrite(&mercados->mercados[i].totalComissoes, sizeof (int), 1, ficheiro);
        fwrite(&mercados->mercados[i].estado, sizeof (Estado), 1, ficheiro);
        int buffer = strlen(mercados->mercados[i].nome);
        fwrite(&buffer, sizeof (int), 1, ficheiro);
        fwrite(mercados->mercados[i].nome, sizeof (char), buffer, ficheiro);
        if (mercados->mercados[i].numComissoes != 0) {
            for (j = 0; j < mercados->mercados[i].numComissoes; j++) {
                fwrite(&mercados->mercados[i].comissoes[j].dataInicio.ano, sizeof (int), 1, ficheiro);
                fwrite(&mercados->mercados[i].comissoes[j].dataInicio.mes, sizeof (int), 1, ficheiro);
                fwrite(&mercados->mercados[i].comissoes[j].dataInicio.dia, sizeof (int), 1, ficheiro);
                fwrite(&mercados->mercados[i].comissoes[j].dataFim.ano, sizeof (int), 1, ficheiro);
                fwrite(&mercados->mercados[i].comissoes[j].dataFim.mes, sizeof (int), 1, ficheiro);
                fwrite(&mercados->mercados[i].comissoes[j].dataFim.dia, sizeof (int), 1, ficheiro);
                fwrite(&mercados->mercados[i].comissoes[j].codigoVendedor, sizeof (int), 1, ficheiro);
                fwrite(&mercados->mercados[i].comissoes[j].percentagem, sizeof (int), 1, ficheiro);
                fwrite(&mercados->mercados[i].comissoes[j].estado, sizeof (Estado), 1, ficheiro);
            }
        }
    }
    fclose(ficheiro);
    printf("\nMercados exportados com sucesso\n");
}

void listarMercadosComissoes(Mercados mercados) {
    int i, j, comissoes[mercados.numMercados], temp;
    for (i = 0; i < mercados.numMercados - 1; i++) {
        comissoes[i] = mercados.mercados[i].numComissoes;
    }

    for (i = 0; i < mercados.numMercados - 1; i++) {
        for (j = 0; j < mercados.numMercados - i - 1; j++) {
            if (comissoes[j] < comissoes[j + 1]) {
                temp = comissoes[j];
                comissoes[j] = comissoes[j + 1];
                comissoes[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < mercados.numMercados; i++) {
        printf("\nPosição:%d", (i + 1));
        imprimirMercado(mercados.mercados[temp]);
    }
}