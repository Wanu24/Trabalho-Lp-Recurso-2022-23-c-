#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vendedor.h"
#include "input.h"

int procurarVendedor(Vendedores vendedores, int codigo) {
    int i;

    for (i = 0; i < vendedores.numVendedores; i++) {
        if (vendedores.vendedores[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void adicionarVendedor(Vendedores *vendedores) {
    int cod;
    printf("Criar vendedor:\n");
    cod = obterInteiro(0, MAX_INT, "Insira o código do vendedor que pretende criar: ");


    if (procurarVendedor(*vendedores, cod) == -1) {

        if ((*vendedores).totalVendedores == (*vendedores).numVendedores) {
            (*vendedores).totalVendedores += 3;
            (*vendedores).vendedores = (Vendedor*) realloc((*vendedores).vendedores, ((*vendedores).numVendedores) * sizeof (Vendedor));
        }



        (*vendedores).vendedores[(*vendedores).numVendedores].codigo = cod;
        (*vendedores).vendedores[(*vendedores).numVendedores].estado = 0;
        (*vendedores).vendedores[(*vendedores).numVendedores].telefone = obterInteiro(900000000, 999999999, "Insira o número de telefone: ");

        char buffer[SIZE_BUFFER];

        lerString(buffer, SIZE_BUFFER, "Nome: ");
        (*vendedores).vendedores[(*vendedores).numVendedores].nome = malloc((strlen(buffer) + 1) * sizeof (char));
        strcpy((*vendedores).vendedores[(*vendedores).numVendedores].nome, buffer);

        lerString(buffer, SIZE_BUFFER, "Email: ");
        (*vendedores).vendedores[(*vendedores).numVendedores].email = malloc((strlen(buffer) + 1) * sizeof (char));
        strcpy((*vendedores).vendedores[(*vendedores).numVendedores].email, buffer);


        (*vendedores).numVendedores++;
    } else {
        printf("O vendedor já existe!!");
    }
}

void libertarMemVendedor(Vendedores *vendedores) {
    int i;
    for (i = 0; i < vendedores->numVendedores; i++) {

        free(vendedores->vendedores[i].nome);
        free(vendedores->vendedores[i].email);
    }
    free(vendedores->vendedores);
}

void imprimirVendedor(Vendedor vendedor) {
    printf("\nCódigo:%d\nNome:%s\nTelefone:%d\nEmai:%s\n", vendedor.codigo, vendedor.nome,
            vendedor.telefone, vendedor.email
            );

    if (vendedor.estado == 0) {
        printf("Estado: ativo\n");
    } else if (vendedor.estado == 1) {
        printf("Estado: desativo\n");
    }


}

void listarVendedores(Vendedores vendedores) {
    int i;

    if (vendedores.numVendedores > 0) {
        for (i = 0; i < vendedores.numVendedores; i++) {
            imprimirVendedor(vendedores.vendedores[i]);
        }
    } else {
        printf("Não existem vendedores criados!!\n");
    }
}

void atualizarDadosVendedor(Vendedor *vendedor) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\nAtletar:\n1- Nome\n");
        printf("4- Telefone\n");
        printf("5- Email\n");
        printf("0- Voltar\n");
        escolha = obterInteiro(0, 3, "\nEscolha uma opção!\n");
        switch (escolha) {
            case 0:
                fflush(stdin);
                system("clear");
                break;

            case 1:
                lerString(buffer, SIZE_BUFFER, "Nome: ");
                vendedor->nome = realloc(vendedor->nome, (strlen(buffer) + 1) * sizeof (char));
                strcpy(vendedor->nome, buffer);
                break;

            case 2:
                vendedor->telefone = obterInteiro(900000000, 999999999, "Insira o número de telefone: ");
                break;

            case 3:
                lerString(buffer, SIZE_BUFFER, "Email: ");
                vendedor->email = realloc(vendedor->email, (strlen(buffer) + 1) * sizeof (char));
                strcpy(vendedor->email, buffer);
                break;

            default:
                printf("Opção inválida\n");
                fflush(stdin);
                system("clear");
                break;
        }
    } while (escolha != 0);

}

void editarVendedor(Vendedores *vendedores) {
    listarVendedores(*vendedores);

    printf("Editar dados do vendedor:\n");
    int id = procurarVendedor(*vendedores, obterInteiro(0, MAX_INT, "Insira o código do vendedor que pertende alterar: "));

    if (id != -1) {
        imprimirVendedor((*vendedores).vendedores[id]);
        atualizarDadosVendedor(&(*vendedores).vendedores[id]);

    } else {
        printf("Vendedor não existe!!\n");
    }
}

void eliminarVendedor(Vendedores *vendedores, Mercados mercados) {
    int i, j;
    listarVendedores(*vendedores);

    printf("Eliminar vendedor:\n");
    int indice = procurarVendedor(*vendedores, obterInteiro(0, MAX_INT, "Insira o código do vendedor que pertende eliminar: "));


    if (indice != -1) {

        if (mercados.numMercados > 0) {
            for (i = 0; i < mercados.numMercados; i++) {
                for (j = 0; j < mercados.mercados[i].numComissoes; j++) {
                    if (vendedores->vendedores[indice].codigo == mercados.mercados[i].comissoes[j].codigoVendedor) {
                        vendedores->vendedores[indice].estado = 1;
                        return;
                    }
                }
            }
        }

        free(vendedores->vendedores[indice].nome);
        free(vendedores->vendedores[indice].email);



        vendedores->numVendedores--;

        vendedores->vendedores[indice] = vendedores->vendedores[vendedores->numVendedores];

    } else {
        printf("Cliente não existe!!\n");
    }
}

void readVendedores(Vendedores *vendedores) {
    FILE *ficheiro;
    int i, j;
    ficheiro = fopen("Vendedores.bin", "rb");
    if (ficheiro == NULL) {
        printf("\nErro ao abrir/criar o ficheiro\n");
        return;
    }
    fread(&vendedores->totalVendedores, sizeof (int), 1, ficheiro);
    fread(&vendedores->numVendedores, sizeof (int), 1, ficheiro);
    if (vendedores->numVendedores == 0) {
        fclose(ficheiro);
        printf("\nNao existem vendedores para importar\n");

    } else {
        vendedores->vendedores = (Vendedor*) realloc((*vendedores).vendedores, ((*vendedores).totalVendedores) * sizeof (Vendedor));
        for (i = 0; i < vendedores->numVendedores; i++) {
            fread(&vendedores->vendedores[i].codigo, sizeof (int), 1, ficheiro);
            fread(&vendedores->vendedores[i].telefone, sizeof (int), 1, ficheiro);
            fread(&vendedores->vendedores[i].estado, sizeof (Estado), 1, ficheiro);
            int buffer;
            fread(&buffer, sizeof (int), 1, ficheiro);
            vendedores->vendedores[i].nome = (char*) malloc(sizeof (char) * (buffer + 1));
            fread(vendedores->vendedores[i].nome, sizeof (char), buffer, ficheiro);
            vendedores->vendedores[i].nome[buffer] = '\0';
            fread(&buffer, sizeof (int), 1, ficheiro);
            vendedores->vendedores[i].email = (char*) malloc(sizeof (char) * (buffer + 1));
            fread(vendedores->vendedores[i].email, sizeof (char), buffer, ficheiro);
            vendedores->vendedores[i].email[buffer] = '\0';
        }
        fclose(ficheiro);
        printf("\nVendedores importados com sucesso\n");
    }
}

void writeVendedores(Vendedores *vendedores) {
    if (vendedores->numVendedores == 0) {
        printf("\nNao existem vendedores para exportar\n");
        return;
    }
    int i, j;
    FILE *ficheiro;
    ficheiro = fopen("Vendedores.bin", "wb");
    if (ficheiro == NULL) {
        printf("\nErro ao criar/abrir o ficheiro\n");
        return;
    }
    fwrite(&vendedores->totalVendedores, sizeof (int), 1, ficheiro);
    fwrite(&vendedores->numVendedores, sizeof (int), 1, ficheiro);
    for (i = 0; i < vendedores->numVendedores; i++) {
        fwrite(&vendedores->vendedores[i].codigo, sizeof (int), 1, ficheiro);
        fwrite(&vendedores->vendedores[i].telefone, sizeof (int), 1, ficheiro);
        fwrite(&vendedores->vendedores[i].estado, sizeof (Estado), 1, ficheiro);
        int buffer = strlen(vendedores->vendedores[i].nome);
        fwrite(&buffer, sizeof (int), 1, ficheiro);
        fwrite(vendedores->vendedores[i].nome, sizeof (char), buffer, ficheiro);
        buffer = strlen(vendedores->vendedores[i].email);
        fwrite(&buffer, sizeof (int), 1, ficheiro);
        fwrite(vendedores->vendedores[i].email, sizeof (char), buffer, ficheiro);
    }
    fclose(ficheiro);
    printf("\nVendedores exportados com sucesso\n");
}

void listarVendedorComissoes(Vendedores vendedores, Mercados mercados) {
    int i, j, temp;
    int repeticoes[vendedores.numVendedores];
    for (i = 0; i < mercados.numMercados; i++) {
        if (mercados.mercados[i].numComissoes != 0) {
            for (j = 0; j < mercados.mercados[i].numComissoes; j++) {
                temp = procurarVendedor(vendedores, mercados.mercados[i].comissoes[j].codigoVendedor);
                repeticoes[temp]++;
            }
        }
    }
    for (i = 0; i < mercados.numMercados - 1; i++) {
        for (j = 0; j < mercados.numMercados - i - 1; j++) {
            if (repeticoes[j] < repeticoes[j + 1]) {
                temp = repeticoes[j];
                repeticoes[j] = repeticoes[j + 1];
                repeticoes[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < mercados.numMercados; i++) {
        printf("\nPosição:%d", (i+1));
        imprimirVendedor(vendedores.vendedores[temp]);

    }

}