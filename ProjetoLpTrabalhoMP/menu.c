#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "input.h"
#include "vendedor.h"
#include "mercado.h"
#include "log.h"

void menu(Vendedores *vendedores, Mercados *mercados) {
    int escolha;

    printf("\n");
    puts(MENU);
    printf("  Móveis para Todos  \n");
    puts(MENU);

    puts(MENU);
    printf("|         Menu             |\n");
    puts(MENU);

    printf("1- Criar vendendedor\n");
    printf("2- Listar vendedores\n");
    printf("3- Editar vendedor\n");
    printf("4- Eliminar vendedor\n");
    printf("5- Criar mercado\n");
    printf("6- Listar mercados\n");
    printf("7- Editar mercado\n");
    printf("8- Eliminar mercado\n");
    printf("9- Adicionar comissao\n");
    printf("10- Concluir comissao\n");
    printf("11- Listar vendedores por comissoes\n");
    printf("12- Listar mercados por comissoes\n");
    printf("0- Sair do programa e guardar alterações\n");

    puts(MENU);
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);
    system("clear");


    switch (escolha) {
        case 1:
            adicionarVendedor(vendedores);
            logMsg("Criar vendedor");
            break;
        case 2:
            listarVendedores(*vendedores);
            logMsg("Listar vendedores");
            break;
        case 3:
            editarVendedor(vendedores);
            logMsg("Editar vendedor");
            break;
        case 4:
            eliminarVendedor(vendedores, *mercados);
            logMsg("Eliminar vendedor");
            break;
        case 5:
            adicionarMercado(mercados);
            logMsg("Criar vendedor");
            break;
        case 6:
            listarMercados(*mercados);
            logMsg("Listar vendedores");
            break;
        case 7:
            editarMercado(mercados);
            logMsg("Editar vendedor");
            break;

        case 8:
            eliminarMercado(mercados);
            logMsg("Eliminar vendedor");
            break;

        case 9:
            adicionarComissao(mercados, *vendedores);
            logMsg("Adicionar comissao");
            break;

        case 10:
            concluirComissao(mercados, *vendedores);
            logMsg("Conlcuir comissao");
            break;

        case 11:
            listarVendedorComissoes(*vendedores, *mercados);
            logMsg("Listar vendedores por comissoes");
            break;
            
        case 12:
            listarMercadosComissoes(*mercados);
            logMsg("Listar mercados por comissoes");
            break;

        case 0:
            logMsg("Sair do programa");

            writeVendedores(vendedores);
            writeMercados(mercados);

            libertarMemVendedor(vendedores);
            libertarMemMercado(mercados);

            sairPrograma();
            break;
        default:
            printf("Opção inválida\n");
            printf("Prima ENTER para voltar ao menu\n");
            fflush(stdin);
            getchar();
            system("clear");
            menu(vendedores, mercados);
            break;
    };
    menu(vendedores, mercados);
}

void sairPrograma() {
    printf("Guardar alterações....\n");
    printf("Obrigado por utilizar o programa\n");
    fflush(stdin);
    getchar();
    exit(0);
}