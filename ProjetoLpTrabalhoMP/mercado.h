/* 
 * File:   mercado.h
 * Author: Manuel
 *
 * Created on 15 de fevereiro de 2023, 08:35
 */

#ifndef MERCADO_H
#define MERCADO_H
#include "vendedor.h"
#include "input.h"

int procurarMercado(Mercados mercados, int codigo);

void adicionarMercado(Mercados *mercados);

void libertarMemMercado(Mercados *mercados);

void imprimirMercado(Mercado mercado);

void listarMercados(Mercados mercados);

void atualizarDadosMercado(Mercado *mercado);

void editarMercado(Mercados *mercados);

void adicionarComissao(Mercados *mercados, Vendedores vendedores);

void imprimirComissaoMercado(Mercado mercado, int indiceComissao);

void eliminarMercado(Mercados *mercados);

int verificarData(Comissao comissao1, Comissao comissao2);

void concluirComissao(Mercados *mercados, Vendedores vendedores);

void readMercados(Mercados *mercados);

void writeMercados(Mercados *mercados);

void listarMercadosComissoes(Mercados mercados);

#endif /* MERCADO_H */

