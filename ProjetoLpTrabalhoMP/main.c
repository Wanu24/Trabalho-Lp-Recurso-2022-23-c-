/* 
 * File:   main.c
 * Author: Manuel
 *
 * Created on 15 de fevereiro de 2023, 07:16
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "mercado.h"
#include "vendedor.h"
#include "log.h"
#include "menu.h"

/*
 * 
 */


int main(int argc, char** argv) {


    Vendedores vendedores;
    Mercados mercados;

    vendedores.numVendedores = 0;
    vendedores.totalVendedores = 5;
    mercados.numMercados = 0;
    mercados.totalMercados = 5;

    vendedores.vendedores = (Vendedor*) malloc(sizeof (Vendedor) * vendedores.totalVendedores);
    mercados.mercados = (Mercado*) malloc(sizeof (Mercado) * mercados.totalMercados);


    readVendedores(&vendedores);
    
    readMercados(&mercados);

    menu(&vendedores, &mercados);

    return (EXIT_SUCCESS);
}