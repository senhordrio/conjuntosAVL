/*
 * @autor: senhordrio
 * Classe conjunto que representa a estrutura de dado conjunto.
 * Aqui estão presentes as operações básicas de conjuntos.
 * 
 */

#ifndef CONJUNTO_H
#define CONJUNTO_H

#include "nohArvore.h"
#include "avl.h"

using namespace std;

class conjunto
{
private:
	avl mDados;

public:
	// sugestão de métodos públicos para sua classe conjunto
	void insere(int elemento);
	void remove(int elemento);
	bool membro(int elemento);

	void uniao(conjunto &C1, conjunto &C2);
	void intersecao(conjunto &C1, conjunto &C2);
	void diferenca(conjunto &C1, conjunto &C2);

	unsigned tamanho();

	void imprime();
	void depura();
};

#endif