/* 
 * File:   vendedor.h
 * Author: Manuel
 *
 * Created on 15 de fevereiro de 2023, 08:35
 */

#ifndef VENDEDOR_H
#define VENDEDOR_H
#include "mercado.h"
#include "input.h"

int procurarVendedor(Vendedores vendedores, int codigo);

void adicionarVendedor(Vendedores *vendedores);

void libertarMemVendedor(Vendedores *vendedores);

void imprimirVendedor(Vendedor vendedor);

void listarVendedores(Vendedores vendedores);

void atualizarDadosVendedor(Vendedor *vendedor);

void editarVendedor(Vendedores *vendedores);

void eliminarVendedor(Vendedores *vendedores, Mercados mercados);

void readVendedores(Vendedores *vendedores);

void writeVendedores(Vendedores *vendedores);

void listarVendedorComissoes(Vendedores vendedores, Mercados mercados);

#endif /* VENDEDOR_H */

