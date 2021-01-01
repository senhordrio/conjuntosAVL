/*
 * @autor: senhordrio
 * Classe da estrutura nó. Os nós da árvore.
 */

#ifndef NOHARVORE_H
#define NOHARVORE_H
#include <iostream>

typedef int Dado;

class nohArvore
{
	friend class avl;

private:
	nohArvore *esquerdo;
	nohArvore *direito;
	nohArvore *pai;
	Dado valor;
	int altura;
	int calculaBalanceamento(nohArvore *noh);
	unsigned int calculaAltura(nohArvore *noh);

public:
	int fatorBalanceamento();
	nohArvore(Dado dado);
	~nohArvore();
};

#endif